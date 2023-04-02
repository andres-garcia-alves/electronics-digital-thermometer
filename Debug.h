#ifndef DEBUG_H
#define DEBUG_H

// enable/disable debuging
#define DEBUG       true

#if DEBUG
void updateSerialPort(SensorMeasure sensorMeasure) {

  Serial.print("Temperature: ");
  Serial.print(sensorMeasure.temperature);
  Serial.print("ºC    ");
  Serial.print("Heat-Index: ");
  Serial.print(sensorMeasure.heatIndex);
  Serial.print("ºC    ");
  Serial.print("Humidity: ");
  Serial.print(sensorMeasure.humidity);
  Serial.println("%");
}
#endif

#endif
