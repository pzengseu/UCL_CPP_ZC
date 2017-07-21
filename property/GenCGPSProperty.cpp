//
// Created by zp on 17-6-17.
//

#include <assert.h>
#include "GenCGPSProperty.h"
#include "../UCL/UCL.h"

UCLPropertyBase GenCGPSProperty::genContSig(string content, uint8_t alg, uint8_t helper)
{
    assert(helper <= 5);
    assert(alg < 5);

    UCLPropertyBase signature;
    signature.setLPartHead(2, 5, alg);

    string hash = UCL::genHash(alg, content);
    string signCont = UCL::genSig(helper, hash);
    signature.setProperty(12, helper, signCont);

    return signature;
}

UCLPropertyBase GenCGPSProperty::genUCLSig(uint8_t alg, uint8_t helper)
{
    assert(helper <= 5);
    assert(alg < 5);

    UCLPropertyBase signature;
    signature.setLPartHead(2, 5, alg);
    signature.setProperty(15, helper, "");

    return signature;
}
