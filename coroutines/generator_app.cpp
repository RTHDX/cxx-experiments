#include <iostream>

#include "simple_generator.hpp"


generator_t<int> range_i(int s = 0, int step = 1) {
    for (int current = s;; current += step) {
        co_yield current;
    }
}

generator_t<double> range_d(double s = 0.0, double step = 1.0) {
    for (double current = s;; current += step) {
        co_yield current;
    }
}

int main() {
    auto generator = range_i();
    for (int i = 0; i < 10; ++i) {
        generator.next();
        std::cout << generator.get_value() << std::endl;
    }
    std::cout << std::endl;
    auto generator_d = range_d();
    for (int i = 0; i < 10; ++i) {
        generator_d.next();
        std::cout << generator_d.get_value() << std::endl;
    }
}
