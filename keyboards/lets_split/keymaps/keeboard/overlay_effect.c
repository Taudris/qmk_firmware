#include "quantum.h"
#include "overlay_effect.h"
#include "overlay.h"
#include "rgblight.h"
#include "led_tables.h"

extern rgblight_config_t rgblight_config;

static bool is_set = false, is_dirty = false;
static uint16_t color_hue = 0;
static uint8_t color_sat = 0, overlay_effect = OVERLAY_EFFECT_NONE;

void overlay_effect_set(uint16_t hue, uint8_t sat, uint8_t effect) {
  color_hue = hue;
  color_sat = sat;
  overlay_effect = effect;
  is_set = true;
  is_dirty = true;
}

void overlay_effect_set_effect(uint8_t effect) {
  overlay_effect = effect;
  is_set = true;
  is_dirty = true;
}

void overlay_effect_clear(void) {
  if (is_set) {
    is_set = false;
    overlay_clear();
  }
}

inline static uint8_t multiply_scalar(uint8_t a, uint8_t b) {
  //0 = 0.0, 255 = 1.0
  uint16_t mul = (uint16_t)a * (uint16_t)b;
  mul += (a >> 1) + (b >> 1);
  return (uint8_t)(mul >> 8);
}

void overlay_effect_task(void) {
  static uint16_t timer_last = 0;
  static uint8_t effect_state = 0, effect_brightness = 255, last_val;

  uint8_t val;

  if (!is_set) { return; }

  if (is_dirty) {
    timer_last = timer_read();
    effect_state = 0;
    effect_brightness = 255;
  }

  val = rgblight_config.val;
  if (val < 20) {
    val = 20;
  }

  //determine brightness and multiply
  switch (overlay_effect) {
    case OVERLAY_EFFECT_NONE: break;

    case OVERLAY_EFFECT_STROBE_AND_BREATHE: {
      //strobe
      //repeat 5x: 2 seconds to fade in, 2 seconds to fade out

      uint16_t last_elapsed = timer_elapsed(timer_last);

      switch (effect_state) {
        default:
          effect_state = 0;
        case 0: //strobe off #1
        case 2: //strobe off #2
          effect_brightness = 0;
          if (last_elapsed >= 100) {
            timer_last = timer_read();
            effect_state++;
          }
          break;

        case 1: //strobe on #1
        case 3: //strobe on #2
          effect_brightness = 255;
          if (last_elapsed >= 100) {
            timer_last = timer_read();
            effect_state++;
          }
          break;

        case 4: //fade out #1
        case 6:
        case 8: //fade out #3
          if (last_elapsed > 8) {
            timer_last = timer_read();
            while (last_elapsed > 8) {
              if (effect_brightness == 128) {
                effect_state++;
                break;
              }
              effect_brightness--;
              last_elapsed -= 8;
            }
          }
          break;

        case 5: //fade in #1
        case 7:
        case 9: //fade in #3
          if (last_elapsed > 8) {
            timer_last = timer_read();
            while (last_elapsed > 8) {
              if (effect_brightness == 255) {
                effect_state++;
                break;
              }
              effect_brightness++;
              last_elapsed -= 8;
            }
          }
          break;
      }
      break;
    }
  }

  if (effect_brightness == 0) {
    val = 0;
  } else if (effect_brightness < 255) {
    val = multiply_scalar(val, effect_brightness);
  }

  if (is_dirty || last_val != val) {
    last_val = val;
    overlay_set_val(color_hue, color_sat, val);
  }

  is_dirty = false;
}
