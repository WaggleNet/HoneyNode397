#pragma once
#include "custom_types.h"
#include "pinmap.h"

enum AnomType {AN_INTRUSION, AN_DHT1DOWN, AN_DHT2DOWN, AN_LOWBATT};

extern anomaly_t anomaly_flags;

uint8_t * getAnomalyItem(AnomType flag);

void setAnomaly(AnomType flag);
void writeAnomaly(AnomType flag, uint8_t value);
void clearAnomaly(AnomType flag);
uint8_t getAnomaly(AnomType flag);

boolean hasAnyAnomaly();
