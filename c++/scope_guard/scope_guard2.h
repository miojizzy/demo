#pragma once 

namespace sg2 {


class ScopeGuardImplBase { // 基类
public:
    ScopeGuardImplBase() : commit_(false) {}
    void commit() const noexcept { commit_ = true; } // commit提交方法，const的，并且noexcept
protected:
    ScopeGuardImplBase(const ScopeGuardImplBase &other) : commit_(other.commit_) { other.commit(); } // 拷贝构造函数
    ~ScopeGuardImplBase() {}
    mutable bool commit_; // mutable的
private:
    ScopeGuardImplBase &operator=(const ScopeGuardImplBase &) = delete; // 不允许赋值构造
};


template<typename Func, typename Arg>
class ScopeGuardImpl : public ScopeGuardImplBase { // 派生实现类
public:
    ScopeGuardImpl(const Func &func, Arg &arg) : func_(func), arg_(arg) {}
    ~ScopeGuardImpl() { if (!commit_) func_(arg_); } // 析构类
private:
    const Func &func_; // 方法成员变量，传入回滚方法。const
    Arg &arg_;
};


template<typename Func, typename Arg>
ScopeGuardImpl<Func, Arg> makeScopeGuard(const Func &func, Arg &arg) {
    return ScopeGuardImpl<Func, Arg>(func, arg);

}

} // namespace sg2