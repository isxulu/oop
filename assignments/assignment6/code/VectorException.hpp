#ifndef _VECTOR_EXCEPTION_H_
#define _VECTOR_EXCEPTION_H_

#include <iostream>

extern const int OUT_OF_BOUND = -1;
extern const int OUT_OF_MEMORY = -2;

class VectorException {
private:
    int m_bad;
    int m_index;
public:
    VectorException(int t, int i=0): m_bad(t), m_index(i) {}
    ~VectorException() {}
    void diagnostic() {
        if ( m_bad == OUT_OF_BOUND ) {
            std::cout << "index " << m_index << " out of range!" << std::endl;
        }
        else if ( m_bad == OUT_OF_MEMORY ) {
            std::cout << "out of memory!" << std::endl;
        }
    }
};

#endif