#ifndef AKKU_DATA_H
#define AKKU_DATA_H

#include <Arduino.h>

class AkkuData {
public:
    AkkuData();
    
    double internalRes;
    double volt;
    double capacity;
    unsigned long lastMeasure;
    unsigned long elapsedTime;
    bool isRunning;
    
    void reset();
};

// 8 Akkus
extern AkkuData akkuDatas[8];

#endif