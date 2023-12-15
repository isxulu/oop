#ifndef _STRING_HEAD_
#define _STRING_HEAD_

#include "./StringRep.h"
#include "./UCPointer.h"

class String {
public:
    String(const char* s): m_rep(0) {
        m_rep = new StringRep(s);           // 刚 new 出来是 0
    }
    String(const String &s): m_rep(s.m_rep) {}
    ~String() {}

    String& operator=(const String& s) {
        m_rep = s.m_rep;                    // let smart pointer do work!
        return *this;
    }
    int operator==(const String& s) const {
        // overload -> forwards to StringRep
        return m_rep->equal(*s.m_rep);      // smart ptr *
    }
    String operator+(const String &) const;
    int length() const {
        return m_rep->length();
    }

private:
    UCPointer<StringRep> m_rep;
};

#endif