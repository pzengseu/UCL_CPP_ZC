#include <iostream>
#include <bitset>
#include "test.h"
#include "testUCLCode.h"

using namespace std;

void testUCLCodeEasy()
{
    cout << "========== UCL Code test begin==========\n";
    test_code();
    test_unpack();
    cout << "========== UCL Code test end  ==========\n";
}

int main()
{
    testCommand();
    return 0;
}