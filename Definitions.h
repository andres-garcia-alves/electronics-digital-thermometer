#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// digit selector pins
#define DISPLAY_DIGIT_0   13
#define DISPLAY_DIGIT_1   10
#define DISPLAY_DIGIT_2   9
#define DISPLAY_DIGIT_3   3

// display segment pins
#define DISPLAY_LED_A     12
#define DISPLAY_LED_B     2
#define DISPLAY_LED_C     5
#define DISPLAY_LED_D     7
#define DISPLAY_LED_E     8
#define DISPLAY_LED_F     A4
#define DISPLAY_LED_G     4
#define DISPLAY_LED_DOT   6

// DHT sensor type & pins
#define SENSOR_TYPE       DHT11
#define SENSOR_DHT_VCC    A0
#define SENSOR_DHT_DATA   A5

#define MODE_INTERVAL     6000
#define SENSOR_INTERVAL   MODE_INTERVAL * 3

// data structures
struct SensorMeasure {
  bool valid = true;
  float temperature = 0;
  float heatIndex = 0;
  float humidity = 0;
} sensorMeasure;

struct DisplayText {
  String temperature = " 00c";
  String heatIndex = " 00C";
  String humidity = " 0 h";
  byte temperatureDotPos = 1;
  byte heatIndexDotPos = 1;
  byte humidityDotPos = -1;
} displayText;

enum eDataMode { NONE, TEMPERATURE, HEAT_INDEX, HUMIDITY };

#endif
