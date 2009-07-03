#ifndef Ping_h
#define Ping_h
#define INCHES 1
#define CENTIMETERS 2

class Ping {
  private:
    long microsecondsToInches(long);
    long microsecondsToCentimeters(long);
    int _sig_pin;
    int _units;
    long (Ping::*conversion_function)(long);
  public:
    Ping(int sig_pin, int units = INCHES);
    long read(int timeout = 20000);
};

#endif