#pragma once
#include "Arduino.h"

struct readouts_t {
    float temp;
    float humid;
};

struct power_t {
    float battery_volt;
    float solar_volt;
};

struct anomaly_t {
    uint8_t intrusion = 0;
    uint8_t dht1_down = 0;
    uint8_t dht2_down = 0;
    uint8_t low_batt = 0;
};

#define CH_READOUTS 5 // Combined Data at 69=5+64
#define CH_ANOMALY 6 // Commands at 70=6+64
#define CH_POWER 7 // Status Indicators at 71=7+64
