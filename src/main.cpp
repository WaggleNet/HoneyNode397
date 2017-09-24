#include "HoneyNode.h"
#include "Ticker.h"
#include "custom_types.h"
#include "sensors.h"
#include "power.h"
#include "anomaly.h"

HoneyNode honey(7,8);

void reportReadouts() {
    auto readouts = getSensorReadouts();
    auto result = honey.Send(CH_READOUTS, readouts);
    if (result != 0) Serial.println("Problem Sending");
}

void reportPower() {
    return;
}

void reportAnomaly() {
    if (hasAnyAnomaly) {
        honey.Send(CH_ANOMALY, anomaly_flags);
        clearAnomaly(AN_INTRUSION); // Intrusion is a one-off alarm
    }
}

Ticker readoutTimer(reportReadouts, 2000);
Ticker powerTimer(reportPower, 10000);
Ticker anomalyTimer(reportAnomaly, 5000);

void setup() {
    // Setting up everything
    Serial.begin(115200);
    Serial.setTimeout(5000);
    initSensors();
    pinMode(BTN_RESET, INPUT_PULLUP);

    // Configure Net
    honey.begin();
    honey.AddChannel(CH_ANOMALY, uint32_t);
    honey.AddChannel(CH_READOUTS, readouts_t);
    honey.AddChannel(CH_POWER, power_t);

    // Begin Operations
    readoutTimer.start();
    powerTimer.start();
    anomalyTimer.start();
}

void loop() {
    honey.update();
    readoutTimer.update();
    powerTimer.update();
    anomalyTimer.update();
}
