#ifndef _CLIMATE_H
#define _CLIMATE_H

#include "bme280.h"

class Climate {
public:
  Climate();
  void init();
  void read();

  inline const char* getTemperature() const {
    return temperature;
  }

  inline const char* getHumidity() const {
    return humidity;
  }

  inline const char* getPressure() const {
    return pressure;
  }

private:
  struct bme280_dev device = { 0 };
  char temperature[6] = { 0 };
  char humidity[8] = { 0 };
  char pressure[8] = { 0 };
  uint32_t delay = 0;
};

#endif
