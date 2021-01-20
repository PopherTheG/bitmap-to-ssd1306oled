#include <stdio.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

#include "string.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "ssd1306_popher_func.h"
#include "ssd1306_aim1_icons.h"

#define TAG "MAIN.C"

#define I2C_MASTER_PORT SSD1306_I2C_PORT
#define I2C_SDA GPIO_NUM_21
#define I2C_SCL GPIO_NUM_22

/**
 * @brief     This main program showcases how to use the ssd1306_bmp_to_pixel function
 * 
 * @note      This program is dependent on 'https://www.dcode.fr/binary-image' to convert
 *            an image into an array of 1's and 0's
 */

/**
 * @name                    i2c_initialize
 * 
 * @brief                   Initialize an I2C port
 * 
 * @param   mode            Set I2C as MASTER or SLAVE
 * @param   sda_io_num      GPIO number for SDA
 * @param   scl_io_num      GPIO number for SCL
 * @param   sda_pullup_en   Enable or disable pullup
 * @param   scl_pullup_en   Enable or disable pullup
 * @param   clk_speed       Desired clock speed for I2C bus
 * @param   i2c_num         I2C port to use
 */
static void i2c_initialize(i2c_mode_t mode, int sda_io_num, int scl_io_num, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_speed, i2c_port_t i2c_num)
{
  i2c_config_t conf = {
      .mode = mode,
      .sda_io_num = sda_io_num,
      .scl_io_num = scl_io_num,
      .sda_pullup_en = sda_pullup_en,
      .scl_pullup_en = scl_pullup_en,
      .master.clk_speed = clk_speed};
  ESP_ERROR_CHECK(i2c_param_config(i2c_num, &conf));
  ESP_ERROR_CHECK(i2c_driver_install(i2c_num, conf.mode, 0, 0, 0));
}

void app_main(void)
{
  i2c_initialize(I2C_MODE_MASTER, I2C_SDA, I2C_SCL, true, true, 100000, I2C_MASTER_PORT); /* Initalize I2C communication with OLED */
  ssd1306_init();
  while (1)
  {
    ssd1306_bmp_to_pixel(0, 0, 30, 30, humidity_icon_30x30);
    ssd1306_update_screen();
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_bmp_to_pixel(0, 0, 30, 28, heart_icon_30x28);
    ssd1306_update_screen();
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_bmp_to_pixel(0, 0, 115, 64, aim1_decal_115x64);
    ssd1306_update_screen();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
