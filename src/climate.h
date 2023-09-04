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

  // Settings

  inline uint8_t getTemperatureOsr() const {
    return settings.osr_t;
  }

  inline uint8_t getHumidityOsr() const {
    return settings.osr_h;
  }

  inline uint8_t getPressureOsr() const {
    return settings.osr_p;
  }

  inline uint8_t getFilter() const {
    return settings.filter;
  }

  inline uint8_t getStandbyTime() const {
    return settings.standby_time;
  }

private:
  struct bme280_dev device = { 0 };
  struct bme280_settings settings = { 0 };
  char temperature[10];
  char humidity[8];
  char pressure[8];

  void chk(int8_t rslt, const char api_name[]);
  void toa(char* dst, size_t len, int dec, int32_t src);

  static BME280_INTF_RET_TYPE bme280_read(
    uint8_t reg_addr,
    uint8_t* reg_data,
    uint32_t length,
    void* intf_ptr);

  static BME280_INTF_RET_TYPE bme280_write(
    uint8_t reg_addr,
    const uint8_t* reg_data,
    uint32_t length,
    void* intf_ptr);

  static void bme280_delay(uint32_t period, void *intf_ptr);
};

#endif
