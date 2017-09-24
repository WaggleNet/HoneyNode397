#include "sensors.h"

DHT dht1(DHT1_DATA, DHT11);
DHT dht2(DHT2_DATA, DHT11);

void initSensors() {
    pinMode(INTRUSION, INPUT_PULLUP);
    dht1.begin();
    dht2.begin();
}

readouts_t getSensorReadouts() {
    float t1 = dht1.readTemperature();
    float t2 = dht2.readTemperature();
    float h1 = dht1.readHumidity();
    float h2 = dht2.readHumidity();
    auto d1_kaput = isnan(t1) || isnan(h1);
    auto d2_kaput = isnan(t2) || isnan(h2);
    readouts_t readouts;
    writeAnomaly(AN_DHT1DOWN, d1_kaput);
    writeAnomaly(AN_DHT2DOWN, d2_kaput);
    if (d1_kaput && d2_kaput) return readouts;
    if (d1_kaput) {
        readouts.temp = t2;
        readouts.humid = h2;
    } else if (d2_kaput) {
        readouts.temp = t1;
        readouts.humid = h1;
    } else {
        readouts.temp = (t1 + t2) / 2;
        readouts.humid = (h1 + h2) / 2;
    }
    return readouts;
}
