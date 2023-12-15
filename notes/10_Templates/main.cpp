#include "Vector.h"
#include <iostream>
using namespace std;

int main() {
    Vector<int> v(100);
    v[0] = 10;
    cout << v[0] << endl;
}