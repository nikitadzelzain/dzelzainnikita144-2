#include <iostream>
#include <initializer_list>

using namespace std;

class Vector2D {
public:
    double x;
    double y;

    Vector2D(double xv = 0.0, double yv = 0.0) : x(xv), y(yv) {}

    void show() const {
        cout << "(" << x << ", " << y << ")";
    }
};

class Matrix2x2 {
private:
    double data[2][2];

public:
    Matrix2x2() {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                data[i][j] = 0.0;
    }

    Matrix2x2(initializer_list<initializer_list<double>> rows) {
        int i = 0;
        for (const auto& row : rows) {
            int j = 0;
            for (const auto& val : row) {
                if (i < 2 && j < 2) data[i][j] = val;
                ++j;
            }
            ++i;
        }
        for (int r = 0; r < 2; ++r)
            for (int c = 0; c < 2; ++c)
                if (r >= i) data[r][c] = 0.0;
    }

    Matrix2x2 operator+(const Matrix2x2& rhs) const {
        Matrix2x2 res;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                res.data[i][j] = data[i][j] + rhs.data[i][j];
        return res;
    }

    Matrix2x2 operator*(const Matrix2x2& rhs) const {
        Matrix2x2 res;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) {
                res.data[i][j] = 0.0;
                for (int k = 0; k < 2; ++k)
                    res.data[i][j] += data[i][k] * rhs.data[k][j];
            }
        return res;
    }

    Vector2D operator*(const Vector2D& v) const {
        return Vector2D(
            data[0][0] * v.x + data[0][1] * v.y,
            data[1][0] * v.x + data[1][1] * v.y
        );
    }

    double operator()(int row, int col) const {
        return data[row][col];
    }

    void show() const {
        cout << data[0][0] << " " << data[0][1] << "\n"
            << data[1][0] << " " << data[1][1];
    }
};

int main() {
    Matrix2x2 m1({ {1, 2}, {3, 4} });
    Matrix2x2 m2({ {5, 6}, {7, 8} });

    cout << "m1:\n";
    m1.show();
    cout << "\n\nm2:\n";
    m2.show();
    cout << "\n\n";

    Matrix2x2 sum = m1 + m2;
    cout << "m1 + m2:\n";
    sum.show();
    cout << "\n\n";

    Matrix2x2 prod = m1 * m2;
    cout << "m1 * m2:\n";
    prod.show();
    cout << "\n\n";

    Vector2D v(2, 5);
    Vector2D res = m1 * v;
    cout << "m1 * (2, 5) = ";
    res.show();
    cout << "\n\n";

    double elem = m1(0, 1);
    cout << "m1(0, 1) = " << elem << "\n";

    return 0;
}
