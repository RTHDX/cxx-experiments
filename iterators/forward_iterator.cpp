#include <iostream>

#include "forward_iterator.hpp"

int main() {
    container_t<int> ints({1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (auto num : ints) {
        std::cout << num << std::endl;
    }
    std::cout << std::endl;

    container_t<double> doubles({1.0, 2.0, 3.4, 5.6, 3.5, 5.3});
    for (auto num : doubles) {
        std::cout << num << std::endl;
    }
    return 0;
}
