
#include "XorM.h"
XorM::XorM() {}
XorM::~XorM() {}

void XorM::init()
{
    _mangle = 0;
}

float XorM::process(float input, float carrier)
{

    if (_mangle == 0 && carrier == 0)
        return input;

    int16_t intInput = (int16_t)(input * 32767.0f);
    int16_t intCarrier = (int16_t)(carrier * 32767.0f);
    _mangled = (float)(intInput ^ (_mangle + intCarrier));

    return _mangled / 32767.0f;
}

float XorM::setMangle(float mangle)
{
    _mangle = (int16_t)(mangle * 32767.0f);
    return _mangle;
}