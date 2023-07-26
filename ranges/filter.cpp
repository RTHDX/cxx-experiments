#include <iostream>
#include <vector>
#include <ranges>

#include <boost/stacktrace.hpp>

struct Entry {
    int id;
};

int main() {
    std::cout << boost::stacktrace::stacktrace() << std::endl;

    const std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto even_numbers = numbers | std::views::filter([](int x) { return x % 2 == 0; });

    for (auto n : even_numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    for (auto n : numbers) {
        std::cout << n << " ";
    } std::cout << std::endl;

    std::vector<Entry> entries{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
    auto predicate = [](const Entry& e) { return e.id % 2 != 0; };
    std::ranges::filter_view<std::ranges::ref_view<std::vector<Entry>>, decltype(predicate)> odd_entries = entries | std::views::filter(predicate);
    for (auto& e : odd_entries) {
        std::cout << e.id << " ";
    }
    std::cout << std::endl;

    return 0;
}
