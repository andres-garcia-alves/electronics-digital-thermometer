#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// digit selector pins
#define DISPLAY_DIGIT_0   11
#define DISPLAY_DIGIT_1   2
#define DISPLAY_DIGIT_2   3
#define DISPLAY_DIGIT_3   5

// display segment pins
#define DISPLAY_LED_A     12
#define DISPLAY_LED_B     4
#define DISPLAY_LED_C     7
#define DISPLAY_LED_D     9
#define DISPLAY_LED_E     10
#define DISPLAY_LED_F     13
#define DISPLAY_LED_G     6
#define DISPLAY_LED_DOT   8

// DHT sensor type & pins
#define SENSOR_TYPE       DHT11
#define SENSOR_DHT_VCC    A0
#define SENSOR_DHT_OUT    A5

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
