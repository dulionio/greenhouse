#ifndef _CLIMATE_H
#define _CLIMATE_H

#define BME280_32BIT_ENABLE

#include "bme280.h"

class Climate {
public:
  Climate();

private:
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;

  void print_error(const char api_name[], int8_t rslt);
};

#endif
