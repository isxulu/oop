#include <iostream>
using namespace std;

class V {
private:
    int i;
};

void mswap( float a, float b ) {
    float t = a;
    a = b;
    b = t;
    cout << "mswap(float)" << endl;
}

template < class T >
void mswap( T a, T b ) {
    T t = a;
    a = b;
    b = t;
    cout << "mswap(T)" << endl;
}

int main() {
    // int a = 5;
    // int b = 6;
    // mswap( a, b );
    // double c = 5.0;
    // double d = 6.0;
    // mswap( c, d );
    // V e, f;
    // mswap( e, f );
    mswap( 1.0, 2.0 );
    mswap( 1, 2 );
    mswap( 1, 2.0 );
    return 0;
}