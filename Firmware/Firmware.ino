/*
Digital Thermometer v1.4

Created by: Andres Garcia Alves <andres.garcia.alves@gmail.com>
Microcontroller: Arduino Nano (ATMega328 @16Mhz)

Version 1.0, 2022.12.08 - Initial release.
Version 1.1, 2022.12.10 - Re-arrange LEDs pin-out to simplefy PCB.
Version 1.2, 2022.12.11 - Using masked bits to improve character display.
Version 1.3, 2023.03.28 - Use of headers for better readability.
Version 1.4, 2023.04.08 - Hardware re-desing.

This source code is licensed under GPL v3.0

Pinout (4 digit multiplexed 7-segment display):

      ***(A)***
  (F) *       * (B)
      ***(G)***
  (E) *       * (C)
      ***(D)***

D00 -> debug (serial port)
D01 -> debug (serial port)
D02 -> output to F segment of selected digit
D03 -> output to A segment of selected digit
D04 -> output to selector pin for digit 0
D05 -> output to E segment of selected digit
D06 -> output to D segment of selected digit
D07 -> output to dot point of selected digit
D08 -> output to C segment of selected digit
D09 -> output to G segment of selected digit
D10 -> output to selector pin for digit 1
D11 -> output to B segment of selected digit
D12 -> output to selector pin for digit 2
D13 -> output to selector pin for digit 3

*/

#include <DHT.h>
#include "Definitions.h"
#include "Debug.h"
#include "Display_4d.h"


// variables
DHT dht(SENSOR_DHT_DATA, SENSOR_TYPE);

eDataMode dataMode = NONE;
byte currentDigit = 0;

unsigned long int currentMillis = 0;
unsigned long int nextSensorTick = 0;
unsigned long int nextDataModeTick = 0;
byte seansorFailures = 0;


void setup() {

  #if DEBUG
  Serial.begin(9600);
  #endif

  // pins mode
  pinMode(DISPLAY_DIGIT_0, OUTPUT);
  pinMode(DISPLAY_DIGIT_1, OUTPUT);
  pinMode(DISPLAY_DIGIT_2, OUTPUT);
  pinMode(DISPLAY_DIGIT_3, OUTPUT);
  
  pinMode(DISPLAY_LED_A, OUTPUT);
  pinMode(DISPLAY_LED_B, OUTPUT);
  pinMode(DISPLAY_LED_C, OUTPUT);
  pinMode(DISPLAY_LED_D, OUTPUT);
  pinMode(DISPLAY_LED_E, OUTPUT);
  pinMode(DISPLAY_LED_F, OUTPUT);
  pinMode(DISPLAY_LED_G, OUTPUT);
  pinMode(DISPLAY_LED_DOT, OUTPUT);

  // initialize DHT sensor
  pinMode(SENSOR_DHT_VCC, OUTPUT);
  digitalWrite(SENSOR_DHT_VCC, HIGH);
  dht.begin();

  // initial text
  delay(1200);
}


void loop() {

  currentMillis = millis();

  // sensor reading
  if (currentMillis > nextSensorTick) {

    // next sensor reading
    nextSensorTick = currentMillis + SENSOR_INTERVAL;

    // sensor reading
    sensorMeasure = readSensor();
    displayText = buildDisplayText(sensorMeasure);

    #if DEBUG
    updateSerialPort(sensorMeasure);
    #endif
  }

  // data mode
  if (currentMillis > nextDataModeTick) {
    nextDataModeTick = currentMillis + MODE_INTERVAL; // next mode change

    switch (dataMode) {
      case NONE:        dataMode = TEMPERATURE; break;
      case TEMPERATURE: dataMode = HEAT_INDEX;  break;
      case HEAT_INDEX:  dataMode = HUMIDITY;    break;
      case HUMIDITY:    dataMode = TEMPERATURE; break;
    }
  }

  // update display & move to next digit
  updateDisplay(displayText, dataMode, currentDigit);
  currentDigit = (++currentDigit) % 4; // valid range 0-3

  delay(5);
}


SensorMeasure readSensor() {
  SensorMeasure aux;

  aux.temperature = dht.readTemperature();  // temperature (celsius degrees)
  aux.humidity = dht.readHumidity();        // humidity

  // check for sensor-reading errors
  if (isnan(aux.temperature) || isnan(aux.humidity)) {
    aux.valid = false;
    seansorFailures++;
    
    #if DEBUG
    Serial.println("Error obteniendo los datos del sensor DHT11");
    /*aux.valid = true;
    aux.temperature = 88.8;
    aux.heatIndex = 88.8;
    aux.humidity = 0;*/
    #endif

  } else { // calculte heat-index (celsius degrees)
    aux.valid = true;
    seansorFailures = 0;
    aux.heatIndex = dht.computeHeatIndex(aux.temperature, aux.humidity, false);
  }

  return aux;
}


DisplayText buildDisplayText(SensorMeasure sensorMeasure) {
  DisplayText aux;

  if (sensorMeasure.valid) {
    aux.temperature = String(sensorMeasure.temperature, 1);
    aux.temperature.replace(".", "");
    aux.temperature += "c";
    aux.temperatureDotPos = 1;
  
    aux.heatIndex = String(sensorMeasure.heatIndex, 1);
    aux.heatIndex.replace(".", "");
    aux.heatIndex += "C";  
    aux.heatIndexDotPos = 1;
  
    aux.humidity = String(sensorMeasure.humidity, 1);
    aux.humidity.replace(".", "");
    aux.humidity.setCharAt(2, " ");
    aux.humidity += "h";
    aux.humidityDotPos = -1;

  } else {
    String failureText = "----" + String(seansorFailures);
    failureText = failureText.substring(failureText.length() - 4);

    aux.temperature = failureText;
    aux.temperatureDotPos = -1;
    aux.heatIndex = failureText;
    aux.heatIndexDotPos = -1;
    aux.humidity = failureText;
    aux.humidityDotPos = -1;
  }

  return aux;
}
