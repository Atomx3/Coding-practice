/*
3. C++ Programming
7. Module 7
1. Programming Assignment #1

This is a legacy version of the code that supports C++ compilers before 2015.
Instead of using operator(), it implements operator[] to support multi-dimensional array access syntax.

*/
#include <iostream>
using namespace std;

// Forward declarations of template classes to resolve circular dependencies
template <typename T> class CArray1D;
template <typename T> class CArray2D;
template <typename T> class CArray3D;

// CArray1D: Represents a 1-dimensional array view into the 3D array data
// Handles the innermost dimension access
template <typename T>
class CArray1D {
public:
    // Constructor: initializes a 1D array view
    // @param dim3: size of the innermost dimension
    // @param data: pointer to the shared data array
    // @param offset: starting position in the data array
    CArray1D(int dim3, T* data, int offset)
        : dim3_(dim3), data_(data), offset_(offset) {}

    // Overloaded subscript operator for accessing array elements
    // @param i: index into the 1D array
    // @return: reference to the element at position i
    T& operator[](int i) {
        return data_[offset_ + i];
    }

private:
    int dim3_;    // Size of the innermost dimension
    T* data_;    // Pointer to the shared data array
    int offset_; // Starting position in the data array
};

// CArray2D: Represents a 2-dimensional array view into the 3D array data
// Returns CArray1D for the next level of array access
template <typename T>
class CArray2D {
public:
    // Constructor: initializes a 2D array view
    // @param dim2: size of the middle dimension
    // @param dim3: size of the innermost dimension
    // @param data: pointer to the shared data array
    // @param offset: starting position in the data array
    CArray2D(int dim2, int dim3, T* data, int offset)
        : dim2_(dim2), dim3_(dim3), data_(data), offset_(offset) {}

    // Overloaded subscript operator for accessing 2D array elements
    // @param i: index into the middle dimension
    // @return: CArray1D object representing a 1D slice of the array
    CArray1D<T> operator[](int i) {
        return CArray1D<T>(dim3_, data_, offset_ + i * dim3_);
    }

private:
    int dim2_;    // Size of the middle dimension
    int dim3_;    // Size of the innermost dimension
    T* data_;    // Pointer to the shared data array
    int offset_; // Starting position in the data array
};

// CArray3D: Main class that manages the 3-dimensional array
// Allocates and deallocates the continuous memory block for the entire array
template <typename T>
class CArray3D {
public:
    // Constructor: creates a 3D array
    // @param dim1: size of the outermost dimension
    // @param dim2: size of the middle dimension
    // @param dim3: size of the innermost dimension
    CArray3D(int dim1, int dim2, int dim3)
        : dim1_(dim1), dim2_(dim2), dim3_(dim3) {
        data_ = new T[dim1_ * dim2_ * dim3_]; // Allocate continuous memory block
    }

    // Destructor: deallocates the dynamically allocated memory
    ~CArray3D() {
        delete[] data_;
    }

    // Overloaded subscript operator for accessing 3D array elements
    // @param i: index into the outermost dimension
    // @return: CArray2D object representing a 2D slice of the array
    CArray2D<T> operator[](int i) {
        return CArray2D<T>(dim2_, dim3_, data_, i * dim2_ * dim3_);
    }

private:
    int dim1_;    // Size of the outermost dimension
    int dim2_;    // Size of the middle dimension
    int dim3_;    // Size of the innermost dimension
    T* data_;    // Pointer to the dynamically allocated data array
};

int main() {
    // Create a 3D array with dimensions 3x4x5
    CArray3D<int> a(3, 4, 5);
    int No = 0;

    // Initialize the array with sequential numbers
    // The nested loops demonstrate how to access elements using operator[]
    for (int i = 0; i < 3; ++i)        // Outermost dimension
        for (int j = 0; j < 4; ++j)    // Middle dimension
            for (int k = 0; k < 5; ++k) // Innermost dimension
                a[i][j][k] = No++;     // Assign and increment

    // Print all elements to verify correct initialization and access
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 5; ++k)
                cout << a[i][j][k] << ",";

    return 0;
}