#include "climate.h"
#include "hardware/spi.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <cstring>

BME280_INTF_RET_TYPE bme280_read(uint8_t reg_addr, uint8_t* reg_data, uint32_t length, void* intf_ptr);
BME280_INTF_RET_TYPE bme280_write(uint8_t reg_addr, const uint8_t* reg_data, uint32_t length, void* intf_ptr);
void bme280_delay(uint32_t period, void* intf_ptr);
void fmt(char* dst, size_t len, int dec, int32_t num);
void chk(int8_t rslt, const char api_name[]);

Climate::Climate() {
  device.read = bme280_read;
  device.write = bme280_write;
  device.delay_us = bme280_delay;
  device.intf = BME280_SPI_INTF;
  device.intf_ptr = this;
}

void Climate::init() {
  struct bme280_settings settings = { 0 };

  // Use SPI0 at 1MHz for up to 10m
  spi_init(spi0, 1000 * 1000);
  gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

  // Chip select is active-low, so we'll initialise it to a driven-high state
  gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
  gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);

  chk(bme280_init(&device), "bme280_init");

  // Configure indoor navigation settings
  chk(bme280_get_sensor_settings(&settings, &device), "bme280_get_sensor_settings");
  settings.filter = BME280_FILTER_COEFF_16;
  settings.osr_h = BME280_OVERSAMPLING_1X;
  settings.osr_p = BME280_OVERSAMPLING_16X;
  settings.osr_t = BME280_OVERSAMPLING_2X;
  chk(bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &device), "bme280_set_sensor_settings");

  // Calculate delay between forced mode and reading measurement
  chk(bme280_cal_meas_delay(&delay, &settings), "bme280_cal_meas_delay");
}

void Climate::read() {
  struct bme280_data data = { 0 };
  chk(bme280_set_sensor_mode(BME280_POWERMODE_FORCED, &device), "bme280_set_sensor_mode");
  bme280_delay(delay, this);
  chk(bme280_get_sensor_data(BME280_ALL, &data, &device), "bme280_get_sensor_data");
  fmt(temperature, sizeof(temperature), 2, data.temperature);
  fmt(humidity, sizeof(humidity), 3, data.humidity);
  fmt(pressure, sizeof(pressure), 2, data.pressure);
}

BME280_INTF_RET_TYPE bme280_read(uint8_t reg_addr, uint8_t* reg_data, uint32_t length, void* intf_ptr) {
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);
  spi_write_blocking(spi0, &reg_addr, 1);
  spi_read_blocking(spi0, 0, reg_data, length);
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
  return BME280_OK;
}

BME280_INTF_RET_TYPE bme280_write(uint8_t reg_addr, const uint8_t* reg_data, uint32_t length, void* intf_ptr) {
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);
  spi_write_blocking(spi0, &reg_addr, 1);
  spi_write_blocking(spi0, reg_data, length);
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
  return BME280_OK;
}

void bme280_delay(uint32_t period, void* intf_ptr) {
  sleep_us(period);
}

void fmt(char* dst, size_t len, int dec, int32_t num) {
  char buf[len];
  int idx = len - 1;
  int pos = idx - dec - 1;

  buf[idx--] = 0;
  do {
    char ch = '0' + num % 10;
    buf[idx--] = ch;
    if (idx == pos) {
      buf[idx--] = '.';
    }
    num /= 10;
  } while (idx >= 0 && (idx > pos || num != 0));
  strcpy(dst, &buf[idx + 1]);
}

void chk(int8_t rslt, const char api_name[]) {
  if (rslt != BME280_OK) {
    printf("%s\t", api_name);

    switch (rslt) {
    case BME280_E_NULL_PTR:
      printf("Error [%d] : Null pointer error.", rslt);
      printf("It occurs when the user tries to assign value (not address) to a "
        "pointer, which has been initialized to NULL.\r\n");
      break;

    case BME280_E_COMM_FAIL:
      printf("Error [%d] : Communication failure error.", rslt);
      printf("It occurs due to read/write operation failure and also due to "
        "power failure during communication\r\n");
      break;

    case BME280_E_DEV_NOT_FOUND:
      printf("Error [%d] : Device not found error. It occurs when the device "
        "chip id is incorrectly read\r\n",
        rslt);
      break;

    case BME280_E_INVALID_LEN:
      printf("Error [%d] : Invalid length error. It occurs when write is done "
        "with invalid length\r\n",
        rslt);
      break;

    default:
      printf("Error [%d] : Unknown error code\r\n", rslt);
      break;
    }
  }
}
