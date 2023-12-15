#include "Vector.h"

template <class T>
T& Vector<T>::operator[]( int index ) {
    return content[index];
}