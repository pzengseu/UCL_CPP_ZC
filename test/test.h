//
// Created by zp on 12/20/16.
//

#ifndef UCL_CPP_TEST_H
#define UCL_CPP_TEST_H

#include <iomanip>
#include <fstream>
#include <iostream>
#include "../property/base/UCLPropertyHead.h"
#include "../property/base/UCLPropertySet.h"
#include "../UCL/UCL.h"
#include <sstream>

void testCommand();
void printPackString(string pack);
UCL generateRUCL();

UCLCode generateCode();
UCLPropertySet generateCDPS();
UCLPropertySet generateCGPS();
UCLPropertySet generateZCPS();

#endif //UCL_CPP_TEST_H
