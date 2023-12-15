#ifndef _UCPOINTER_H_
#define _UCPOINTER_H_

template <class T>
class UCPointer {
private:
    T* m_pObj;
    void increment() {
        if ( m_pObj )
            m_pObj->incr();
    }
    void decrement() {
        if ( m_pObj ) 
            m_pObj->decr();
    }

public:
    UCPointer(T* r = 0): m_pObj(r) {
        increment();
    }
    UCPointer(const UCPointer<T> &p) {
        m_pObj = p.m_pObj;
        increment();        // only increment, because it is a construct
    }
    ~UCPointer() {
        decrement();
    }
    UCPointer &operator=(const UCPointer<T> &p) {
        if ( m_pObj != p.m_pObj ) {
            decrement();            // 原来指的 UCObject--
            m_pObj = p.m_pObj;
            increment();            // 现在指的 UCObject++
        }
        return *this;
    }
    T* operator->() const {
        return m_pObj;
    }
    T& operator*() const {
        return *m_pObj;
    }
};

#endif