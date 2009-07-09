/*
  Modified version of the Ping.pde example that is packaged with the Arduino IDE 
  License:  GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
  Copyright: 2009 Kristopher Chambers <kristopher.chambers@gmail.com>
  Date: 7/9/2009
*/

#include "WConstants.h"
#include "Ping.h"

Ping::Ping(int sig_pin, int units) {
  _sig_pin = sig_pin;
  _units = units;
  if (units == INCHES) {
    conversion_function = &Ping::microsecondsToInches;
  } else {
    conversion_function = &Ping::microsecondsToCentimeters;    
  }
}

long Ping::read(int timeout) {
  long duration;

  pinMode(_sig_pin, OUTPUT);
  digitalWrite(_sig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_sig_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_sig_pin, LOW);

  pinMode(_sig_pin, INPUT);
  duration = pulseIn(_sig_pin, HIGH, timeout); // Returns 0 if timeout is reached
  
  return (this->*conversion_function)(duration);
}

long Ping::microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long Ping::microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
