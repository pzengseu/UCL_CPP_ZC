//
// Created by zp on 17-7-27.
//

#ifndef UCL_CPP_ZCPSINFO_H
#define UCL_CPP_ZCPSINFO_H
#include <iostream>
#include <map>
#include "UCLPropertyBase.h"

using namespace std;

class ZCPSInfo {
private:
    map<int, string> spaceLocMap;
    map<int, string> timeMap;
    map<int, string> shapeMap;
    map<int, string> phyElectricMap;
    map<int, string> phySoundMap;
    map<int, string> phyNuclearMap;
    map<int, string> materialMap;
    map<int, string> passAbiMap;
    map<int, string> motionFeaMap;
public:
    ZCPSInfo();

    //初始化受控映射表
    void init();

    void setPropertyMap(map<int, string> &propertySetCategoryMap,
                        map<int, map<int, string>> &propertyCategoryMap);

    void showProperty(UCLPropertyBase propertyBase);
};

#endif //UCL_CPP_ZCPSINFO_H
