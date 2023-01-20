
#include "ChainedHashtable.h"
#include <iostream>
void checkHashTable();
template<class Type>
bool checkTest(std::string, Type, Type);
int main()
{
    checkHashTable();
    return 0;
}
void checkHashTable(){
    std::cout << "Chained Hashtable" << std::endl;
    ChainedHashtable<int> htable(20);
    for(int i = 0; i < 20; i++){
        htable.add(rand() % 100);
    }
    checkTest("#1 Size Test" , 20, htable.size());
    htable.add(151);
    checkTest("#2 Test Contains", true, htable.contains(151));
    htable.remove(151);
    checkTest("#3 Test Remove", false, htable.contains(151));
    std::cout << htable;
}
//This helps with testing, do not modify.
template<class Type>
bool checkTest(std::string testName, Type whatItShouldBe, Type whatItIs) {
    if (whatItShouldBe == whatItIs) {
        std::cout << "Passed " << testName << std::endl;
        return true;
    }
    else {
        std::cout << "****** Failed test " << testName << " ****** " << std::endl
        << "Output was " << whatItIs << std::endl
        << "     Output should have been " <<
        whatItShouldBe << std::endl;
        return false;
    }
}
