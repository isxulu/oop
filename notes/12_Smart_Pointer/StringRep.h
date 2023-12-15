#ifndef _STRING_REP_H_
#define _STRING_REP_H_

#include "./UCObject.h"
#include <cstring>

class StringRep : public UCObject {
public:
    StringRep(const char* s) {
        if (s) {
            int len = strlen(s) + 1;
            m_pChars = new char[len];
            strcpy(m_pChars, s);
        }
        else {
            m_pChars = new char[1];
            *m_pChars = '\0';
        }
    }
    StringRep(const StringRep& sr) {
        int len = sr.length();
        m_pChars = new char[len+1];
        strcpy(m_pChars, sr.m_pChars);
    }
    ~StringRep() {
        delete[] m_pChars;
    }

    int length() const {
        return strlen(m_pChars);
    }
    int equal(const StringRep& sp) const {
        return (strcmp(m_pChars, sp.m_pChars) == 0);
    }

private:
    char* m_pChars;
    void operator=(const StringRep &) {}
};

#endif