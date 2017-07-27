//
// Created by zp on 17-7-27.
//

#include "ZCPSInfo.h"

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

void ZCPSInfo::showProperty(UCLPropertyBase property) {

}