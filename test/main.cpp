#include <iostream>
#include <iterator>
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

void testUCL()
{
    //UCLCode部分测试函数
//    testUCLCodeEasy();

    //测试UCL打包解包
    testCommand();
}

int main()
{
    testUCL();
    return 0;
}
