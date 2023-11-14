#ifndef __H_CRTP_DEMO__
#define __H_CRTP_DEMO__
#include <stdio.h>
namespace CRTP_DEMO{

template<typename D>
class Base{ // 1.基类转为模版
public:
    Base(){};
    virtual ~Base(){}; // 2.析构函数为虚函数

    void func(){_derived()->func_impl();};
    void func_impl(){};                     // 3.interface implement 分离, 注意调用


private:
    inline D* _derived(){return static_cast<D*>(this);};    // 4.强转为子类
    friend D;                                               // 5.友元权限

private:
    int _value;  // 6.protected 私有化

};

class Derived : public Base<Derived>{  // 1.
public:
    Derived(){};
    ~Derived(){};
    
    void func_impl(){                   //3.
        printf("value:%d\n", _value);
    };
};


template<typename D>            
void global_virtual_func(Base<D>* p){ // 7.参数用到基类的全局函数 变为模版
    p->func();
};


void test(){
    Base<Derived>* ptr;
    ptr = new Derived();
    ptr->func();
    global_virtual_func(ptr);

};


};

#endif
