#ifndef __H_CRTP1__
#define __H_CRTP1__
#include <stdio.h>
namespace CRTP1{


template<typename D> //这里的D是子类
class Base{
public:
    Base(){};
    ~Base(){};

    void func(){ //本应该为虚函数的func
        printf("B::func\n");
        static_cast<D*>(this)->func(); //强转成子类指针来调用子类的函数
    };
};

class Derived : public Base<Derived>{ // 注意继承时候要加自己
public:
    Derived(){};
    ~Derived(){};
    
    void func(){
        printf("D::func\n");
    };

};

template<typename D>
void global_virtual_func(Base<D>* p){ // 全局 虚函数 从普通函数编程了模版函数
    p->func();
};



void test(){
    Derived d;
    Base<Derived>* ptr;
    ptr = new Derived();
    ptr->func();
    global_virtual_func(ptr);
};


};

#endif
