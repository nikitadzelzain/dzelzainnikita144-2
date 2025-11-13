#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    int grade;

    Student(string n, int g) : name(n), grade(g) {}

    bool operator==(const Student& other) const {
        return name == other.name;
    }

    bool operator>(const Student& other) const {
        return grade > other.grade;
    }

    bool operator<=(const Student& other) const {
        return grade <= other.grade;
    }
};

int main() {
    vector<Student> students = {
        {"Alice", 85},
        {"Bob", 90},
        {"Charlie", 78}
    };

    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.grade < b.grade; });

    for (const auto& s : students) {
        cout << s.name << " " << s.grade << endl;
    }

    return 0;
}
