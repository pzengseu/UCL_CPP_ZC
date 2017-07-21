//
// Created by zp on 17-6-17.
//

#ifndef UCL_CPP_GENCDPSPROPERTY_H
#define UCL_CPP_GENCDPSPROPERTY_H

#include "UCLPropertyBase.h"

/**
 * CDPS, title, originality, file Description
 */
class GenCDPSProperty
{
public:
    //title
    static UCLPropertyBase genTitle(string vPart, uint8_t helper=0);

    //file description
    static UCLPropertyBase genFileDescription(string vPart, uint8_t helper=0);

    //Related UCL
    static UCLPropertyBase genRelatedUCL(uint8_t count, string vPart, uint8_t helper=0);

    //Content Object
    static UCLPropertyBase genContObject(string vPart, uint8_t helper=0);
};
#endif //UCL_CPP_GENCDPSPROPERTY_H
