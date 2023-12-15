#include <iostream>
using namespace std;

#include "./String.h"

int main() {
    cout << "hello\n";
    String a = "Hello";
    String b = a;
    b = a;
    b  ="bye";
    cout << (a == b) << endl;
    return 0;
}