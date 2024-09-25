/*
3. C++程序设计
4. 第4周
4. 编程题＃4：大整数的加减乘除
我已经有了“+，-，*，/” 四种运算符函数重载，用于相应的“+，-，*，/”计算。
以下是用于除法运算的部分程序，其他三种暂时做了隐藏。
可能需要“<, ==”等其他类型的运算符配合计算，如何尽可能减少
其他类运算符的使用？请精简代码，尽可能重复使用各种运算符。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <cmath>
using namespace std;

class BigInt {
private:
    vector<int> num;
    bool is_negative = false;  // 新增：表示这个 BigInt 对象是否为负数

public:
    BigInt(string s) {
        for (int i = s.size() - 1; i >= 0; i--) {
            num.push_back(s[i] - '0');
        }
    }

    bool operator==(const BigInt& b) const {
        return num == b.num;
    }

    bool operator<=(const BigInt& b) const {
        return num.size() <= b.num.size();
    }
    bool operator<(const BigInt& b) const {
        if (num.size() != b.num.size()) {
            return num.size() < b.num.size();
        }
        for (int i = num.size() - 1; i >= 0; --i) {
            if (num[i] != b.num[i]) {
                return num[i] < b.num[i];
            }
        }
        return false;  // 如果两个数相等，返回 false
    }
    
    // argument b is past to operator function.
    BigInt operator+(const BigInt& b) const {
        BigInt res("");
        // a is stored in the object num
        // a call the operator + overloading
        res.num.resize(max(num.size(), b.num.size()));
        int carry = 0;
        for (int i = 0; i < res.num.size(); i++) {
            if (i < num.size()) carry += num[i];
            if (i < b.num.size()) carry += b.num[i];
            res.num[i] = carry % 10;
            carry /= 10;
        }
        if (carry) res.num.push_back(carry);
        return res;
    }
    
    BigInt operator-(const BigInt& b) const {
        if (*this < b) {
            BigInt res = b - *this;  // 如果 b 大于 a，我们交换 a 和 b，然后进行减法操作
            res.is_negative = true;  // 然后我们将结果标记为负数
            return res;
        }
        BigInt res(*this);
        res.num.resize(max(num.size(), b.num.size()));
        int carry = 0;
        for (int i = 0; i < res.num.size(); i++) {
            carry = 0;
            if (i < res.num.size()) carry += res.num[i];
            if (i < b.num.size()) carry -= b.num[i];
            if (carry < 0) {
                carry += 10;
                if (i + 1 < res.num.size()) res.num[i + 1]--;  // 在新对象上借位
            }
            res.num[i] = carry;
        }
        // Remove leading zeros
        while (res.num.size() > 1 && res.num.back() == 0) {
            res.num.pop_back();
        }
        return res;
    }

    BigInt operator*(const BigInt& b) const {
    BigInt res("0");
    res.num.resize(num.size() + b.num.size());
    for (int i = 0; i < num.size(); i++) {
        for (int j = 0; j < b.num.size(); j++) {
            res.num[i + j] += num[i] * b.num[j];
            if (res.num[i + j] >= 10) {
                res.num[i + j + 1] += res.num[i + j] / 10;
                res.num[i + j] %= 10;
            }
        }
    }
        // Remove leading zeros
        while (res.num.size() > 1 && res.num.back() == 0) {
            res.num.pop_back();
        }
        return res;
    }
    
    BigInt operator/(const BigInt& b) const {
        if (b == BigInt("0")) {
            throw std::overflow_error("Division By Zero Exception.");
        }

        BigInt quotient("0");
        BigInt dividend(*this);

        // Perform long division
        while (b <= dividend) {
            int factor = 0;
            while (b * BigInt(std::to_string(factor + 1)) <= dividend) {
                factor++;
            }
            quotient = quotient * BigInt("10") + BigInt(std::to_string(factor));
            dividend = dividend - (b * BigInt(std::to_string(factor)));
        }

        // Adjust for rounding (consider negative remainder)
        if (2 * std::abs(dividend) >= b) {
            quotient = quotient + BigInt("1");
        }

        return quotient;
    }


    friend ostream& operator<<(ostream& out, const BigInt& x) {
        if (x.is_negative) {  // 如果这个 BigInt 对象是负数，我们在输出之前添加一个负号
            out << '-';
        }
        for (int i = x.num.size() - 1; i >= 0; i--) {
            out << x.num[i];
        }
        return out;
    }
};

int main() {
    string a, b;
    char op;
    cin >> a >> op >> b;
    BigInt num1(a), num2(b);
    switch (op) {
        case '+':
            cout << num1 + num2 << endl;
            break;
        // deal with negative int.
        case '-':
            cout << num1 - num2 << endl;
            break;
        case '*':
            cout << num1 * num2 << endl;
            break;
        case '/':
            cout << num1 / num2 << endl;
            break;
    }
    return 0;
}
