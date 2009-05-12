#include "WConstants.h"
#include "Ping.h"

Ping::Ping(int sig_pin) {
  _sig_pin = sig_pin;
}

long Ping::read(int timeout) {
  long duration, inches;

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
  duration = pulseIn(_sig_pin, HIGH, timeout);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
 
  return inches;
}

long Ping::microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
