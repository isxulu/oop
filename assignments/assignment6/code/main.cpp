#include <iostream>
#include "Vector.h"
using namespace std;

int main() {
    try {
        Vector<int> v1(5);
        cout << "*********** Test1: test push_back() function ***********" << endl;
        v1.push_back(1); v1.push_back(2); v1.push_back(3); v1.push_back(4); v1.push_back(5);
        for ( int i = 0; i < 5; i++ ) {
            cout << v1[i] << " ";
        }

        cout << endl << endl;
        cout << "*********** Test2: test empty() and clear() functions ***********" << endl;
        cout << "v1 is empty: " << v1.empty() << endl;
        v1.clear();
        cout << "after clear, v1 is empty: " << v1.empty() << endl;
        
        cout << endl;
        cout << "*********** Test3: test index out of bound exception catch of [] ***********" << endl;
        cout << v1[6] << endl;
    } catch(VectorException& e) {
        e.diagnostic();
    }
    try {
        cout << endl;
        cout << "*********** Test4: test inflate when push_bach() ***********" << endl;
        Vector<string> v2(3);
        v2.push_back("u1"); v2.push_back("u2"); v2.push_back("u3");
        cout << "original size of v2: " << v2.size() << endl;
        v2.push_back("u4");
        cout << "after push_back to v2, size of v2 becomes:" << v2.size() << endl;

        cout << endl;
        cout << "*********** Test5: test at() ***********" << endl;
        for ( int i = 0; i < 4; i++ ) {
            cout << v2.at(i) << " " << endl;
        }

        cout << endl;
        cout << "*********** Test3: test index out of bound exception catch of at() " << endl;
        v2[-1] = "exception";
    } catch(VectorException& e) {
        e.diagnostic();
    }
    return 0;
}