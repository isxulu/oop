#include <iostream>
#include <fstream>
#include "diary.h"
using namespace std;

int main(int argc, char **argv) {
    /* Define a Diary object */
    Diary diary;
    /* Read in all the entities in the input file */
    diary.readDiary();

    /* List the specified entities */
    diary.listEntity( argv[1] );
    return 0;
}