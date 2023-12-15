#include "./fraction.hpp"
using namespace std;

int main() {
    /* Test 1: ctor takes two integers as parameters */
    Fraction f1(-1, 6); f1.print();
    Fraction f2(1, 7);  f2.print();
    /* Test 2: arithmetical operators: + - * / and copy ctor */
    Fraction f3 = f1 + f2; f3.print();
    Fraction f4 = f1 - f2; f4.print();
    Fraction f5 = f1 * f2; f5.print();
    Fraction f6 = f1 / f2; f6.print();
    /* Test 3: relational operators: < <= == != >= > */
    int f7 = f1 < f2;  cout << f7 << endl;
    int f8 = f1 == f2; cout << f8 << endl;
    /* Test 4: type cast to double */
    double d1 = f1.toDouble();
    /* Test 5: type cast to string */
    string s1 = f2.toString();
    cout << d1 << " " << s1 << endl;
    /* Test 6: inserter and extractor for streams */
    cout << "Please input numerator and denominator respectively: ";
    Fraction f10; cin >> f10;
    cout << f10;
    /* Test 7: conversion from a finite decimal string */
    cout << "Please input a double decimals: ";
    double d; cin >> d;
    Fraction f9(d);
    f9.print();

    return 0;
}