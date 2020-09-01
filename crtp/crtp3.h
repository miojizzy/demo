#ifndef __H_CRTP3__
#define __H_CRTP3__
#include <stdio.h>
namespace CRTP3{



class AbsBase{ //抽象层
public:
    virtual ~AbsBase(){}; //虚析构函数
    virtual void func() = 0; //指定了子类要实现的接口
};

template<typename D>
class Base : public AbsBase{
public:
    Base(){};
    ~Base(){printf("base<derived>::delete\n");};
    
    // 其他不再抽象层中的虚函数 还是原方法加

private:
    inline D* _derived(){return static_cast<D*>(this);};
};

class Derived : public Base<Derived>{ 
public:
    Derived(){};
    ~Derived(){printf("derived::delete\n");};
    
    void func(){ // 子类的实现函数 直接由抽象类而来
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
    delete ptr;
};


};

#endif
