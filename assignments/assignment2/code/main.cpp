#include <iostream>
#include <iomanip>
#include "student.h"
using namespace std;
const int width = 11;
const int nInfty = -1000000;
const int pInfty =  1000000;

/* This function can split a line of string input into several part by space. */
vector<string> splitString( string line, string separator );
/* This function can output the final statistical data.
 * and I use a template here is because that min score and max score
 * are of int type, but average score is of double type
 */
template<typename T>
void PrintStatistical( vector<T> s, string sName );

int main () {
    /* definde the vector that store all students' information */
    vector<Student*> stu;
    
    /* Start to input the information */
    string line, cName, cScore;
    vector<string> s;
    vector<string> header;                              // header store the string of the title
    header.push_back("no"); header.push_back("name");
    while ( 1 ) {
        getline(cin, line);                             // read in a line once a time(does not include '\n)
        if ( line == "#" ) break;                       // for simplification, I let '#' to denote quit signal
        else {
            s = splitString( line, " " );
            Student* t = new Student;
            t->SetID( stoi( s[0] ) );                   // store student's ID
            t->SetName( s[1] );                         // store student's name
            for ( int j = 2; j < s.size(); j += 2 ) {
                cName = s[j]; cScore = s[j+1];          // store student's courses information
                t->SetScore( cName, stoi( cScore ) );
                /* Insert the name of the course to the header if it never showed before */
                int flag = 1;                           // flag = 1 denote have found, otherwise
                for ( int j = 0; j < header.size(); j++ ) {
                    if ( header[j] == cName ) {
                        flag = 0;
                        break;
                    }
                }
                if ( flag ) header.push_back( cName );  // insert the course's name
            }
            t->Average();                               // compute this student's average score
            stu.push_back( t );                         // add this student into the whole record
        }
    }
    header.push_back( "average" );                      // add 'average'
    
    /* Print the whole information in a table */
    for ( int i = 0; i < header.size(); i++ ) {
        cout << left << setw(width) << header[i];
    }
    for ( int i = 0; i < stu.size(); i++ ) {
        stu[i]->Print( header );
    }
    
    /* Compute several statistical data */
    vector<double> averageScore;                        // a double type vector that stores the average score of each course
    vector<int> minScore, maxScore;                     // int type vectors that store the minimum and maximum score of each course
    for ( int i = 2; i < header.size()-1; i++ ) {
        int totalScore = 0, totalNum = 0;               // used for compute the average score
        int minimum = pInfty, maximum = nInfty;         // used for compute the minimum and maximum score
        for ( int j = 0 ; j < stu.size(); j++ ) {
            int ret = stu[j]->TakeCourse( header[i] );
            if ( ret < 0 ) continue;
            else {
                totalNum += 1; totalScore += ret;
                if ( minimum > ret ) minimum = ret;     // if current score < minimum score, then set update the minimum
                if ( maximum < ret ) maximum = ret;     // if current score > maximum score, then set update the maximum
            }
        }
        minScore.push_back( minimum );                  // store the information of this score in order to print later
        maxScore.push_back( maximum );
        averageScore.push_back( totalScore * 1.0 / totalNum );
    }
    /* Print the statistical information just computed */
    PrintStatistical( minScore, "min" );
    PrintStatistical( maxScore, "max" );
    PrintStatistical( averageScore, "average" );
    return 0;
}

vector<string> splitString( string line, string separator ) {
    line += separator;
    vector<string> splited;
    string::size_type pos1 = 0, pos2 = 0;
    while( pos2 != line.npos ) {
        pos1 = line.find_first_not_of( separator, pos2 );
        if ( pos1 == line.npos ) break;
        pos2 = line.find_first_of( separator, pos1 );
        splited.push_back( line.substr( pos1, pos2 - pos1 ) );
    }
    return splited;
}
template<typename T>
void PrintStatistical( vector<T> s, string sName ) {
    cout << endl;
    cout << left << setw(width) << " ";
    cout << left << setw(width) << sName;
    for ( int i = 0; i < s.size(); i++ ) {
        cout << left << setw(width) << s[i];
    }
}