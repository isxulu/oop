#include <iostream>
#include <fstream>
#include "diary.h"
using namespace std;

int main( int argc, char **argv ) {
    /* Define a Diary object */
    Diary diary;
    /* Read in all the entities in the input file */
    diary.readDiary();

    /* Delete the specified date diary */   
    int ret = diary.removeEntity( argv[1] );
    if ( !ret ) cout << "Delete successfully!" << endl;
    else cout << "Delete fails!" << endl;

    /* Write the modified diary back to the file */
    diary.writeDiary( "./test_pdremove_out.txt" );
    return 0;
}