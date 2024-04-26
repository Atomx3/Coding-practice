/*
1. 运算符“::”是不能被重载的：
运算符 :: 是作用域解析运算符，它用于指定一个成员属于哪个类或命名空间，
这个运算符不能被重载。

2. 运算符重载函数的参数的个数等于该运算符的操作数的个数减一：
对于成员函数形式的运算符重载，this 指针隐式地作为第一个操作数，
因此参数数量是操作数减一。
本案例解说：
+ 运算符被重载为 Number 类的成员函数。
它只有一个参数 other，因为第一个操作数 num1 是通过 this 指针隐式传递的。
所以，num1 + num2 在内部被转换为 num1.operator+(num2)，
其中 num1 是 this 指针指向的对象，而 num2 是作为参数传递的。

3. 同一个运算符只能被重载一次：
但可以有不同版本，接受不同类型的参数。

4. 运算符 ++ 可以被重载为成员函数或全局函数。
这里作为案例展示，同时配置了2个（成员，全局）函数都用于 Number类Operator+ 运算符重载。
当尝试使用 num1 + num2 时，编译器无法确定使用哪个重载版本；
将出现报错，实际程序中，必须删除一个；
通常，我们会保留成员函数形式的重载，因为它可以直接访问类的私有成员。

展示运算符重载的正确用法：

*/


#include <iostream>

class Number {
private:
    int value;

public:
    // 构造函数
    Number(int v) : value(v) {}

     // 添加一个获取 value 的成员函数
    int getValue() const {
        return value;
    }


    // 重载前缀 "++" 运算符作为成员函数
    Number& operator++() {
        ++value;
        return *this;
    }

    // 重载后缀 "++" 运算符作为成员函数
    Number operator++(int) {
        Number temp = *this;
        ++*this;
        return temp;
    }

    // 重载 "+" 运算符作为成员函数，参考以上注释中“本案例解说”
    // 参数个数为1，因为第一个操作数是隐式的 "this" 对象
    Number operator+(const Number& other) const {
        return Number(value + other.value);
    }

    // 显示值的函数
    void display() const {
        std::cout << "Value: " << value << std::endl;
    }
};

// 实例：重载 "+" 运算符作为全局函数
Number operator+(const Number &a, const Number &b)
{
    return Number(a.getValue() + b.getValue());
}

int main() {
    Number num1(10);
    Number num2(20);

    // 使用重载的 "++" 运算符
    ++num1;
    num1++;

    // 使用重载的 "+" 运算符，参考以上注释中“本案例解说”
    Number num3 = num1 + num2; // 等同于 num1.operator+(num2)

    num1.display();
    num2.display();
    num3.display();// 输出 "Value: 30"

    return 0;
}

