#include <iostream>
#include <string>
using namespace std;

class Fi {
public:
    Fi() { cout << "Fi()" << endl; }
};

class Fee {
    int i;
    char* buf;
public:
    Fee( int k ):i(k) { cout << "Fee(int)" << endl; buf = new char(i); }
    Fee( const Fi& ) { cout << "Fee(Fi)" << endl; }
    Fee( const Fee& that ) {
        i = that.i;
        buf = new char(i);
    }
    ~Fee() { delete[] buf; }
    Fee& operator=( const Fee& that ) {
        i = that.i;
        delete[] buf;
        buf = new char(i);
        cout << "=()" << endl;
        return *this;
    }
};

int main() {
    Fee fee = 1;    // Fee(int)
    Fi fi;
    Fee fum = fi;   // Fee(Fi)
    fum = fi;
}

/** The output:
 *  Fee(int)
 *  Fi()
 *  Fee(Fi)
 *  Fee(Fi)  
 **/