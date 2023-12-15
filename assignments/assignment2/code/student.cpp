#include"student.h"
#include <iostream>
#include <iomanip>
using namespace std;
const int width = 11;

void Student::SetID( int n ) {
    m_number = n;
}

void Student::SetName( string name ) {
    m_name = name;
}

void Student::SetScore( string courseName, int courseScore ) {
    Course c;
    c.courseName = courseName;
    c.courseScore = courseScore;
    m_courses.push_back( c );
}

void Student::Average() {
    double total = 0.0;
    for ( int i = 0; i < m_courses.size(); i++ ) {
        total += m_courses[i].courseScore;
    }
    m_average = total * 1.0 / m_courses.size();
}

int Student::TakeCourse( string courseName ) {
    int ret = -1;
    for ( int i = 0; i < m_courses.size(); i++ ) {
        if ( m_courses[i].courseName == courseName ) {
            ret = m_courses[i].courseScore;
            break;
        }
    }
    return ret;
}

void Student::Print( vector<string> all ) {
    cout << endl;
    cout << left << setw(width) << m_number;
    cout << left << setw(width) << m_name;
    for ( int i = 2; i < all.size()-1; i++ ) {
        int flag = 0, idx = 0;
        for ( int j = 0; j < m_courses.size(); j++ ) {
            if ( m_courses[j].courseName == all[i] ) {
                idx = j;
                flag = 1;
                break;
            }
        }
        if ( flag ) cout << left << setw(width) << m_courses[idx].courseScore;
        else cout << left << setw(width) << "*";
    }
    cout << left << setw(width) << m_average;
}