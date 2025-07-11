/*
3. C++程序设计
4. 第4 module
3. 编程题＃3：

this solution could not pass the test of old version of coursera examination.

*/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Array2
{
	private:
		int **ptr;
		int row;
		int col;
	public:
		Array2(int i = 0, int j = 0);
		Array2(Array2 &a);
		~Array2();
		Array2& operator=(const Array2 &a);
		int& operator()(int i, int j) { return ptr[i][j]; }
		int* operator[](int i) { return ptr[i]; }
};

Array2::Array2(int i, int j)
{
	if (i == 0 || j == 0)
	{
		ptr = NULL;
	}
	else
	{
		row = i;
		col = j;
		ptr = new int*[row];
		for (int k = 0; k < row; k++)
		{
			ptr[k] = new int[col];
		}

	}
}

Array2::Array2(Array2 &a)
{
	if (!a.ptr)
	{
		ptr = NULL;
		row = 0;
		col = 0;
		return;
	}
	else
	{
		ptr = new int*[a.row];
		for (int k = 0; k < a.row; k++)
		{
			ptr[k] = new int[a.col];
			memcpy(ptr[k], a.ptr[k], sizeof(int)*a.col);
		}
		row = a.row;
		col = a.col;
	}
}

Array2::~Array2()
{
	if (ptr)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] ptr[i];
		}
		delete[] ptr;
	}
}

Array2& Array2::operator=(const Array2 &a) {
    if (this == &a) {
        return *this;
    }

    if (ptr) {
        for (int i = 0; i < row; i++) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }

    row = a.row;
    col = a.col;

    if (!a.ptr) {
        ptr = nullptr;
    } else {
        ptr = new int*[row];
        for (int k = 0; k < row; k++) {
            ptr[k] = new int[col];
            memcpy(ptr[k], a.ptr[k], sizeof(int) * col);
        }
    }

    return *this;  // Ensure the function returns *this in all control paths
}

int main()
{
	Array2 a(3, 4);
	int i, j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 4; j++)
		{
			a[i][j] = i * 4 + j;
		}
	}
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 4; j++)
		{
			cout << a(i, j) << ",";
		}
		cout << endl;
	}

	cout << "next" << endl;

	Array2 b;
	b = a;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 4; j++)
		{
			cout << b[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}