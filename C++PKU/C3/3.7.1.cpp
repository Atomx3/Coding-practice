/*
3. C++程序设计
7. module 7
1. 编程题＃1：
类里面可以定义类, 类模版里面也可以定义类模版
before we add inner class and inner class template 
the program has realize the same output.
so inner class and it's template are some what unnecessary.

这是新版本的程序，符合现代C++编译器标准的程序。它使用了以下现代C++特性：

1. 使用 operator() 重载运算符来实现多维数组访问，这是一种更现代和灵活的方式，允许自定义索引操作符的行为。
2. 使用了类内初始化列表（constructor initializer list）来初始化成员变量。

*/

#include <iostream>
using namespace std;

template <typename T>
class CArray3D {
public:
    CArray3D(int dim1, int dim2, int dim3)
        : dim1_(dim1), dim2_(dim2), dim3_(dim3) {
        data_ = new T[dim1_ * dim2_ * dim3_];
    }

    ~CArray3D() {
        delete[] data_;
    }

    // Access operator to get a reference to the element at (i, j, k)
    T& operator()(int i, int j, int k) {
        return data_[i * dim2_ * dim3_ + j * dim3_ + k];
    }

    // inner class
    class Inner {
    public:
        Inner(T initData) : data(initData) {}
        
        T getData() {
            return data; 
        }
    private:
        T data;
    };

    // inner class template
    template <typename U>
    class InnerTemplate {
    public:
        InnerTemplate(U initX) : x(initX) {}
        U getX() {
            return x;
        }
    private:
        U x;  
    };

private:
    int dim1_;
    int dim2_;
    int dim3_;
    T* data_;
};

int main() {
    CArray3D<int> a(3, 4, 5);
    int No = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 5; ++k)
                a(i, j, k) = No++;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 5; ++k)
                cout << a(i, j, k) << ",";

    return 0;
}