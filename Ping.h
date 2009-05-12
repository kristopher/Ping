#ifndef Ping_h

#define Ping_h

class Ping {
  private:
    long microsecondsToInches(long);
    int _sig_pin;
  public:
    Ping(int);
    long read();
};

#endif