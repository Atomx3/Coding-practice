/*
期末考试选择题解析

在 C++ 中，虚函数表（vtable）是用于支持动态多态性的一个机制。
每个含有虚函数的类都有一个虚函数表。如果类中有虚函数，
编译器会在对象的内存布局中添加一个指向虚函数表的指针。
纯虚函数是一种特殊的虚函数，它没有实现，必须在派生类中被重写。
包含纯虚函数的类称为抽象类，不能直接实例化。

1. 虚函数：
在代码中，任何使用 virtual 关键字声明的成员函数都是虚函数。
在您的程序示例中，Shape 类中的 area() 函数和析构函数 ~Shape() 都被声明为虚函数。

2. 虚函数表 (vtable)：
虚函数表是一个编译器在编译时为每个含有虚函数的类或对象生成的隐藏表。
它包含了指向类的虚函数的指针。
在您的程序中，Shape 类有一个虚函数表，其中包含了指向 area() 函数和析构函数的指针。
当创建 Circle 或 Rectangle 对象时，
它们各自的虚函数表会被设置为指向它们重写的 area() 函数和析构函数。

3. 纯虚函数：
使用 = 0 语法声明的函数是纯虚函数。
它在基类中没有实现，必须在派生类中提供实现。
Shape 类的 area() 函数就是一个纯虚函数。

4. 抽象类：
包含纯虚函数的类称为抽象类，不能被实例化。

程序示例，展示虚函数表、虚函数、纯虚函数和抽象类的用法：

*/

#include <iostream>

// 抽象类
class Shape {
public:
    // 纯虚函数，用于计算面积
    virtual double area() const = 0;

    // 虚析构函数
    virtual ~Shape() {}
};

// 派生类：圆形
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // 派生类重写基类 Shape 的 area() 函数时，它们实现了虚函数
    // 重写纯虚函数，计算圆形的面积
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

// 派生类：矩形
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    // 重写纯虚函数，计算矩形的面积
    double area() const override {
        return width * height;
    }
};

int main() {
    // 不能直接创建抽象类的实例
    // Shape shape; // 错误：不能实例化抽象类

    // 创建派生类的实例
    Circle circle(5);
    Rectangle rectangle(4, 6);

    // 使用指向基类的指针数组来调用派生类的函数
    Shape* shapes[2] = {&circle, &rectangle};

    // 通过基类指针调用重写的函数
    for (int i = 0; i < 2; ++i) {
        std::cout << "Shape " << i + 1 << " area: " << shapes[i]->area() << std::endl;
    }

    return 0;
}
