#include <iostream>
#include <vector>
using namespace std;

class Base {
private:
    int alpha = 1;
public:
    int blphb = 2;
    Base( int k ) : alpha(k) {
        cout << "Base()\n";
    }
    ~Base() {
        cout << "~Base()\n";
    }
    void prt() {
        cout << alpha << " " << blphb << endl;
    }
};

class Derived : public Base{
private:
    int alpha = 666;
    int clphc = 3;
public:
    Derived() : Base(9) {
        cout << "Derived()\n";
    }
    ~Derived() {
        cout << "~Derived()\n";
    }
    void prt() {
        Base::prt();
        cout << alpha << endl;      // Can access alpha of Base class if it is protected
        cout << blphb << endl;
        cout << clphc << endl;
    }
};

class Eerived : public Derived {
public:
    void pp() {
        // cout << alpha << endl;      // Can access alpha of Base class if it is protected
    }
};

int main() {
    /* See the size of the Base class and Derived class */
    cout << "The size of Base class, namely the number of int in it is: " << sizeof(Base) << endl;          // 2 integer
    cout << "The size of Derived class, namely the number of int in it is: " << sizeof(Derived) << endl;    // 3 integer

    /* The order of constructor */
    Derived td;
    td.prt();
    
    cout << endl;
    int *r = (int*)&td;
    for ( int i = 0; i < sizeof(Derived) / sizeof(int); i++ ) {
        cout << r[i] << endl;
    }
    // Eerived ed;
    // ed.pp();

    // /* See all the ints in Derived class */
    // Base b;
    // int *p = (int*)&b;
    // cout << p[0] << " " << p[1] << endl;
    // // b.prt();
    // Derived d;
    // p = (int*)&d;
    // cout << p[0] << " " << p[1] << " " << p[2] << endl;
    // // d.prt();

    // /* A base class's pointer to a derived class onbject */
    // Base *q = &d;
    // q->prt();
    return 0;
}