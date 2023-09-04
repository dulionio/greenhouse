#include "climate.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
  Climate climate;

  stdio_init_all();
  climate.init();

  while (true) {
    time_us_64() / 10000;
    climate.read();
    printf(
      "Temperature: %s, Humidity: %s, Pressure: %s\n",
      climate.getTemperature(),
      climate.getHumidity(),
      climate.getPressure());
    printf(
      "Temperature OSR: %d, Humidity OSR: %d, Pressure OSR: %d, Filter: %d, Standby Time: %d\n",
      climate.getTemperatureOsr(),
      climate.getHumidityOsr(),
      climate.getPressureOsr(),
      climate.getFilter(),
      climate.getStandbyTime());
    sleep_ms(5000);
  }
}
