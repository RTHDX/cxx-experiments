#include <atomic>
#include <vector>
#include <thread>
#include <iostream>

std::vector<int> vec;
std::atomic_flag flag{};

void prepare_work() {
    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "Preparation complete" << std::endl;
    flag.test_and_set();
    flag.notify_all();
}

void add_work() {
    flag.wait(false);
    int accum = 0;
    for (auto i : vec) {
        accum += i;
    }
    std::cout << "Add worker completed. Sum = " << accum << std::endl;
}

void sub_work() {
    flag.wait(false);
    int accum = 0;
    for (auto i : vec) {
        accum -= i;
    }
    std::cout << "Sub worker completed. Sub = " << accum << std::endl;
}

int main() {
    std::cout << "Staring..." << std::endl;

    std::thread preparation(prepare_work);
    std::thread add(add_work);
    std::thread sub(sub_work);

    preparation.join();
    add.join();
    sub.join();

    std::cout << "End..." << std::endl;
}
