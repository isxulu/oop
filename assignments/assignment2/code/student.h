#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>
#include <vector>
using namespace std;

class Student {
    private:
        int m_number;
        string m_name;
        double m_average;
        struct Course {
            int courseScore;
            string courseName;
        };
        vector<Course> m_courses;
    public:
        void SetID( int n );
        void SetName( string name );
        void SetScore( string courseName, int score );
        void Average();
        int TakeCourse( string courseName );
        void Print( vector<string> all );
};
#endif