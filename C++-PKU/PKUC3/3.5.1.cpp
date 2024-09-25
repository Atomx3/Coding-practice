/*
3. C++程序设计
5. 第5周
1. 编程题＃1：

case 1:
write a class MyString, it could store 4 object (s1,s2,s3,s4),
then we input string type argument to each object as private,
they could deal with =, + and += operators calculating 
for objects and other strings. 
at last output those object.

output:

*/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class MyString {
private:
    char* str; // Pointer to dynamically allocated string

public:
    // Default constructor without argument.
    // initializes the object with default values.
    MyString(){
        str = new char[1];
        str[0] = '\0';
    }

    // Constructor with a string argument
    MyString(const char* val) {
        if (val == nullptr) {
            str = new char[1];
            str[0] = '\0';
        } else {
            str = new char[strlen(val) + 1];
            strcpy(str, val);
        }
    }

    // Copy constructor
    MyString(const MyString& source) {
        str = new char[strlen(source.str) + 1];
        strcpy(str, source.str);
    }

    // Getter method to retrieve the stored string
    const char* getString() const {
        return str;
    }

    // Overload assignment operator =
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    // Overload + operator for concatenating two objects.
    MyString operator+(const MyString& other) const {
        MyString result;
        result.str = new char[strlen(str) + strlen(other.str) + 1];
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }
    // Overload + operator for concatenating a const char[] and an object.
    MyString operator+(const char* other) const {
        MyString result;
        result.str = new char[strlen(str) + strlen(other) + 1];
        strcpy(result.str, str);
        strcat(result.str, other);
        return result;
    }

    // Overload compound addition operator
    MyString& operator+=(const MyString& other) {
        *this = *this + other;
        return *this;
    }
   
    // Overload the << operator for MyString
    friend ostream& operator<<(ostream& os, const MyString& myStr) {
        os << myStr.str;
        return os;
    }
    // Overload the [] operator
    char &operator[](int index)
    {
        return str[index];
    }

    // Destructor
    ~MyString() {
        delete[] str;
    }

    
    // Overload the >, < operator for sorting
    bool operator>(const MyString& other) const {
        return strcmp(str, other.str) > 0;
    }
    bool operator<(const MyString& other) const {
        return strcmp(str, other.str) < 0;
    }
    // Overload the == operator for equality comparison
    bool operator==(const MyString& other) const {
        return strcmp(str, other.str) == 0;
    }

    // Overload the () operator for substring extraction
    MyString operator()(size_t start, size_t length) const {
        if (start >= strlen(str))
            return MyString(); // Return an empty string if start is out of bounds

        char* sub = new char[length + 1];
        strncpy(sub, str + start, length);
        sub[length] = '\0';

        MyString result(sub);
        delete[] sub;
        return result;
    }

};
// Overload the + operator for concatenating a const char[] 
//with a MyString (non-member function)
MyString operator+(const char* lhs, const MyString& rhs) {
    return MyString(lhs) + rhs;
}


int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( *s1 < *s2 )     return -1;
    else if( *s1 == *s2 ) return 0;
    else if( *s1 > *s2 ) return 1;
    return 0;
}

int main() {
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;

    qsort(SArray,4,sizeof(MyString), CompareString);
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
    //输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}