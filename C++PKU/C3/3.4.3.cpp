/*
3. C++程序设计
4. 第4周
3. 编程题＃3：

补充以下的程序，二维数组类 Array2, 可能需要使用构造函数、
复制构造函数、参数列表、运算符重载、友元函数、动态分配内存、析构函数等。

写一个二维数组类 Array2, 使得下面程序的输出结果是：
0,1,2,3,
4,5,6,7,
8,9,10,11,
next
0,1,2,3,
4,5,6,7,
8,9,10,11,

// this solution pass the examination of coursera. 

*/

#include <iostream>
#include <cstring>
using namespace std;

// 在此处补充你的代码

class Array2
{
private:
    int **ptr;  // Double pointer for dynamic 2D array
    int row;    // Number of rows
    int col;    // Number of columns
public:
    Array2(int i = 0, int j = 0);  // Constructor with default parameters
    Array2(Array2 &a);             // Copy constructor, deep copying
    ~Array2();                     // Destructor
    Array2& operator=(const Array2 &a);  // Assignment operator
    int& operator()(int i, int j) { return ptr[i][j]; }  // Overloaded parentheses operator
    int* operator[](int i) { return ptr[i]; }           // Overloaded square brackets operator
};

// Constructor with parameters for initializing and allocating memory for the 2D array
Array2::Array2(int i, int j)
{
    if (i == 0 || j == 0)
    {
        ptr = NULL;  // If rows or columns are zero, set pointer to NULL
    }
    else
    {
        row = i;  // Initialize number of rows
        col = j;  // Initialize number of columns
        ptr = new int*[row];  // Allocate memory for rows
        for (int k = 0; k < row; k++)
        {
            ptr[k] = new int[col];  // Allocate memory for columns in each row
        }
    }
}

// Copy constructor for deep copying the 2D array
// initializing a new object with the contents of an existing object, 
Array2::Array2(Array2 &a)
{
    if (!a.ptr)
    {
        ptr = NULL;  // If the source object's pointer is NULL, set this object's pointer to NULL
        row = 0;
        col = 0;
        return;
    }
    else
    {
        ptr = new int*[a.row];  // Allocate memory for rows
        for (int k = 0; k < a.row; k++)
        {
            ptr[k] = new int[a.col];  // Allocate memory for columns in each row
            memcpy(ptr[k], a.ptr[k], sizeof(int) * a.col);  // Copy the data
        }
        row = a.row;
        col = a.col;
    }
}

// Destructor for freeing the allocated memory
Array2::~Array2()
{
    if (ptr)
    {
        for (int i = 0; i < row; i++)
        {
            delete[] ptr[i];  // Free memory for each row
        }
        delete[] ptr;  // Free memory for the array of row pointers
    }
}

// Assignment operator for deep copying the 2D array and freeing old memory
// assigning the contents of one already existing object to another. 
// both the source and target objects already exist to copy the contents from one to the other.
Array2& Array2::operator=(const Array2 &a)
{
    if (ptr == a.ptr)
    {
        return *this;  // Prevent self-assignment
    }
    if (a.ptr == NULL)
    {
        if (ptr)
        {
            for (int i = 0; i < row; i++)
            {
                delete[] ptr[i];  // Free old memory for each row
            }
            delete[] ptr;  // Free old memory for the array of row pointers
        }
        ptr = NULL;  // Set pointer to NULL
        row = 0;
        col = 0;
        return *this;  // Return the current object
    }
    if (row < a.row || col < a.col)
    {
        if (ptr)
        {
            for (int i = 0; i < row; i++)
            {
                delete[] ptr[i];  // Free old memory for each row
            }
            delete[] ptr;  // Free old memory for the array of row pointers
        }
        ptr = new int*[a.row];  // Allocate new memory for rows
        for (int k = 0; k < a.row; k++)
        {
            ptr[k] = new int[a.col];  // Allocate new memory for columns in each row
            memcpy(ptr[k], a.ptr[k], sizeof(int) * a.col);  // Copy the data
        }
        row = a.row;
        col = a.col;
        return *this;  // Return the current object
    }
}


int main() {
    Array2 a(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b; b = a;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}