#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Student {
    int number;
    int score1;
    int score2;
    int score3;
    string name;
    double average;
};

const int n = 10;                                       // Store the number of students.
const int width = 8;                                    // Control the width of the output.
const int n_infty = -10000000, p_infty = 10000000;      // Define the positive infty and negative infty.

int main () {
    Student students[n];                                // The information of different students.
    double av1, av2, av3;                               // Store the average score of three different tests.
    int min1, min2, min3; min1 = min2 = min3 = p_infty; // Store the minimum score of three different tests.
    int max1, max2, max3; max1 = max2 = max3 = n_infty; // Store the maximum score of three different tests.
    /* Read and compute */
    for ( int i = 0; i < n; i++ ) {
        // Read in the basic information.
        cin >> students[i].number >> students[i].name;
        cin >> students[i].score1 >> students[i].score2 >> students[i].score3;
        av1 += students[i].score1; av2 += students[i].score2; av3 += students[i].score3;
        // Compute the average score of current student directly.
        students[i].average = ( students[i].score1 + students[i].score2 + students[i].score3 ) / 3.0;
        // Update the minimum and maximum score.
        if ( students[i].score1 < min1 ) min1 = students[i].score1;
        if ( students[i].score2 < min2 ) min2 = students[i].score2;
        if ( students[i].score3 < min3 ) min3 = students[i].score3;
        if ( students[i].score1 > max1 ) max1 = students[i].score1;
        if ( students[i].score2 > max2 ) max2 = students[i].score2;
        if ( students[i].score3 > max3 ) max3 = students[i].score3;
    }
    // Compute the average score of three different tests.
    av1 /= n; av2 /= n; av3 /= n;
    /* Output the result */
    cout << setw(width) << left << "no" << setw(width) << left << "name";
    cout << setw(width) << left << "score1" << setw(width) << left << "score2" << setw(width) << left << "score3" << setw(width) << left << "average";
    for ( int i = 0; i < n; i++ ) {
        cout << endl;
        cout << setw(width) << left << students[i].number << setw(width) << left << students[i].name;
        cout << setw(width) << left << students[i].score1 << setw(width) << left << students[i].score2 << setw(width) << left << students[i].score3;
        cout << setw(width) << left << students[i].average;
    }
    cout << endl;
    cout << setw(width) << left << " " << setw(width) << left << "average";
    cout << setw(width) << left << av1 << setw(width) << left << av2 << setw(width) << left << av3 << endl;
    cout << setw(width) << left << " " << setw(width) << left << "min";
    cout << setw(width) << left << min1 << setw(width) << left << min2 << setw(width) << left << min3 << endl;
    cout << setw(width) << left << " " << setw(width) << left << "max";
    cout << setw(width) << left << max1 << setw(width) << left << max2 << setw(width) << left << max3 << endl;
    return 0;
}