//
// Created by zp on 17-6-17.
//

#ifndef UCL_CPP_GENCGPSPROPERTY_H
#define UCL_CPP_GENCGPSPROPERTY_H

#include "UCLPropertyBase.h"

/**
 *  CGPS, signature of content, signature of UCL Package
 */
class GenCGPSProperty {
public:
    //signature of content
    static UCLPropertyBase genContSig(string content, uint8_t alg, uint8_t helper=0);

    //signature of UCL package
    static UCLPropertyBase genUCLSig(uint8_t alg, uint8_t helper=0);
};

#endif //UCL_CPP_GENCGPSPROPERTY_H
