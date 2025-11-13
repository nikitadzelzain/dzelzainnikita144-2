#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

class Shape {
protected:
    string name;
    string color;
public:
    Shape(string name, string color) : name(name), color(color) {}
    virtual ~Shape() {}
    virtual double area() const = 0;
    virtual void draw(ostream& os) const = 0;

    friend ostream& operator<<(ostream& os, const Shape& s) {
        os << "Figure: " << s.name
            << ", color: " << s.color
            << ", area: " << fixed << setprecision(2) << s.area();
        return os;
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(string name, string color, double r)
        : Shape(name, color), radius(r) {
    }

    double area() const override {
        const double PI = acos(-1.0);
        return PI * radius * radius;
    }

    void draw(ostream& os) const override {
        os << "[Circle] name=" << name
            << ", color=" << color
            << ", radius=" << radius
            << ", area=" << fixed << setprecision(2) << area() << "\n";
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(string name, string color, double w, double h)
        : Shape(name, color), width(w), height(h) {
    }

    double area() const override { return width * height; }

    void draw(ostream& os) const override {
        os << "[Rectangle] name=" << name
            << ", color=" << color
            << ", width=" << width
            << ", height=" << height
            << ", area=" << fixed << setprecision(2) << area() << "\n";
    }
};

void printInfo(const Shape& s) {
    cout << s << "\n";
}

int main() {
    Circle c("C1", "red", 1.0);
    Rectangle r("R", "black", 10.4, 20.6);
    Shape* shapes[2] = { &c, &r };

    for (int i = 0; i < 2; ++i)
        printInfo(*shapes[i]);

    return 0;
}
