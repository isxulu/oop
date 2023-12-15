#ifndef _UCOBJECT_H_
#define _UCOBJECT_H_

#include <assert.h>
class UCObject {
private:
    int m_refCount;
public:
    UCObject(): m_refCount(0) {}
    UCObject(const UCObject&): m_refCount(0) {} // new object, so m_refCount = 0
    virtual ~UCObject() {
        assert(m_refCount == 0);    // if we destruct the object when refCount != 0, throw a exception
    }
    void incr() {
        m_refCount++;
    }
    void decr() {
        m_refCount--;
        if ( m_refCount == 0 ) {
            delete this;
        }
    }
    int references() {
        return m_refCount;
    }
};

#endif