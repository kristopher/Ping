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

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // We give a short LOW pulse beforehand to ensure a clean HIGH pulse.
  pinMode(_sig_pin, OUTPUT);
  digitalWrite(_sig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_sig_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_sig_pin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(_sig_pin, INPUT);
  duration = pulseIn(_sig_pin, HIGH, timeout); // Returns 0 if timeout is reached
  
  // convert the time into a distance
  return (this->*conversion_function)(duration);
}

long Ping::microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long Ping::microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
