#include "anomaly.h"

anomaly_t anomaly_flags;

uint8_t * getAnomalyItem(AnomType flag) {
    switch (flag) {
        case AN_INTRUSION:
            return &(anomaly_flags.intrusion);
        case AN_DHT1DOWN:
            return &(anomaly_flags.dht1_down);
        case AN_DHT2DOWN:
            return &(anomaly_flags.dht2_down);
        case AN_LOWBATT:
            return &(anomaly_flags.low_batt);
    }
}

void setAnomaly(AnomType flag) {
    auto item = getAnomalyItem(flag);
    *item = 1;
}

void writeAnomaly(AnomType flag, uint8_t value) {
    auto item = getAnomalyItem(flag);
    *item = value;
}

uint8_t getAnomaly(AnomType flag) {
    auto item = getAnomalyItem(flag);
    return (* item);
}

void clearAnomaly(AnomType flag) {
    auto item = getAnomalyItem(flag);
    *item = 0;
}

boolean hasAnyAnomaly() {
    return (
        getAnomaly(AN_DHT1DOWN) ||
        getAnomaly(AN_DHT2DOWN) ||
        getAnomaly(AN_INTRUSION) ||
        getAnomaly(AN_LOWBATT)
    );
}
