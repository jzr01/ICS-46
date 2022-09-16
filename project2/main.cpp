#include <iostream>
#include "SkipList.hpp"
using namespace std;

int main()
{
    SkipList<unsigned, std::string> sl;
    for(unsigned i=0; i < 10; i++)
    {
        sl.insert(i,"abc");
    }

    return 0;
}
