#include "ergodox_ez.h"
#include "ws2812.h"
#include "ledbbtwi.h"
#include "led_tables.h"

extern rgblight_config_t rgblight_config;

static bool is_lighting_dirty = false;

__attribute__ ((weak))
void lighting_task_user(LED_TYPE* frame) {
}

__attribute__ ((weak))
void lighting_transform_user(LED_TYPE* frame) {
}

void rgblight_set(void) {
  is_lighting_dirty = true;
}

void lighting_task(void) {
  if (!is_lighting_dirty) { return; }

  LED_TYPE frame[RGBLED_NUM];

  if (rgblight_config.enable) {
    memcpy(frame, led, sizeof(led));
  } else {
    memset(frame, 0, sizeof(frame));
  }

  lighting_task_user(frame);

  //apply gamma
  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    frame[i].r = pgm_read_byte(&CIE1931_CURVE[frame[i].r]);
    frame[i].g = pgm_read_byte(&CIE1931_CURVE[frame[i].g]);
    frame[i].b = pgm_read_byte(&CIE1931_CURVE[frame[i].b]);
    #ifdef RGBW
    frame[i].w = pgm_read_byte(&CIE1931_CURVE[frame[i].w]);
    #endif
  }

  lighting_transform_user(frame);

  is_lighting_dirty = false;

  //send to leds
  ledbbtwi_setleds(frame, RGBLED_NUM);
  ws2812_setleds(frame, RGBLED_NUM);
}
