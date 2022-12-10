#include <thread>

#include "event.hpp"
#include "task.hpp"


using namespace std::chrono_literals;
using ms = std::chrono::milliseconds;

ms DEFAULT_TIMEOUT = 1000ms;

void client_thread(const event_t& event, ms timeout) {
    while (true) {
        std::cout << "Entering client loop \n";
        std::this_thread::sleep_for(timeout);
        std::cout << "Emmiting event ... \n";
        event.notify();
    }
}

void_task_t server_thread(const event_t& event) {
    while (true) {
        std::cout << "Entering server loop\n";
        co_await event;
        std::cout << "Event received\n";
    }
}

int main() {
    event_t event("event 1");

    std::jthread client_1(client_thread, std::cref(event), 1000ms);
    std::jthread client_2(client_thread, std::cref(event), 1300ms);
    std::jthread server(server_thread, std::cref(event));
}
