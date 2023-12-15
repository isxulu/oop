#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "VectorException.hpp"

template <class T>
class Vector {
public:
    Vector();                       // creates an empty vector
    Vector( int size );             // creates a vector for holding 'size' elements
    Vector( const Vector& r );      // the copy ctor
    ~Vector();                      // destructs the vector 
    T& operator[]( int index );     // accesses the specified element without bounds checking
    T& at( int index );             // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
    int size() const;               // return the size of the container
    void push_back( const T& x );   // adds an element to the end 
    void clear();                   // clears the contents
    bool empty() const;             // checks whether the container is empty 
private:
    void inflate();                 // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
    T *m_pElements;                 // pointer to the dynamically allocated storage
    int m_nSize;                    // the number of elements in the container
    int m_nCapacity;                // the number of elements that can be held in currently allocated storage
};

template <class T>
Vector<T>::Vector() {
    m_pElements = nullptr;
    m_nCapacity = 0;
    m_nSize = 0;
}

template <class T>
Vector<T>::Vector( int size ) {
    m_pElements = new T[size];
    if ( m_pElements == nullptr ) throw VectorException(OUT_OF_MEMORY);
    m_nCapacity = size;
    m_nSize = 0;
}

template <class T>
Vector<T>::Vector( const Vector& r ) {
    m_nCapacity = r.m_nCapacity;
    m_nSize = r.m_nSize;
    m_pElements = new T[m_nCapacity];
    if ( m_pElements == nullptr ) throw VectorException(OUT_OF_MEMORY);
    for ( int i = 0; i < m_nSize; i++ ) {
        m_pElements[i] = r.m_pElements[i];
    }
}

template <class T>
Vector<T>::~Vector() {
    delete[] m_pElements;
}

template <class T>
T& Vector<T>::operator[]( int index ) {
    if ( index < 0 || index >= m_nSize ) throw VectorException(OUT_OF_BOUND, index);
    return m_pElements[index];
}

template <class T>
T& Vector<T>::at( int index ) {
    if ( index < 0 || index >= m_nSize ) throw VectorException(OUT_OF_BOUND, index);
    return m_pElements[index];
}

template <class T>
int Vector<T>::size() const {
    return m_nSize;
}

template <class T>
void Vector<T>::push_back( const T& x ) {
    if ( m_nSize == m_nCapacity ) inflate();
    m_pElements[m_nSize] = x;
    m_nSize++;
}

template <class T>
void Vector<T>::clear() {
    m_nSize = 0;
}

template <class T>
bool Vector<T>::empty() const {
    return m_nSize == 0? true: false;
}

template <class T>
void Vector<T>::inflate() {
    m_nCapacity *= 2;
    T* temp = new T[m_nCapacity];
    if ( temp == nullptr ) throw VectorException(OUT_OF_MEMORY);
    for ( int i = 0; i < m_nCapacity/2; i++ ) {
        temp[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = temp;
}

#endif