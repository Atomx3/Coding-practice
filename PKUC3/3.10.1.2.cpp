/*
示例代码，用于解释C++中的抽象类、虚析构函数、this指针和const成员函数

1. 抽象类可以包含非纯虚函数：
抽象类是至少包含一个纯虚函数的类，但并不要求所有成员函数都是纯虚函数，

2. 析构函数可以是虚函数：
如果一个类被设计为基类，那么它的析构函数通常应该是虚函数，
这样在通过基类指针删除派生类对象时，可以确保调用正确的析构函数。

3. const成员函数中可以使用this指针：
在const成员函数中，this指针是指向常量的指针，
这意味着你不能通过this指针修改对象的状态，但你仍然可以使用this指针。

4. 在虚函数中能使用this指针：
在虚函数中完全可以使用this指针。
this指针在虚函数中的行为和在非虚函数中一样，它指向调用对象。


*/


#include <iostream>

// 抽象类示例
class AbstractClass {
public:
    // 纯虚函数 - 必须在派生类中实现
    virtual void pureVirtualFunction() = 0;

    // 抽象类也可以有非纯虚函数
    void nonPureVirtualFunction() {
        std::cout << "这是一个非纯虚函数。\n";
    }

    // 虚析构函数
    virtual ~AbstractClass() {
        std::cout << "AbstractClass 的析构函数。\n";
    }
};

// 派生类
class DerivedClass : public AbstractClass {
public:
    // 实现纯虚函数
    void pureVirtualFunction() override {
        std::cout << "这是一个纯虚函数的实现。\n";
    }

    // 析构函数也可以是虚函数
    virtual ~DerivedClass() {
        std::cout << "DerivedClass 的析构函数。\n";
    }
};

// const 成员函数示例
class ConstMemberFunctionClass {
public:
    int value;
    // 构造函数，初始化对象的成员变量，无返回值类型和返回值
    // 可以有参数，也可无参数，即默认构造函数
    ConstMemberFunctionClass(int v) : value(v) {}

    // const 成员函数
    void constMemberFunction() const {
        // 在 const 成员函数中使用 this 指针
        std::cout << "const 成员函数中的 this 指针指向的值: " << this->value << "\n";
    }
};

int main() {
    // 抽象类和虚析构函数
    AbstractClass* abstract = new DerivedClass();
    abstract->pureVirtualFunction();
    abstract->nonPureVirtualFunction();
    delete abstract; // 调用虚析构函数

    // const 成员函数
    ConstMemberFunctionClass constMember(10);
    constMember.constMemberFunction();

    return 0;
}
