#include <iostream>
using namespace std;

class Date {
private:
    int day;
public:
    Date( int d ): day(d) {}
    inline int getDay() const;
    inline int getDay();
};

inline int Date::getDay() const {
    cout << "const getDay()" << endl;
    return day;
}
inline int Date::getDay() {
    day++;
    cout << "this getDay()" << endl;
    return day;
}

int main() {
    Date d(10);
    const Date dd(20);
    cout << d.getDay() << endl;
    cout << dd.getDay() << endl;
}