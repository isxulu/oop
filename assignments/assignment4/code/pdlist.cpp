#include <iostream>
#include <fstream>
#include <cstring>
#include "diary.h"
using namespace std;

int main( int argc, char **argv ) {
    /* Define a Diary object */
    Diary diary;
    /* Read in all the entities in the input file */
    diary.readDiary();
    
    /* list all diaries */
    if ( !strcmp(argv[1], "all") ) diary.listDiary();
    /* list all diaries from date start to date end */
    else diary.listDiary( argv[2], argv[3] );
    return 0;
}