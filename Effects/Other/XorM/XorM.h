#pragma once
#ifndef XORM_H
#define XORM_H


#include <stdint.h>
#include <math.h>

class XorM
{
public:
    XorM();
    ~XorM();


    void init();

    float process(float input, float carrier);

    float setMangle(float mangle);
    
private:
    int16_t _mangle;
    float _mangled;
};


#endif