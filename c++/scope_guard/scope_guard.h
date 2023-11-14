#pragma once

#include <functional>
#include <optional>
#include <tuple>
#include <type_traits>


template <typename Fn,
          typename = std::enable_if_t<std::is_same_v<void, decltype(std::declval<Fn>()())>>
>
class ScopeGuard final {
   public:
    explicit ScopeGuard(Fn&& fn) : fn_(std::forward<Fn>(fn)) {}

    ~ScopeGuard() {
        if (!dismissed_) {
            fn_();
        }
    }

    ScopeGuard(ScopeGuard&) = delete;

    ScopeGuard(ScopeGuard&& other) noexcept
        : fn_(std::move(other.fn_)), dismissed_(other.dismissed_) {}

    ScopeGuard& operator=(ScopeGuard&) = delete;

    ScopeGuard& operator=(ScopeGuard&& other) noexcept {
        if (this != other) {
            fn_(std::move(other.fn_));
            dismissed_ = other.dismissed_;
        }

        return *this;
    }

    void dismiss() { dismissed_ = true; }
    void rehire() { dismissed_ = false; }

   private:
    Fn fn_;
    bool dismissed_{false};
};

/**
 * @brief scope guard，对象销毁时执行fn
 *
 * 使用时需要用一个变量保存返回值，auto guard = makeScopeGuard(...);
 *
 * 否则makeScopeGuard(...)语句结束，fn会被直接调用
 *
 * @tparam Fn
 * @param fn void fn()
 * @return decltype(auto)
 */
template <typename Fn>
decltype(auto) makeScopeGuard(Fn&& fn) {
    // std::decay_t确保fn不是ref，避免fn为lvalue时，在外部被意外修改
    return ScopeGuard<std::decay_t<Fn>>(std::forward<std::decay_t<Fn>>(fn));
}