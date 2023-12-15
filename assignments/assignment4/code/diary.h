#ifndef _DIARY_H_
#define _DIARY_H_

#include <string>
#include <vector>

using namespace std;

class Entity {
private:
    string m_date;
    string m_content;
public:
    Entity() {}
    Entity( string date, string content ): m_date(date), m_content(content) {}
    string getDate() const;
    string getContent() const;
    void setContent( string content );
};

class Diary {
private:
    vector <Entity> diary;
public:
    Diary() {}
    void addEntity( string date, string content );
    void readDiary();
    void writeDiary();
    void readDiary( string fileName );
    void writeDiary( string fileName );
    void listDiary();
    void listDiary( string start, string end );
    void listEntity( string date );
    int removeEntity( string date );
};

#endif