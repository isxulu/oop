#include <iostream>
using namespace std;

int global_variable = 0xdeadbeef;

class B {
public:
    B( int k ) {
        cout << "B()" << k << endl;
    }
};

class Test {
private:
    int i = 0x10;
    B b1;
    int global_variable = k(i);     // c++11, 定义初始化
    B b2;
public:
    Test() : b2(2), b1(1) {              // 初始化列表
        cout << "Test()" << hex << i << ", " << hex << global_variable << endl;
    }
    int k( int i ) { 
        cout << "k" << hex << i << ", " << hex << global_variable << endl;
        return i+0xcafebabe;
    }
    void f() {
        int global_variable = 0x20011002;
        cout << hex << global_variable << endl;
        cout << hex << ::global_variable << endl;
        cout << hex << Test::global_variable << endl;
        cout << hex << this->global_variable << endl;
    }
};

int main () {
    Test t;
    // t.f();
    return 0;
}