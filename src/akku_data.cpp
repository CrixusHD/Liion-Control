#include "akku_data.h"

AkkuData::AkkuData() {
    reset();
}

void AkkuData::reset() {
    internalRes = 0.0;
    volt = 0.0;
    capacity = 0.0;
    lastMeasure = 0;
    elapsedTime = 0;
    isRunning = false;
}

// 8 Akkus global
AkkuData akkuDatas[8];