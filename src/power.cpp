#include "power.h"


float computeVoltage(int pin){
  int sensorValue = analogRead(pin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (1.1*5.3 / 1023.0);
  return voltage;
}

float computePercentage(float voltage){
 float percentage = (voltage-3.45)*208.3-22.9;
 return constrain(percentage,0,100);
}

power_t getPowerReadouts() {
    boolean refFlag = false;
    analogReference(INTERNAL);
    if (!(ADMUX >> REFS1)) {
        analogRead(A6);
        analogRead(A6);
        analogRead(A6);
        analogRead(A6);
        analogRead(A6);
        refFlag = true;
    }   // Get my voltage right

    power_t result;
    result.battery_volt = computeVoltage(BATT_SENS);
    result.solar_volt = computeVoltage(SOLAR_SENS);
    writeAnomaly(AN_LOWBATT, computePercentage(result.battery_volt) < 20);
    // If someone needs higher reference, return it.
    if (refFlag) analogReference(DEFAULT);

    return result;
}
