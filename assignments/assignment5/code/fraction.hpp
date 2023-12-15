#ifndef _FRACTION_H_
#define _FRACTION_H_
#include <string>
#include <iostream>
using namespace std;
const double epsilon = 1e-5;

class Fraction {
private:
    int m_numerator;
    int m_denominator;
public:
    Fraction();
    Fraction( double d );
    Fraction( int n, int d );
    Fraction( const Fraction& f );
    ~Fraction();
    friend istream& operator>>( istream& in, Fraction& f );
    friend ostream& operator<<( ostream& out, Fraction& f );
    const Fraction operator+( const Fraction& f );
    const Fraction operator-( const Fraction& f );
    const Fraction operator*( const Fraction& f );
    const Fraction operator/( const Fraction& f );
    int operator<( const Fraction& f );
    int operator<=( const Fraction& f );
    int operator==( const Fraction& f );
    int operator!=( const Fraction& f );
    int operator>=( const Fraction& f );
    int operator>( const Fraction& f );
    double toDouble();
    string toString();
    void print();
};

#endif