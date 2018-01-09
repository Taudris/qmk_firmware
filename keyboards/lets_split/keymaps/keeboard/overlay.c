#include "lets_split.h"
#include "overlay.h"
#include "rgblight.h"

extern rgblight_config_t rgblight_config;

static uint8_t is_overlay_color_set, overlay_color_hue, overlay_color_sat;

void overlay_color_set(uint8_t hue, uint8_t sat) {
  overlay_color_hue = hue;
  overlay_color_sat = sat;
  is_overlay_color_set = 1;
  rgblight_set();
}

void overlay_color_clear(void) {
  is_overlay_color_set = 0;
  rgblight_set();
}

void overlay_apply(LED_TYPE* frame) {
  if (is_overlay_color_set) {
    uint8_t val = rgblight_config.val;
    if (val < 20) {
      val = 20;
    }

    LED_TYPE overlay_color;
    sethsv(overlay_color_hue, overlay_color_sat, val, &overlay_color);

    memcpy(&frame[0], &overlay_color, sizeof(LED_TYPE));
    memcpy(&frame[1], &overlay_color, sizeof(LED_TYPE));
    memcpy(&frame[RGBLED_NUM-2], &overlay_color, sizeof(LED_TYPE));
    memcpy(&frame[RGBLED_NUM-1], &overlay_color, sizeof(LED_TYPE));
  }
}
