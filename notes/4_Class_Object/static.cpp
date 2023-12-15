#include <iostream>
using namespace std;

class Date {
private:
    int day;
    static int kk;          // static member variable
public:
    Date( int d ): day(d) {
        cout << "Date(" << day << ")\n";
    }
    ~Date() {
        cout << "~Date(" << day << ")\n";
    }
    int getkk() { return kk; }
    void setkk( int k ) { kk = k; }
};

void f() {
    static Date d(10);
    cout << "f()" << endl;
}

int Date::kk = 0;

Date gd0(0);
Date gd1(1);

int main () {
    // cout << "1\n"; f();
    // cout << "2\n"; f();
    // cout << "3\n";
    Date d(0);
    cout << d.getkk() << endl;
    d.setkk(10);
    cout << gd1.getkk() << endl;
    // cout << Date::kk() << endl;
}

Date gd2(2);