#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "diary.h"

/***********************************************************
 *           The menber function of Entity class           *
 ***********************************************************/
string Entity::getDate() const {
    return m_date;
}

string Entity::getContent() const {
    return m_content;
}

void Entity::setContent( string content ) {
    m_content = content;
}

/***********************************************************
 *            The menber function of Diary class           *
 ***********************************************************/
void Diary::addEntity( string date, string content ) {
    /* find whether there has been a diary at date date */
    int i, flag = 1;
    for ( i = 0; i < diary.size(); i++ ) {
        if ( diary[i].getDate() == date ) {
            flag = 0;
            break;
        }
    }
    /* replacing the existing diary of date date */
    if ( !flag ) diary[i].setContent( content );
    /* add an entity to the diary for the date */
    else {
        Entity e( date, content );
        diary.push_back( e );
    }
}

void Diary::readDiary() {
    int flag = 0, i = 0;
    /* date: the diary date, temp: each line of the content */
    string date, temp;
    while ( getline(cin, date) ) {
        // /* getline(cin, str) wiil leave a extra '\n' when confronted with a empty line, so we need to handle it */
        // if ( i++ ) cin.get();

        /* read in the content of current entity */
        string content;
        while ( 1 ) {
            /* read in a line of the diary from the stdin to temp */
            getline(cin, temp);
            if ( temp.empty() ) break;                      // end of current entity
            else if ( temp == "." ) { flag = 1; break; }    // end of all the diaries
            else content += ( temp + "\n" );                // add temp to the total content variable
        }
        /* add the current entity into vector diary */
        Entity e(date, content);
        diary.push_back( e );
        /* flag == 1: denote the end of the input diary */
        if ( flag ) break;
    }
}

void Diary::readDiary( string fileName ) {
    /* declare a input file object */
    ifstream inFile( fileName, ios_base::in );
    /* judge if the file has been successfully opened */
    if ( !inFile.is_open() ) exit(EXIT_FAILURE);
    else {
        int flag = 0;
        /* date: the diary date, temp: each line of the content */
        string date, temp;
        while ( getline(inFile, date) ) {
            string content;
            while( 1 ) {
                /* read in a line of the diary from the stdin to temp */
                getline(inFile, temp);
                if ( temp.empty() ) break;                      // end of current entity
                else if ( temp == "." ) { flag = 1; break; }    // end of all the diaries
                else content += ( temp + "\n" );                // add temp to the total content variable
            }
            /* add the current entity into vector diary */
            Entity e(date, content);
            diary.push_back( e );
            /* flag == 1: denote the end of the input diary */
            if ( flag ) break;
        }
    }
    inFile.close();
}

void Diary::writeDiary() {
    /* judge if the file has been successfully opened */
    for ( int i = 0; i < diary.size(); i++ ) {
        cout << diary[i].getDate() << endl;
        if ( i != diary.size()-1 ) cout << diary[i].getContent() << endl;
        else cout << diary[i].getContent() << "." << endl;
    }
}

void Diary::writeDiary( string fileName ) {
    /* declare a input file object */
    ofstream outFile( fileName, ios_base::trunc );
    /* judge if the file has been successfully opened */
    if ( !outFile.is_open() ) exit(EXIT_FAILURE);
    else {
        for ( int i = 0; i < diary.size(); i++ ) {
            outFile << diary[i].getDate() << endl;
            if ( i != diary.size()-1 ) outFile << diary[i].getContent() << endl;
            else outFile << diary[i].getContent() << "." << endl;
        }
    }
    outFile.close();
}

bool comp( const Entity& e1, const Entity& e2 ) {
    if ( e1.getDate() < e2.getDate() ) return true;
    else return false;
}
void Diary::listDiary() {
    int size = diary.size();
    /* The diary is empty */
    if ( !diary.size() ) cout << "The diary is empty!!!" << endl;
    /* Print all the diaries */
    else {
        /* First sort all the entities by the date */
        sort( diary.begin(), diary.end(), comp );
        /* Print the sorted results */
        for ( int i = 0; i < size; i++ ) {
            cout << diary[i].getDate() << endl;
            if ( i != size-1 ) cout << diary[i].getContent() << endl;
            else cout << diary[i].getContent() << "." << endl;
        }
    }
}

void Diary::listDiary( string start, string end ) {
    int size = diary.size();
    /* The diary is empty */
    if ( !size ) cout << "The diary is empty!!!" << endl;
    else {
        sort( diary.begin(), diary.end(), comp );
        int s1 = 0, s2 = -1;
        for ( int i = 0; i < size; i++ ) {
            if ( diary[i].getDate() < start ) s1 = i + 1;
            if ( diary[i].getDate() < end ) s2 = i;
        }
        /* There is no diary between days in [start, end] */
        if ( s1 >= size || s2 < 0 ) cout << "There is no diary in this period of time!!!" << endl << endl;
        /* Print the diaries between these two days */
        else {
            for ( int i = s1; i <= s2; i++ ) {
                cout << diary[i].getDate() << endl;
                if ( i != s2 ) cout << diary[i].getContent() << endl;
                else cout << diary[i].getContent() << "." << endl;
            }
        }
    }
}

void Diary::listEntity( string date ) {
    int size = diary.size();
    /* The diary is empty */
    if ( !diary.size() ) cout << "The diary is empty!!!" << endl;
    /* Find the expected date */
    else {
        int i, flag = 0;
        for ( i = 0; i < size; i++ ) {
            if ( diary[i].getDate() == date ) {
                flag = 1;
                break;
            }
        }
        if ( !flag ) cout << "There is no diary at this day!!!" << endl << endl;
        else {
            cout << diary[i].getDate() << endl;
            cout << diary[i].getContent();   
        }
    }
}

int Diary::removeEntity( string date ) {
    int size = diary.size();
    /* The diary is empty */
    if ( !diary.size() ) cout << "The diary is empty!!!" << endl;
    else {
        int i, flag = 0;
        for ( int i = 0; i < size; i++ ) {
            if ( diary[i].getDate() == date ) {
                flag = 1;
                break;
            }
        }
        /* remove fails, return -1 */
        if ( !flag ) return -1;
        /* remove success, return 0 */
        else {
            diary.erase( diary.begin() + i );   // erase the element from vector
            return 0;
        }
    }
}