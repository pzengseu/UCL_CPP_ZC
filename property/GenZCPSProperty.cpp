//
// Created by zp on 17-7-21.
//

#include "GenZCPSProperty.h"

//name
UCLPropertyBase GenZCPSProperty::genName(string vPart, uint8_t helper) {
    UCLPropertyBase name;
    name.setProperty(0x1, helper, vPart);

    return name;
}