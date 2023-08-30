#include "climate.h"
#include <stdio.h>

Climate::Climate() {
  int8_t rslt;

  rslt = bme280_init(&dev);
}

/*!
 *  @brief Prints the execution status of the APIs.
 */
void Climate::print_error(const char api_name[], int8_t rslt) {
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
