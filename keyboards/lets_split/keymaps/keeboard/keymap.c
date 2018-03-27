#include "lets_split.h"
#include "action_layer.h"
#include <quantum.h>
#include "eeconfig.h"
#include "lighting.h"
#include "overlay.h"
#include "split_util.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _HYPER 1
#define _GAME 2
#define _RAISE 13
#define _LOWER 14
#define _COMBO 15
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  HYPER,
  GAME,
  RAISE,
  LOWER,
  COMBO,
  ADJUST,
  FLSHRST, //reset key that flashes the leds first
  RGB_SLD
};

#define MONOFF LCTL(LSFT(KC_S))
#define CTALDEL LCTL(LALT(KC_DEL))
#define H(kc) LCTL(LSFT(LALT(LGUI(kc))))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------. ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  | |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |SftCap|   Z  |   X  |   C  |   V  |   B  | |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl | GUI  |MonOff|CtAlDl|Lower |Space | |Space |Raise | Vol- | Vol+ | RAlt |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_ESC,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    /*  */ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    /*  */ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  LSFT_T(KC_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    /*  */ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
  KC_LCTL,         KC_LGUI, MONOFF,  CTALDEL, LOWER,   KC_SPC,  /*  */ KC_SPC,  RAISE,   KC_VOLD, KC_VOLU, KC_RALT, ADJUST \
),

/* Hyper
 * ,-----------------------------------------. ,-----------------------------------------.
 * | Esc  | HypQ | HypW | HypE | HypR | HypT | | HypY | HypU | HypI | HypO | HypP | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  | HypA | HypS | HypD | HypF | HypG | | HypH | HypJ | HypK | HypL | Hyp; | Hyp' |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift| HypZ | HypX | HypC | HypV | HypB | | HypN | HypM | Hyp, | Hyp. | Hyp/ |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl | GUI  |MonOff|CtAlDl|Lower |HypSpc| |HypSpc|Raise | Vol- | Vol+ | RAlt |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_HYPER] = KEYMAP( \
  KC_ESC,  H(KC_Q), H(KC_W), H(KC_E), H(KC_R), H(KC_T), /*  */ H(KC_Y), H(KC_U), H(KC_I),    H(KC_O),   H(KC_P),    KC_BSPC, \
  KC_TAB,  H(KC_A), H(KC_S), H(KC_D), H(KC_F), H(KC_G), /*  */ H(KC_H), H(KC_J), H(KC_K),    H(KC_L),   H(KC_SCLN), H(KC_QUOT), \
  KC_LSFT, H(KC_Z), H(KC_X), H(KC_C), H(KC_V), H(KC_B), /*  */ H(KC_N), H(KC_M), H(KC_COMM), H(KC_DOT), H(KC_SLSH), KC_ENT, \
  KC_LCTL, KC_LGUI, MONOFF,  CTALDEL, LOWER, H(KC_SPC), /*  */ H(KC_SPC), RAISE, KC_VOLD,    KC_VOLU,   KC_RALT,    ADJUST \
),

/* Game
 * ,-----------------------------------------. ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  | |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl | GUI  |MonOff|CtAlDl|Lower |Space | |Space |Raise | Vol- | Vol+ | RAlt |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_GAME] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    /*  */ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    /*  */ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    /*  */ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
  KC_LCTL, KC_LGUI, MONOFF,  CTALDEL, LOWER,   KC_SPC,  /*  */ KC_SPC,  RAISE,   KC_VOLD, KC_VOLU, KC_RALT, ADJUST \
),

/* Raise
 * ,-----------------------------------------. ,-----------------------------------------.
 * |   ~  |   ?  |   !  |   @  |   #  |      | |   [  |   ]  | PgUp |   -  |   =  | Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |   _  |   $  |   %  |   ^  |      | |      | Home | PgDn | End  |      |   |  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|      |   &  |   *  |   (  |   )  | |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl |      |      |      |Lower |Space | |Space |Raise |MNext |MPlay | RAlt |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_TILD, KC_QUES, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX, /*  */ KC_LBRC, KC_RBRC, KC_PGUP, KC_MINS, KC_EQL,  KC_DEL, \
  KC_TAB,  KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, XXXXXXX, /*  */ XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, KC_PIPE, \
  KC_LSFT, XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, /*  */ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT, \
  KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   KC_SPC,  /*  */ KC_SPC,  RAISE,   KC_MNXT, KC_MPLY, KC_RALT, ADJUST \
),

/* Lower
 * ,-----------------------------------------. ,-----------------------------------------.
 * |   `  |      |      |  Up  |      |      | |      |   7  |   8  |   9  |   =  | Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |      | Left | Down |Right |      | |   +  |   4  |   5  |   6  |   *  |   \  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      | |   -  |   1  |   2  |   3  |   /  |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl |      |      |      |Lower |Space | |   0  |Raise |      |   .  | RAlt |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_GRV,  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, /*  */ XXXXXXX, KC_7,    KC_8,    KC_9,   KC_EQL,  KC_DEL, \
  KC_TAB,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, /*  */ KC_PLUS, KC_4,    KC_5,    KC_6,   KC_ASTR, KC_BSLS, \
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /*  */ KC_MINS, KC_1,    KC_2,    KC_3,   KC_SLSH, KC_ENT, \
  KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   KC_SPC,  /*  */ KC_0,    RAISE,   XXXXXXX, KC_DOT, KC_RALT, ADJUST \
),

/* Combo
 * ,-----------------------------------------. ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |Lower |      | |      |Raise |      |      |      |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_COMBO] = KEYMAP( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   /*  */ KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /*  */ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /*  */ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   XXXXXXX, /*  */ XXXXXXX, RAISE,   XXXXXXX, XXXXXXX, XXXXXXX, ADJUST \
),

/* Adjust
 * ,-----------------------------------------. ,-----------------------------------------.
 * |      |      |      |      |      |      | |      |      |      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |RGBMod|      |      |      |      |      | |      |Qwerty|Hyper |Game  |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |RGBSld|RGBTog|      |      |      |      | |      |      |      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Hue- | Hue+ | Bri- | Bri+ |Lower |      | |Reset |Raise |      |      |      |Adjust|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /*  */ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /*  */ XXXXXXX, QWERTY,  HYPER,   GAME,    XXXXXXX, XXXXXXX, \
  RGB_SLD, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /*  */ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, LOWER,   XXXXXXX, /*  */ FLSHRST, RAISE,   XXXXXXX, XXXXXXX, XXXXXXX, ADJUST \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#define LIGHTING_LAYER_EXCLUSIONS (1UL<<_ADJUST)

uint32_t layer_state_set_user(uint32_t state) {
  uint32_t lighting_layer_state = (state | default_layer_state) & ~LIGHTING_LAYER_EXCLUSIONS;
  uint32_t highest_layer = biton32(lighting_layer_state);
  switch (highest_layer) {
    case _QWERTY:
      overlay_color_clear(); //no color
      break;
    case _HYPER:
      overlay_color_set(96, 255); //yellowish green
      break;
    case _GAME:
      overlay_color_set(0, 255); //blood red
      break;
    case _RAISE:
      overlay_color_set(160, 255); //teal
      break;
    case _LOWER:
      overlay_color_set(232, 255); //blue
      break;
    case _COMBO:
      overlay_color_set(32, 255); //orange
      break;
    //case _ADJUST: excluded
  }
  return state;
}

inline void layer_state_change(void) {
  layer_state_set_user(layer_state);
}

static uint16_t last_keycode;

bool process_record_user_internal(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
        layer_state_change();
      }
      return false;
    case HYPER:
      if (record->event.pressed) {
        default_layer_set(1UL<<_HYPER);
        layer_state_change();
      }
      return false;
    case GAME:
      if (record->event.pressed) {
        default_layer_set(1UL<<_GAME);
        layer_state_change();
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_LOWER)) {
          layer_off(_LOWER);
        } else {
          layer_on(_LOWER);
        }
      } else {
        if (last_keycode != LOWER) {
          layer_off(_LOWER);
        }
      }
      update_tri_layer(_LOWER, _RAISE, _COMBO);
      return false;
    case RAISE:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_RAISE)) {
          layer_off(_RAISE);
        } else {
          layer_on(_RAISE);
        }
      } else {
        if (last_keycode != RAISE) {
          layer_off(_RAISE);
        }
      }
      update_tri_layer(_LOWER, _RAISE, _COMBO);
      return false;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
    case FLSHRST:
      rgblight_timer_disable();
      rgblight_config.enable = 1;
      overlay_color_clear();
      rgblight_setrgb(255, 0, 0);
      lighting_task();
      _delay_ms(100);
      rgblight_setrgb(0, 0, 0);
      lighting_task();
      _delay_ms(100);
      rgblight_setrgb(255, 0, 0);
      lighting_task();
      _delay_ms(100);
      rgblight_setrgb(0, 0, 0);
      lighting_task();
      _delay_ms(100);
      rgblight_setrgb(255, 0, 0);
      lighting_task();
      _delay_ms(100);
      rgblight_setrgb(0, 0, 0);
      lighting_task();
      reset_keyboard();
      return false;
    case RGB_SLD:
      #ifdef RGBLIGHT_ENABLE
      rgblight_mode(1);
      #endif
      return false;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = process_record_user_internal(keycode, record);
  last_keycode = keycode;
  return result;
}

void matrix_scan_user() {
  lighting_task();
}

void matrix_slave_scan_user() {
  lighting_slave_task();
}

uint8_t caps_lock_state = 0;

void led_set_user(uint8_t usb_led) {
  uint8_t new_caps_lock_state;

  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    new_caps_lock_state = 1;
  } else {
    new_caps_lock_state = 0;
  }

  if (new_caps_lock_state != caps_lock_state) {
    caps_lock_state = new_caps_lock_state;
    rgblight_set();
  }
}

void lighting_task_user(LED_TYPE* frame) {
  overlay_apply(frame);

  if (caps_lock_state) {
    uint8_t val = rgblight_config.val;
    if (val < 20) {
      val = 20;
    }
    sethsv(0, 255, val, &frame[0]);
  }
}

void lighting_transform_user(LED_TYPE* frame) {
  LED_TYPE temp;
  memcpy(&temp, &frame[0], sizeof(LED_TYPE));
  memcpy(&frame[0], &frame[2], sizeof(LED_TYPE));
  memcpy(&frame[2], &temp, sizeof(LED_TYPE));
}
