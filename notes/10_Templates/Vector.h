template <class T>
class Vector {
private:
    T* content;
    int size;
public:
    Vector( int s ):size(s) {}
    T& operator[]( int index );
};

template <class T>
T& Vector<T>::operator[]( int index ) {
    return content[index];
}