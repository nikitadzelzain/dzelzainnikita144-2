#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imaginary;

    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imaginary * other.imaginary,
            real * other.imaginary + imaginary * other.real
        );
    }

    Complex operator~() const {
        return Complex(real, -imaginary);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << " + " << c.imaginary << "i";
        return os;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);

    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    Complex conj = ~c1;

    cout << sum << endl;
    cout << diff << endl;
    cout << prod << endl;
    cout << conj << endl;

    return 0;
}
