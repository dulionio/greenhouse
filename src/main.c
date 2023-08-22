#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

int main() {
  stdio_init_all();

  while (true) {
    printf("Hello World!\n");
    sleep_ms(1000);
  }
}
