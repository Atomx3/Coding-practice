/*
3. C++程序设计
4. 第4周
4. 编程题＃4：大整数的加减乘除

this solution could not pass the test of old version of coursera examination.

*/

#include <iostream>
#include <string>
#include <algorithm> // for reverse
using namespace std;

// Function to add two large numbers
string add(string a, string b) {
    string result = "";
    int carry = 0, sum = 0;
    int n1 = a.size(), n2 = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < max(n1, n2); i++) {
        int digit1 = (i < n1) ? a[i] - '0' : 0;
        int digit2 = (i < n2) ? b[i] - '0' : 0;
        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    if (carry) result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return result;
}

// Function to subtract two large numbers
string subtract(string a, string b) {
    // Assuming a >= b
    string result = "";
    int borrow = 0, diff = 0;
    int n1 = a.size(), n2 = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < n1; i++) {
        int digit1 = a[i] - '0';
        int digit2 = (i < n2) ? b[i] - '0' : 0;
        diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
    }
    while (result.size() > 1 && result.back() == '0') result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

// Function to multiply two large numbers
string multiply(string a, string b) {
    int n1 = a.size(), n2 = b.size();
    string result(n1 + n2, '0');
    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = n2 - 1; j >= 0; j--) {
            int sum = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = sum / 10;
            result[i + j + 1] = sum % 10 + '0';
        }
        result[i] += carry;
    }
    size_t startpos = result.find_first_not_of('0');
    if (string::npos != startpos) {
        return result.substr(startpos);
    }
    return "0";
}

// Function to divide two large numbers
string divide(string a, string b) {
    if (b == "0") return "undefined"; // Division by zero
    string result = "";
    string temp = "0";
    for (char digit : a) {
        temp += digit;
        int count = 0;
        while (temp.size() > 1 && temp[0] == '0') temp.erase(0, 1);
        while (temp.size() > b.size() || (temp.size() == b.size() && temp >= b)) {
            temp = subtract(temp, b);
            count++;
        }
        result += (count + '0');
    }
    while (result.size() > 1 && result[0] == '0') result.erase(0, 1);
    return result;
}

int main() {
    string a, b, op;
    cin >> a >> op >> b;
    if (op == "+") cout << add(a, b) << endl;
    else if (op == "-") cout << subtract(a, b) << endl;
    else if (op == "*") cout << multiply(a, b) << endl;
    else if (op == "/") cout << divide(a, b) << endl;
    return 0;
}
