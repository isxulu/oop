#include <iostream>
#include "diary.h"
using namespace std;

int main() {
    /* Define a Diary object */
    Diary diary;
    /* Read in all the entities in the input file */
    diary.readDiary( "./test_pdadd.txt" );

    string date, temp;
    /* Print the date hint */
    cout << endl << "Please enter the date in the form(xxxx-xx-xx): ";
    /* Input the date */
    getline(cin, date);
    /* Print the content hint */
    cout << endl << "Please the content of the diary, end with a single '.' line: " << endl;
    /* Read in the content of the entity */
    string content;
    while ( getline(cin, temp) ) {
        if ( temp != "." ) content += (temp + "\n");
        else break;
    }
    diary.addEntity( date, content );

    /* Write the modified diary into the file */
    diary.writeDiary( "./test_pdadd_out.txt" );
    return 0;
}