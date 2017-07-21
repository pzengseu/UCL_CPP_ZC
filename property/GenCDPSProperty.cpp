//
// Created by zp on 17-6-17.
//

#include <assert.h>
#include "UCLPropertyBase.h"
#include "GenCDPSProperty.h"

UCLPropertyBase GenCDPSProperty::genTitle(string vPart, uint8_t helper)
{
    UCLPropertyBase title;
    title.setProperty(0x1, helper, vPart);

    return title;
}

UCLPropertyBase GenCDPSProperty::genFileDescription(string vPart, uint8_t helper)
{
    UCLPropertyBase file;
    file.setProperty(9, helper, vPart);

    return file;
}

/*
第一子分量，长度头部字节，它的 0 ～ 7 位含义如下：
第 0 ～ 2 位保留，含义暂未定义；
第 3 ～ 5 位，其值加 1 表示 UCL 的个数， 111 表示超过 7 个；
第 6 ～ 7 位，其值加 1 表示长度值子分量所占字节数， 10、 11 为非法取值。                                                                                                                                                                          
 */
UCLPropertyBase GenCDPSProperty::genRelatedUCL(uint8_t count, string vPart, uint8_t helper)
{
    assert(count >=1);
    if (count > 7) count = 8;

    UCLPropertyBase relatedUCL;
    relatedUCL.setLPartHead(3, 5, count - 1);
    relatedUCL.setProperty(14, helper, vPart);

    return relatedUCL;
}

UCLPropertyBase GenCDPSProperty::genContObject(string vPart, uint8_t helper)
{
    UCLPropertyBase contentObject;
    contentObject.setProperty(15, helper, vPart);

    return contentObject;
}
