//
// Created by zp on 17-7-27.
//

#include "ZCPSInfo.h"
#include "UCLPropertiesInfo.h"

ZCPSInfo::ZCPSInfo() {
    init();
}

void ZCPSInfo::init() {
    spaceLocMap[1] = "BDS";
    spaceLocMap[2] = "GPS";
    spaceLocMap[3] = "GLONASS";
    spaceLocMap[4] = "GSNS";

    timeMap[1] = "BDS";
    timeMap[2] = "GPS";
    timeMap[3] = "GLONASS";
    timeMap[4] = "GSNS";

    shapeMap[1] = "方形";

    phyElectricMap[1] = "220V";
    phySoundMap[1] = "340m/s";
    phyNuclearMap[1] = "原子弹";

    materialMap[1] = "铁";

    passAbiMap[1] = "高";

    motionFeaMap[1] = "速度单位为厘米每秒（cm/s），加速度单位为厘米每秒平方（cm/s2）";
    motionFeaMap[2] = "速度单位为米每秒（m/s），加速度单位为米每秒平方（m/s2）";
    motionFeaMap[3] = "速度单位为千米每小时（km/h），加速度单位为厘米每秒平方（km/h2）";
    motionFeaMap[4] = "速度单位为英里每小时（mile/h），加速度单位为英里每小时平方（mile/h2）";
}

void ZCPSInfo::setPropertyMap(map<int, string> &propertySetCategoryMap,
                              map<int, map<int, string>> &propertyCategoryMap) {
    propertySetCategoryMap[2] = "ZC目标对象编码体系属性集合";

    map<int, string> zcps;
    zcps[1] = "目标对象名称";
    zcps[2] = "空间位置信息";
    zcps[3] = "时间信息";
    zcps[4] = "目标外形";
    zcps[5] = "物理特性";
    zcps[6] = "目标材质";
    zcps[7] = "通过程度";
    zcps[8] = "空间状况信息地";
    zcps[11] = "绝对运动特性";
    zcps[12] = "相对运动特性";
    zcps[13] = "运行轨迹";
    propertyCategoryMap[2] = zcps;
}

string ZCPSInfo::getMapValue(map<int, string> m, int key) {
    if (m.find(key) == m.end())
    {
        return "无该映射！！！";
    }
    return m[key];
}

void ZCPSInfo::showProperty(UCLPropertyBase property) {
    switch (property.getCategory())
    {
        case 1:
            showName(property);
            break;
        case 2:
            showSpaceLoc(property);
            break;
        case 3:
            showTime(property);
            break;
        case 4:
            showShape(property);
            break;
        case 5:
            showPhysical(property);
            break;
        case 6:
            showMaterial(property);
            break;
        case 7:
            showPassingAbility(property);
            break;
        case 8:
            showSpaceStatus(property);
            break;
        case 11:
        case 12:
            showMotionFea(property);
            break;
        case 13:
            showTravellingPath(property);
    }
}

void ZCPSInfo::showName(UCLPropertyBase propertyBase) {
    cout << "名称: "<<propertyBase.getVPart() << endl;
}

void ZCPSInfo::showSpaceLoc(UCLPropertyBase propertyBase) {
    int helper = propertyBase.getHelper();
    cout << "空间位置解析规则：" << timeMap[helper] << endl;
    cout << "位置坐标：" << propertyBase.getVPart() << endl;
}

void ZCPSInfo::showTime(UCLPropertyBase propertyBase) {
    int helper = propertyBase.getHelper();
    cout << "时间解析规则：" << timeMap[helper] << endl;
    cout << "时间：" << propertyBase.getVPart();
}

vector<string> ZCPSInfo::getShape(string vPart) {
    return UCLPropertiesInfo::split(vPart, DEFAULT_PATTERN);
}

void ZCPSInfo::showShape(UCLPropertyBase propertyBase) {
    vector<string> shapes = getShape(propertyBase.getVPart());
    string shape = shapes[0];
    string loc = shapes[1];

    cout << "几何轮廓: " << shape << ", " << getMapValue(shapeMap, atoi(shape.c_str())) << endl;
    cout << "投影边界: " << loc << endl;
}

vector<string> ZCPSInfo::getPhysical(string vPart) {
    return UCLPropertiesInfo::split(vPart, DEFAULT_PATTERN);
}

void ZCPSInfo::showPhysical(UCLPropertyBase propertyBase) {
    vector<string> physicals = getPhysical(propertyBase.getVPart());
    string electric = physicals[0];
    string sound = physicals[1];
    string nuclear = physicals[2];

    cout << "电磁特性: " << electric << ", " << getMapValue(phyElectricMap, atoi(electric.c_str())) << endl;
    cout << "声波特性: " << sound << ", " << getMapValue(phySoundMap, atoi(sound.c_str())) << endl;
    cout << "核生化特性: " << nuclear << ", " << getMapValue(phyNuclearMap, atoi(nuclear.c_str())) << endl;
}

void ZCPSInfo::showMaterial(UCLPropertyBase propertyBase) {
    string value = propertyBase.getVPart();
    cout << "材质: " << value << ", " << getMapValue(materialMap, atoi(value.c_str())) << endl;
}

void ZCPSInfo::showPassingAbility(UCLPropertyBase propertyBase) {
    string value = propertyBase.getVPart();
    cout << "通过程度: " << value << ", " << getMapValue(passAbiMap, atoi(value.c_str())) << endl;
}

void ZCPSInfo::showSpaceStatus(UCLPropertyBase propertyBase) {
    vector<string> spaceStatus = getPhysical(propertyBase.getVPart());
    string group = spaceStatus[0];
    string sky = spaceStatus[1];
    cout << "地面环境状态信息: " << group << endl;
    cout << "空中环境信息: " << sky << endl;
}

void ZCPSInfo::showMotionFea(UCLPropertyBase propertyBase) {
    int helper = propertyBase.getHelper();
    vector<string> motions = getPhysical(propertyBase.getVPart());

    cout << "运动特性解析规则: " << getMapValue(motionFeaMap, helper) << endl;
    cout << "速度: " << motions[0] << endl;
    cout << "加速度: " << motions[1] << endl;
    cout << "运动轨迹: " << motions[2] << endl;
}

void ZCPSInfo::showTravellingPath(UCLPropertyBase propertyBase) {
    int helper = propertyBase.getHelper();
    cout << "运动轨迹解析规则: " << getMapValue(spaceLocMap, helper) << endl;
    cout << "运动轨迹: " << propertyBase.getVPart() << endl;
}


