/**
 * From Thinking in C++, 2nd Exdition
 * Available at http://www.BruceEckel.com
 * (c) Bruce Eckel 2000
 * Copyright notice in Copyright.txt
 * A class that counts its objects
 **/
#include <iostream>
#include <string>
using namespace std;

static int objectCount = 0;     // 每次制造一个 HowMany 对象的时候加一

class HowMany {
public:
    HowMany() { objectCount++; print("HowMany()"); }
    HowMany( const HowMany& r ) {
        objectCount++;
        this->i = r.i;
        print("HowMany(HowMany)");
    }
    void set( int i ) { this->i = i; }
    void print( const string& msg = "") {
        if ( msg.size() != 0 ) cout << msg << ": ";
        cout << "objectCount = " << objectCount << ", i=" << i << endl;
    }
    ~HowMany() {
        objectCount--;
        print("~HowMany()");
    }
private:
    int i;
};

HowMany f( HowMany x ) {
    cout << &x << endl;
    cout << "begin of f" << endl;
    x.print("x argument inside f()");
    x.set(2);
    cout << "end of f" << endl;
    return x;
}

int main() {
    HowMany h;
    h.set(1);
    h.print("after construction of h");
    cout << &h << endl;
    HowMany h2 = f(h);
    h2.print( "after ctor of h2" );
    cout << &h2 << endl;
    h2.set(3);
    h.print("after call to f()");
    return 0;
}