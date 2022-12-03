#pragma once

#include <coroutine>
#include <memory>
#include <iostream>


template <typename T>
struct generator_t {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    generator_t(handle_type h) : coro(h) {}
    ~generator_t() { if (coro) { coro.destroy(); } }
    generator_t(const generator_t&) = delete;
    generator_t& operator = (const generator_t&) = delete;

    generator_t(generator_t&& old) : coro(old.coro) {
        old.coro = nullptr;
    }

    generator_t& operator = (generator_t&& old) {
        if (this == &old) { return *this; }

        coro = old.coro;
        old.coro = nullptr;
        return *this;
    }

    T get_value() {
        return coro.promise().current_value;
    }

    bool next() {
        coro.resume();
        return not coro.done();
    }

    handle_type coro;
    std::shared_ptr<T> value;

    struct promise_type {
        promise_type() = default;
        ~promise_type() = default;

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        generator_t<T> get_return_object() {
            return generator_t<T>{ handle_type::from_promise(*this) };
        }

        std::suspend_never return_void() {
            return {};
        }

        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        void unhandled_exception() {
            std::exit(1);
        }

        T current_value;
    };
};

template <typename G> concept generator_c = requires(G g) {
    G::promise_type;
    g.get_value();
    g.next();
};
