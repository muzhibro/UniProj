#include <iostream>
#include <stdexcept>
using namespace std;

class Integer {
private:
    int value;

public:
    Integer(int num) : value(num) {} // 整数类的构造函数，用于初始化整数值

    int getValue() const {
        return value;
    }

    void display() const {
        cout << value;
    }
};

class Fraction : public Integer { // 分数类从整数类派生，继承整数值的功能
private:
    int numerator; // 分子
    int denominator; // 分母

public:
    Fraction(int num, int den) : Integer(num), numerator(num), denominator(den) {
        // 分数类的构造函数，用于初始化分子和分母
        if (denominator == 0) {
            throw invalid_argument("Error: Denominator cannot be zero.");
        }
    }

    Fraction() : Integer(0), numerator(0), denominator(1) {
        // 默认构造函数，将分子和分母初始化为0和1
    }

    void display() const {
        cout << numerator << "/" << denominator;
    }

    Fraction operator+(const Fraction& other) const {
        // 加法运算符重载，实现两个分数的相加
        int commonDenominator = denominator * other.denominator;
        int commonNumerator = numerator * other.denominator + other.numerator * denominator;
        return Fraction(commonNumerator, commonDenominator);
    }

    Fraction operator-(const Fraction& other) const {
        // 减法运算符重载，实现两个分数的相减
        int commonDenominator = denominator * other.denominator;
        int commonNumerator = numerator * other.denominator - other.numerator * denominator;
        return Fraction(commonNumerator, commonDenominator);
    }

    Fraction operator*(const Fraction& other) const {
        // 乘法运算符重载，实现两个分数的相乘
        int productNumerator = numerator * other.numerator;
        int productDenominator = denominator * other.denominator;
        return Fraction(productNumerator, productDenominator);
    }

    Fraction operator/(const Fraction& other) const {
        // 除法运算符重载，实现两个分数的相除
        int quotientNumerator = numerator * other.denominator;
        int quotientDenominator = denominator * other.numerator;
        return Fraction(quotientNumerator, quotientDenominator);
    }

    void simplify() {
        // 化简分数，将分数化简为最简形式
        int gcd = getGCD(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

private:
    int getGCD(int a, int b) const {
        // 辅助函数，计算最大公约数
        if (b == 0)
            return a;
        return getGCD(b, a % b);
    }
};

int main() {
    int num1, num2, den1, den2;
    cout << "Enter the numerator and denominator of the first fraction: ";
    cin >> num1 >> den1;
    cout << "Enter the numerator and denominator of the second fraction: ";
    cin >> num2 >> den2;

    try {
        Fraction fraction1(num1, den1); // 创建第一个分数对象
        Fraction fraction2(num2, den2); // 创建第二个分数对象
        int choice;
    cout << "Menu:\n";
    cout << "1. Add fractions\n";
    cout << "2. Subtract fractions\n";
    cout << "3. Multiply fractions\n";
    cout << "4. Divide fractions\n";
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    Fraction result;
    switch (choice) {
        case 1:
            result = fraction1 + fraction2; // 分数相加
            cout << "Result: ";
            result.display();
            break;
        case 2:
            result = fraction1 - fraction2; // 分数相减
            cout << "Result: ";
            result.display();
            break;
        case 3:
            result = fraction1 * fraction2; // 分数相乘
            cout << "Result: ";
            result.display();
            break;
        case 4:
            if (fraction2.getValue() != 0) {
                result = fraction1 / fraction2; // 分数相除
                cout << "Result: ";
                result.display();
            } else {
                throw runtime_error("Error: Division by zero is not allowed.");
            }
            break;
        default:
            throw invalid_argument("Invalid choice.");
    }
} catch (const exception& e) {
    cout << e.what() << endl; // 输出捕获到的异常信息
}

return 0;

}