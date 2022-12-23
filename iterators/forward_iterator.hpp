#pragma once

#include <iterator>
#include <cstddef>
#include <vector>
#include <iostream>


template <typename T> class container_t {
public:
    container_t(std::vector<T>&& input) {
        size_t lowest = input.size() < MAX_LEN ? input.size() : MAX_LEN;
        for (ptrdiff_t i = 0; i < lowest; ++i) {
            _data[i] = input[i];
        }
        _actual_len = lowest;
    }

    struct iterator {
        using iterator_categosy = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator(pointer ptr) : _ptr(ptr) {}

        reference operator * () const {
            std::cout << __FUNCSIG__ << std::endl;
            return *_ptr;
        }

        pointer operator -> () const {
            std::cout << __FUNCSIG__ << std::endl;
            return _ptr;
        }

        iterator& operator ++ () {
            std::cout << __FUNCSIG__ << std::endl;
            _ptr++;
            return *this;
        }

        iterator operator ++ (int) {
            std::cout << __FUNCSIG__ << std::endl;
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator == (const iterator& lhs, const iterator& rhs) {
            return lhs._ptr == rhs._ptr;
        }

        friend bool operator != (const iterator& lhs, const iterator& rhs) {
            return lhs._ptr != rhs._ptr;
        }

    private:
        pointer _ptr;
    };

    iterator begin() { return &_data[0]; }
    iterator end()   { return &_data[_actual_len]; }

private:
    static constexpr size_t MAX_LEN = 1000;

    T _data[MAX_LEN];
    size_t _actual_len {0};
};
