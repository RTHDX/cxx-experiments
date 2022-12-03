#pragma once

#include <coroutine>
#include <chrono>
#include <iostream>
#include <functional>
#include <string>
#include <stdexcept>
#include <atomic>
#include <thread>


class event_t {
public:
    event_t() = default;
    event_t(std::string&& name);
    event_t(const event_t&) = delete;
    event_t(event_t&&) = delete;
    event_t& operator = (const event_t&) = delete;
    event_t& operator = (event_t&&) = delete;
    ~event_t() = default;

    class awaiter_t;
    awaiter_t operator co_await() const noexcept;

    const std::string& name() const { return _name; }
    void notify() const noexcept;

private:
    friend class awaiter_t;

    mutable std::atomic<void*> suspeder_awaiter {nullptr};
    mutable std::atomic<bool> notifier {false};
    const std::string _name = "UNNAMED";
};


using co_handle = std::coroutine_handle<>;
class event_t::awaiter_t{
public:
    awaiter_t(const event_t& e) : event(e) {}

    bool await_ready() const;
    bool await_suspend(co_handle handler) noexcept;
    void await_resume() noexcept {}

private:
    friend class event_t;

    const event_t& event;
    co_handle handler;
};


bool event_t::awaiter_t::await_ready() const {
    if (event.suspeder_awaiter.load() != nullptr) {
        throw std::runtime_error("More than 1 waiter");
    }

    return event.notifier;
}

bool event_t::awaiter_t::await_suspend(co_handle h) noexcept {
    handler = h;
    if (event.notifier) { return false; }
    event.suspeder_awaiter.store(this);
    return true;
}


event_t::event_t(std::string&& n)
    : _name(n)
{}

void event_t::notify() const noexcept {
    notifier = true;

    auto* waiter = static_cast<awaiter_t*>(suspeder_awaiter.load());
    if (waiter != nullptr) {
        waiter->handler.resume();
    }
}


event_t::awaiter_t event_t::operator co_await() const noexcept {
    return awaiter_t {*this};
}
