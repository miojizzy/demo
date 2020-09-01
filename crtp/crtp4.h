#ifndef __H_CRTP4__
#define __H_CRTP4__
#include <stdio.h>
namespace CRTP4{


template<typename D>
class Base{
public:
    Base(){};
    ~Base(){printf("base<derived>::delete\n");};

    void func(){_derived()->func_impl();};
    void func_impl(){printf("ERROR FUNC!");};

    void destroy(){delete _derived();};

// 原继承方式
//protected:
//    int _value;
// 新方式：私有化加友元
private:
    int _value; // 私有化
    friend D;   // 声明子类为友元类

private:
    inline D* _derived(){return static_cast<D*>(this);};
};

class Derived : public Base<Derived>{ 
public:
    Derived(){};
    ~Derived(){printf("derived::delete\n");};
    
    void func_impl(){
        printf("value:%d\n", _value);
    };
};

/* 错误的继承方式 子类与传入的子类类型不同
class Derived1 : public Base<Derived>{ 
public:
    Derived1(){};
    ~Derived1(){printf("derived1::delete\n");};
    
    void func_impl(){
        printf("value:%d\n", _value);
    };
};
*/

template<typename D>
void global_virtual_func(Base<D>* p){
    p->func();
};


void test(){
//    Derived d;
    Base<Derived>* ptr;
    ptr = new Derived();
    ptr->func();
    global_virtual_func(ptr);
    ptr->destroy();

    //在Derived1继承传错子类的情况下 只有在显式的写出这里 才会编译出问题
    //Base<Derived1>* p = new Derived1(); 
};


};

#endif
