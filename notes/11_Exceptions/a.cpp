#include <iostream>
using namespace std;

class VIE {
private:
    int idx;
public:
    VIE(int i): idx(i) {}
    ~VIE() {}
    void diag() {
        cout << "VIE:" << idx << endl;
    }
};

template <class T>
class Vector {
private:
    T* element;
    int size;
public:
    Vector(int s): size(s) {
        element = new T[s];
    }
    ~Vector() { delete[] element; }
    T& operator[](int index) {
        if ( index < 0 || index >= size ) {
            throw VIE(index);
        }
        return element[index];
    }
};

void func() {
    Vector<int> v(10);
    v[3] = 5;
    cout << "1\n";
    int i = v[42];
    cout << "2\n";
}

void func2() {
    cout << "3\n";
}

void outer() {
    try {
        cout << "4\n";
        func();
        func2();
    } catch (VIE& v) {
        // v.diag();
        throw;
    }
    cout << "5\n";
}

int main() {
    // outer();
    func();
    return 0;
}