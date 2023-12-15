#include <iostream>
using namespace std;

class B {
protected:
    int i = 0;
public:
    void prt() {
        cout << "B: " << i << endl;
    }
};

class D : public B {
private:
    int j = 30;    
public:
    D () {
        i = 10;
    }
    void prt() {
        cout << "D: " << i << endl;
    }
};

class Point {

};

class Shape {
protected:
    int x = 10;
    // Point center;
public:
    Shape() {
        cout << "Shape()" << endl;
        move();
    }
    virtual void render() {
        cout << "shape::render" << endl;
    }
    virtual void move() { 
        cout << "shape::move()" << endl;
        x = 20; 
    }
    virtual void prt() { cout << x << endl; }
};

class Rectangle:public Shape {
protected:
    // int width;
    // int height;
public:
    Rectangle() {
        cout << "Rectangle()" << endl;
        // move();
    }
    void render() {
        cout << "rec::render" << endl;
    }
    void move() {
        cout << "rec::move()" << endl;
        x = 30;
    }
};

class Square:public Rectangle {
public:
    void render() {
        cout << "sqr::render" << endl;
    }
};

void render( Shape* s ) {
    s->render();
}

int main() {
    // /* The assignment of VPTR */
    // Rectangle r;
    // r.prt();
    // cout << "----------" << endl;
    // Shape *s = &r;
    // s->move();

    /* See how the virtual function is implemented */
    // cout << sizeof(Shape) << endl;
    // cout << sizeof(Square) << endl;
    // Square s;
    // // int *p = (int*)&s;
    // // cout << *p << endl;
    // long long **p = (long long **)&s;
    // void (*f)() = (void (*)())(**p);
    // (*f)();

    /* The pointer: polymorphism variables */
    // Square s;
    // Rectangle r;
    // s.render();      // static -- Square::render();
    // r.render();      // static -- Rectangle::render();
    // render( &s );    // dynamic -- Square::render();
    // render( &r );    // dynamic -- Rectangle::render();

    /* Upcast */
    D d;
    d.prt();    // Derived class's object
    B* b = &d;
    b->prt();
    
    /* Slice */
    // B b;
    // b.prt();    // Base class's object
    // b = d;      // Assign a derived object to a base object
    // b.prt();
    // cout << "The size of b is: " << sizeof(b) << endl;
    return 0;
}