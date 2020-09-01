#ifndef __H_CRTP2__
#define __H_CRTP2__
#include <stdio.h>
namespace CRTP2{


template<typename D>
class Base{
public:
    Base(){};
    ~Base(){printf("base<derived>::delete\n");};

    void func(){ // 1.本应该为虚函数的func
        printf("B::func\n");
        _derived()->func_impl(); // 1.调用子类的实现函数
    };
    void func_impl(){}; // 1.默认的实现

    void destroy(){delete _derived();}; // 2.实现子类的析构

private:    //3.私有化的强转函数
    inline D* _derived(){return static_cast<D*>(this);};
};

class Derived : public Base<Derived>{ 
public:
    Derived(){};
    ~Derived(){printf("derived::delete\n");};
    
    void func_impl(){ // 1.子类的实现函数，func不动
        printf("D::func\n");
    };

};

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
    ptr->destroy(); // 2.要显示的调用来析构子类
};


};

#endif
