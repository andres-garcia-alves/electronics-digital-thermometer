#ifndef DISPLAY_7S_4D_H
#define DISPLAY_7S_4D_H

void displayCharacter(char, bool);
void displaySegmentsByMaskedBits(byte);


void updateDisplay(DisplayText displayText, eDataMode dataMode, byte currentDigit) {
  char character = ' ';
  bool dotEnabled = false;

  // enable current digit
  digitalWrite(DISPLAY_DIGIT_0, (currentDigit == 0) ? LOW : HIGH); // 1st digit relft to right
  digitalWrite(DISPLAY_DIGIT_1, (currentDigit == 1) ? LOW : HIGH); // 2nd digit relft to right
  digitalWrite(DISPLAY_DIGIT_2, (currentDigit == 2) ? LOW : HIGH); // 3rd digit relft to right
  digitalWrite(DISPLAY_DIGIT_3, (currentDigit == 3) ? LOW : HIGH); // 4th digit relft to right

  // retrieve character for the current digit
  if (dataMode == TEMPERATURE) {
    character = displayText.temperature.charAt(currentDigit);
    dotEnabled = (displayText.temperatureDotPos == currentDigit) ? true : false;
  } else if (dataMode == HEAT_INDEX) {
    character = displayText.heatIndex.charAt(currentDigit);
    dotEnabled = (displayText.heatIndexDotPos == currentDigit) ? true : false;
  } else if (dataMode == HUMIDITY) {
    character = displayText.humidity.charAt(currentDigit);
    dotEnabled = (displayText.humidityDotPos == currentDigit) ? true : false;
  }

  // display character
  displayCharacter(character, dotEnabled);
}


void displayCharacter(char character, bool dotEnabled) {
  byte maskedBits = 0;

  switch(character) {      //.GFEDCBA (0 = OFF, 1 = ON)
    case '0': maskedBits = 0b00111111; break;
    case '1': maskedBits = 0b00000110; break;
    case '2': maskedBits = 0b01011011; break;
    case '3': maskedBits = 0b01001111; break;
    case '4': maskedBits = 0b01100110; break;
    case '5': maskedBits = 0b01101101; break;
    case '6': maskedBits = 0b01111101; break;
    case '7': maskedBits = 0b00000111; break;
    case '8': maskedBits = 0b01111111; break;
    case '9': maskedBits = 0b01100111; break;
    case 'c': maskedBits = 0b01011000; break;
    case 'h': maskedBits = 0b01110100; break;
    case 'C': maskedBits = 0b00111001; break;
    case '-': maskedBits = 0b01000000; break;
    default:  maskedBits = 0b00000000;
  }

  if (dotEnabled) { maskedBits += 0b10000000; }

  displaySegmentsByMaskedBits(maskedBits);
}


// set individuals leds ON/OFF by mask (format: '.GFEDCBA')
void displaySegmentsByMaskedBits(byte maskedBits) {

  digitalWrite(DISPLAY_LED_A, maskedBits & 1);
  digitalWrite(DISPLAY_LED_B, maskedBits & 2);
  digitalWrite(DISPLAY_LED_C, maskedBits & 4);
  digitalWrite(DISPLAY_LED_D, maskedBits & 8);
  digitalWrite(DISPLAY_LED_E, maskedBits & 16);
  digitalWrite(DISPLAY_LED_F, maskedBits & 32);
  digitalWrite(DISPLAY_LED_G, maskedBits & 64);
  digitalWrite(DISPLAY_LED_DOT, maskedBits & 128);
}

#endif
