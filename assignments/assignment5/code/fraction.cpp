#include <iostream>
#include <algorithm>
#include "./fraction.hpp"
using namespace std;

/* Compute the greatest common divisor */
int gcd( int x, int y ) {
    return !y? x: gcd( y, x%y );
}

/* default constructor */
Fraction::Fraction() {}

/* normal constructor */
Fraction::Fraction( double d ) {
    int i = 1;
    while ( 1 ) {
        if ( ((d - (int)d) < epsilon) || abs((d - (int)d - 1)) < epsilon ) break;   // there is bug here: the (int)d's precision can not be guaranteed
        d *= 10;
        i *= 10;
    }
    m_denominator = i;
    m_numerator = d;
    int gcdn = gcd( m_numerator, m_denominator );
    m_denominator /= gcdn;
    m_numerator /= gcdn;
}

/* normal constructor */
Fraction::Fraction( int n, int d ): m_numerator(n), m_denominator(!n? 1: d) {}  // set d = 1 if n == 0, to denote zero

/* cpoy constructor */
Fraction::Fraction( const Fraction& f ) {
    this->m_numerator = f.m_numerator;
    this->m_denominator = f.m_denominator;
}

/* destructor */
Fraction::~Fraction() {}

/* Overload operator + for Fraction class */
const Fraction Fraction::operator+( const Fraction& f ) {
    int numerator, denominator, gcdn;
    if ( m_denominator == f.m_denominator ) {       // two operands' denominators are the same
        numerator = m_numerator + f.m_numerator;
        denominator = m_denominator;
        if ( !numerator ) denominator = 1;
        else {
            gcdn = gcd( abs(numerator), m_denominator );
            denominator /= gcdn;
            numerator /= gcdn;
        }
    }
    else {                                          // two operands' denominators are not the same
        gcdn = gcd( m_denominator, f.m_denominator );
        denominator = m_denominator * f.m_denominator / gcdn;
        numerator = m_numerator * denominator / m_denominator + f.m_numerator * denominator / f.m_denominator;
        if ( !numerator ) denominator = 1;
        else {
            gcdn = gcd( abs(numerator), denominator );
            denominator /= gcdn;
            numerator /= gcdn;
        }
    }
    return Fraction( numerator, denominator );
}

/* Overload operator - for Fraction class */
const Fraction Fraction::operator-( const Fraction& f ) {
    int numerator, denominator, gcdn;
    if ( m_denominator == f.m_denominator ) {       // two operands' denominators are the same
        numerator = m_numerator - f.m_numerator;
        denominator = m_denominator;
        if ( !numerator ) denominator = 1;
        else {
            gcdn = gcd( abs(numerator), m_denominator );
            denominator /= gcdn;
            numerator /= gcdn;
        }
    }
    else {                                          // two operands' denominators are not the same
        gcdn = gcd( m_denominator, f.m_denominator );
        denominator = m_denominator * f.m_denominator / gcdn;
        numerator = m_numerator * denominator / m_denominator - f.m_numerator * denominator / f.m_denominator;
        if ( !numerator ) denominator = 1;
        else {
            gcdn = gcd( abs(numerator), denominator );
            denominator /= gcdn;
            numerator /= gcdn;
        }
    }
    return Fraction( numerator, denominator );
}

/* Overload operator * for Fraction class */
const Fraction Fraction::operator*( const Fraction& f ) {
    int denominator = m_denominator * f.m_denominator;
    int numerator = m_numerator * f.m_numerator;
    if ( !numerator ) denominator = 1;
    else {
        int gcdn = gcd( abs(numerator), denominator );
        denominator /= gcdn;
        numerator /= gcdn;
    } 
    return Fraction( numerator, denominator );
}

/* Overload operator / for Fraction class */
const Fraction Fraction::operator/( const Fraction& f ) {
    return operator*( Fraction( f.m_denominator, f.m_numerator ) );
}

/* Overload operator < for Fraction class */
int Fraction::operator<( const Fraction& f ) {
    Fraction t = operator-( f );
    return t.m_numerator < 0? 1: 0;
}

/* Overload operator <= for Fraction class */
int Fraction::operator<=( const Fraction& f ) {
    Fraction t = operator-( f );
    return t.m_numerator <= 0? 1: 0;
}

/* Overload operator == for Fraction class */
int Fraction::operator==( const Fraction& f ) {
    return (m_numerator == f.m_numerator) && (m_denominator == f.m_denominator)? 1: 0;
}

/* Overload operator != for Fraction class */
int Fraction::operator!=( const Fraction& f ) {
    return (m_numerator == f.m_numerator) && (m_denominator == f.m_denominator)? 0: 1;
}

/* Overload operator >= for Fraction class */
int Fraction::operator>=( const Fraction& f ) {
    Fraction t = operator-( f );
    return t.m_numerator >= 0? 1: 0;
}

/* Overload operator > for Fraction class */
int Fraction::operator>( const Fraction& f ) {
    Fraction t = operator-( f );
    return t.m_numerator > 0? 1: 0;
}

/* Print the fraction to the console */
void Fraction::print() {
    cout << m_numerator << "/" << m_denominator << endl;
}

/* Cast the current fraction to a double object */
double Fraction::toDouble() {
    double d = 1.0 * m_numerator / m_denominator;
    return d;
}

/* Cast the current fraction to a string object */
string Fraction::toString() {
    string s = to_string( m_numerator ) + "/" + to_string( m_denominator );
    return s;
}

istream& operator>>( istream& in, Fraction& f ) {
    in >> f.m_numerator >> f.m_denominator;
    return in;
}

ostream& operator<<( ostream& out, Fraction& f ) {
    out << f.m_numerator << "/" << f.m_denominator << endl;
    return out;
}