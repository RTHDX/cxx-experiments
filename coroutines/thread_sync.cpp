#include "event.hpp"
#include "task.hpp"

using namespace std::chrono_literals;

void evel_elapsed(const auto& start, const auto& end) {
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Waited = " << elapsed.count() << " seconds" << std::endl;
}

void_task_t receiver(event_t& event) {
    auto start = std::chrono::high_resolution_clock::now();
    co_await event;
    std::cout << "Received the event! " << event.name() << std::endl;
    evel_elapsed(start, std::chrono::high_resolution_clock::now());
}

void_task_t number_receiver(const event_t& event, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    co_await event;
    std::cout << "Received the event! " << event.name() << " at thread: " << n
              << std::endl;
    evel_elapsed(start, std::chrono::high_resolution_clock::now());
}

void send_work(const event_t& event) {
    std::cout << "Worker thread entering..." << std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout << "Workder thread ending..." << std::endl;
    event.notify();
}

void_task_t multiple_events_receiver(const event_t& event_1,
                                     const event_t& event_2) {
    auto start = std::chrono::high_resolution_clock::now();

    co_await event_1;
    std::cout << "Received event 1" << std::endl;
    evel_elapsed(start, std::chrono::high_resolution_clock::now());

    co_await event_2;
    std::cout << "Received event 2" << std::endl;
    evel_elapsed(start, std::chrono::high_resolution_clock::now());
}

using ms = std::chrono::milliseconds;
void custom_work(const event_t& event, ms timeout) {
    std::this_thread::sleep_for(timeout);
    std::cout << "Exiting event..." << event.name() << std::endl;
    event.notify();
}

int main() {
    std::cout << std::endl;
/*
    std::cout << "Notification before waiting " << std::endl;
    event_t event_0;
    auto sender_0 = std::thread(custom_work, std::cref(event_0), 1000ms);
    auto receiver_0 = std::thread(receiver, std::ref(event_0));

    receiver_0.join();
    sender_0.join();

    std::cout << std::endl;

    event_t event_1("custom_event_1"), event_2("custom_event_2");
    auto sender_1 = std::thread(custom_work, std::cref(event_1), 2000ms);
    auto sender_2 = std::thread(custom_work, std::cref(event_2), 1000ms);
    auto receiver_12 = std::thread(multiple_events_receiver,
                                   std::cref(event_1),
                                   std::cref(event_2));

    receiver_12.join();
    sender_1.join();
    sender_2.join();

    std::cout << std::endl;
*/
    event_t event_3("multiple_waiters");
    auto sender_3 = std::thread(custom_work, std::cref(event_3), 500ms);
    auto receiver_3 = std::thread(number_receiver, std::ref(event_3), 1);
    auto receiver_4 = std::thread(number_receiver, std::ref(event_3), 2);
    auto receiver_5 = std::thread(number_receiver, std::ref(event_3), 3);

    receiver_5.join();
    receiver_4.join();
    receiver_3.join();
    sender_3.join();

    return 0;
}
