#include "ssd1306_popher_func.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include <stdio.h>

/**
 * @name        ssd1306_bmp_to_pixel
 * 
 * @param x     starting x position of image.
 * @param y     starting y position of image.
 * @param w     width of image.
 * @param h     height of image.
 * @param buf   buffer that holds bit data of image.
 * 
 * @note        only works for monochrome bitmap images.
 * 
 * @note        the 'buf' parameter should be an array  that holds data
 *              of where there should be an activated pixel or not. Samples
 *              of bitmap array's can be seen in 'ssd1306_aim1_icons.h'.
 */
void ssd1306_bmp_to_pixel(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *buf)
{
  for (uint32_t j = y; j < y + h; j++)
  {
    for (uint32_t i = x; i < x + w; i++)
    {
      uint32_t color_in_pixel;
      color_in_pixel = (i - x) + ((j - y) * w);
      // printf("color index: %u\n", color_in_pixel);
      ssd1306_draw_pixel(i, j, buf[color_in_pixel]);
    }
  }
}