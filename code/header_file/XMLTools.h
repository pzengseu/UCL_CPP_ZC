//
// Created by Oneway on 2017/07/22.
// Modified by Oneway on 2017/07/22.
//

#ifndef XMLTOOLS_H
#define XMLTOOLS_H
#include <iostream>
#include <stdio.h>
#include "../tinyxml/tinyxml.h"
#include "./UCLXMLConf.h"
#include "./UCLCode.h"
#include <ctime>
#include <iomanip>

using namespace std;

void readXml(const char* filePath);
void writeXml(const char* filePath);
void showFromXml(const UCLCode &code);//根据xml的配置解析并显示各个字段的含义
void test_code_xml();
void testRead();

#endif //XMLTOOLS_H
