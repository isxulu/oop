#include <iostream>
#include <string>
using namespace std;


class Fee {
public:
    Fee( int ) { cout << "Fee(int)\n"; }
    Fee( const Fi& ) { cout << "Fee(Fi)\n"; }

};