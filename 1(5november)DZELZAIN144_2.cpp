#include <iostream>
using namespace std;

class Number {
private:
    int value;

public:
    Number(int v = 0) : value(v) {}

    Number operator+(const Number& other) const {
        return Number(value + other.value);
    }

    Number operator-(const Number& other) const {
        return Number(value - other.value);
    }

    Number operator*(const Number& other) const {
        return Number(value * other.value);
    }

    friend ostream& operator<<(ostream& os, const Number& num) {
        os << num.value;
        return os;
    }
};

int main() {
    Number a(5), b(3);

    Number c = a + b;
    Number d = a - b;
    Number e = a * b;

    cout << c << endl;
    cout << d << endl;
    cout << e << endl;

    return 0;
}
