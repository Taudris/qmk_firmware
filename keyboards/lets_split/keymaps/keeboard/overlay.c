#include "quantum.h"
#include "overlay.h"
#include "rgblight.h"

extern rgblight_config_t rgblight_config;

static bool is_set, is_color_val_set;
static uint16_t color_hue;
static uint8_t color_sat, color_val;

void overlay_set(uint16_t hue, uint8_t sat) {
  is_set = true;
  is_color_val_set = false;
  color_hue = hue;
  color_sat = sat;
  color_val = 0;
  rgblight_set();
}

void overlay_set_val(uint16_t hue, uint8_t sat, uint8_t val) {
  is_set = true;
  is_color_val_set = true;
  color_hue = hue;
  color_sat = sat;
  color_val = val;
  rgblight_set();
}

void overlay_clear(void) {
  is_set = false;
  rgblight_set();
}

void overlay_apply(LED_TYPE* frame) {
  if (is_set) {
    uint8_t val;

    if (is_color_val_set) {
      val = color_val;
    } else {
      val = rgblight_config.val;
      if (val < 20) {
        val = 20;
      }
    }

    LED_TYPE color;
    sethsv(color_hue, color_sat, val, &color);

    memcpy(&frame[0], &color, sizeof(LED_TYPE));
    memcpy(&frame[1], &color, sizeof(LED_TYPE));
    memcpy(&frame[RGBLED_NUM-2], &color, sizeof(LED_TYPE));
    memcpy(&frame[RGBLED_NUM-1], &color, sizeof(LED_TYPE));
  }
}
