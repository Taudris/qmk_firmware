#ifndef QMK_KEYBOARD_H
#define QMK_KEYBOARD_H "quantum.h"
#endif

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "config.h"
#include "activity_timer.h"
#include "lighting.h"
#include "overlay_effect.h"
#include "overlay.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define NAVI 3 // navigation keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  KC_RESET
};

#define KC_RESET_WIN_GRAPHICS_DRIVER LCTL(LSFT(LGUI(KC_B)))
#define KC_RWGD KC_RESET_WIN_GRAPHICS_DRIVER

#define KC_LOCK_SLEEP LCTL(LSFT(LALT(KC_L)))
#define KC_LKSL KC_LOCK_SLEEP

#define KC_SECURE_ATTENTION_SIGNAL LCTL(LALT(KC_DEL))
#define KC_SAS KC_SECURE_ATTENTION_SIGNAL

#define KC_THUMB_DOWN LCTL(LSFT(KC_2))
#define KC_TD KC_THUMB_DOWN

#define KC_THUMB_UP LCTL(LSFT(KC_1))
#define KC_TU KC_THUMB_UP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Escape |   1  |   2  |   3  |   4  |   5  |C+A+Hm|           |C+A+Dl|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  | LGui |           | RGui |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | SYMB   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | Enter  |
 * |--------+------+------+------+------+------| LSft |           | RSft |------+------+------+------+------+--------|
 * |LSh/Caps|   Z  |   X  |   C  |   V  |   B  | +Tab |           | +Tab |   N  |   M  |  Up  |   ,  |   .  |RSh/Caps|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Grv |  F4  |  F5  |  F2  |  F3  |                                       | Left | Down | Right| NAVI | MDIA |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Esc  | App  |       | App  | Esc  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LAlt |       | RSft |      |      |
 *                                 | Space| Tab  |------|       |------| Bksp |Enter |
 *                                 |      |      | LCtl |       | RCtl |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
  // left hand
     KC_ESC,   KC_1,    KC_2,     KC_3,     KC_4,     KC_5,     LCTL(LALT(KC_HOME)),
     KC_DELT,  KC_Q,    KC_W,     KC_E,     KC_R,     KC_T,     KC_LGUI,
  MO(SYMB),    KC_A,    KC_S,     KC_D,     KC_F,     KC_G,
     KC_LSFT,  KC_Z,    KC_X,     KC_C,     KC_V,     KC_B,     LSFT(KC_TAB),
     KC_GRV,   KC_F4,   KC_F5,    KC_F2,    KC_F3,

  KC_ESC,  KC_APP,
  KC_LALT,
  KC_SPC,  KC_TAB,  KC_LCTL,

  // right hand
       KC_SAS,   KC_6,     KC_7,     KC_8,     KC_9,        KC_0,            KC_MINS,
       KC_RGUI,  KC_Y,     KC_U,     KC_I,     KC_O,        KC_P,            KC_BSLS,
                 KC_H,     KC_J,     KC_K,     KC_L,        KC_SCLN,         KC_QUOT,
  RSFT(KC_TAB),  KC_N,     KC_M,     KC_UP,    KC_COMM,     KC_DOT,   RSFT_T(KC_CAPS),
                           KC_LEFT,  KC_DOWN,  KC_RGHT,  MO(NAVI),        MO(MDIA),

  KC_APP,  KC_ESC,
  KC_RSFT,
  KC_RCTL,  KC_BSPC,  KC_ENT
),

/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |C+S+Es|           |RGui+/|  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   _  |      |           |      |LCtl+Y|   [  |   ]  |   -  |   +  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |LCtl+A|LGui+S|   (  |   )  |   =  |------|           |------|   #  |   <  |   >  |   /  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |LCtl+Z|LCtl+X|LCtl+C|LCtl+V|   -  |      |           |      |      |      |      |   !  |   ?  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,       KC_F1,          KC_F2,          KC_F3,          KC_F4,     KC_F5,    LCTL(LSFT(KC_ESC)),
  KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_LCBR,        KC_RCBR,   KC_UNDS,  KC_TRNS,
  KC_TRNS,  LCTL(KC_A   ),  LGUI(KC_S   ),       KC_LPRN,        KC_RPRN,   KC_EQL,
  KC_TRNS,  LCTL(KC_Z   ),  LCTL(KC_X   ),  LCTL(KC_C   ),  LCTL(KC_V   ),  KC_MINS,  KC_TRNS,
  KC_PSCR,       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

  KC_TRNS,  KC_TRNS,
  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,

  // right hand
  RGUI(KC_SLSH),       KC_F6,     KC_F7,     KC_F8,    KC_F9,    KC_F10,       KC_F11,
       KC_TRNS,   LCTL(KC_Y   ),  KC_LBRC,   KC_RBRC,  KC_MINS,  KC_PLUS,      KC_F12,
                       KC_HASH,   KC_LT,     KC_GT,    KC_SLSH,  KC_ASTR,      KC_TRNS,
       KC_TRNS,        KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_EXLM,  KC_QUES,  OSM(MOD_RSFT),
                                  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,

  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |           |GDvRst|      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Version |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |LckSlp|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |LGuiF4| VolUp|  TU  |  TD  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Prev | VolDn| Next | Play | BASE |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA
[MDIA] = LAYOUT_ergodox(
  KC_RESET,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  VRSN,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

  RGB_MOD,  KC_NO,
  KC_NO,
  RGB_VAD,  RGB_VAI,  KC_TRNS,

  // right hand
  KC_RWGD,  KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_LKSL,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  LGUI(KC_F4),   KC_VOLU,  KC_TU,    KC_TD,    KC_TRNS,
                           KC_MPRV,  KC_VOLD,  KC_MNXT,  KC_MPLY,  KC_TRNS,

  RGB_TOG, RGB_SLD,
  RGB_SAI,
  RGB_SAD, RGB_HUD, RGB_HUI
),

/* Keymap 3: Navigation
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | PgUp |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Home | PgDn | End  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NAVIGATION
[NAVI] = LAYOUT_ergodox(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

  KC_TRNS,  KC_TRNS,
  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,

  // right hand
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PGUP,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                      KC_HOME,  KC_PGDN,  KC_END,   KC_TRNS,  KC_TRNS,

  KC_TRNS,  KC_TRNS,
  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS
),
};


#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool pressed = record->event.pressed;

  if (pressed) {
    {
      uint8_t temp_mod = get_mods();
      uint8_t temp_osm = get_oneshot_mods();
      //turn off capslock when pressing shift to type a shifted key
      if (
        host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) && //capslock on
        (temp_mod & MODS_SHIFT_MASK || temp_osm & MODS_SHIFT_MASK) && //left or right shift pressed
        keycode != KC_CAPS && //key is not capslock
        keycode != KC_LSFT && //key is not left shift
        keycode != KC_RSFT    //key is not right shift
      ) {
        register_code(KC_CAPS);
        unregister_code(KC_CAPS);
      }
    }

    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      case RGB_SLD:
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
        return false;
      case KC_LOCK_SLEEP:
        rgblight_disable();
        break;
      case KC_SAS:
        rgblight_enable();
        break;
      case KC_RESET:
        overlay_effect_clear();
        rgblight_sethsv_noeeprom(0, 0, 0);
        matrix_scan_user();
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        _delay_ms(100);
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
        _delay_ms(100);
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        _delay_ms(100);
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
        _delay_ms(100);
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        _delay_ms(100);
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
        reset_keyboard();
        return false;
      case RGB_MIN ... RGB_MAX:
        if (keycode != RGB_TOG) {
          overlay_effect_clear(); //clear the overlay effect so the user can see the RGB adjustments more clearly
        }
        break;
    }
  }

  activity_timer_reset();

  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  activity_timer_init(30*60);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  activity_timer_task();
  overlay_effect_task();
  lighting_task();
};

static uint8_t last_layer = 0;

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state); //get highest active layer
  switch (layer) {
    case SYMB:
      ergodox_right_led_2_on();
      if (last_layer != layer) { overlay_effect_set(0, 255, OVERLAY_EFFECT_NONE); }
      break;
    case MDIA:
      ergodox_right_led_3_on();
      if (last_layer != layer) { overlay_effect_set(240, 255, OVERLAY_EFFECT_NONE); }
      break;
    /*case NAVI:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      if (last_layer != layer) { overlay_effect_set(120, 255, OVERLAY_EFFECT_NONE); }
      break;*/
    default:
      overlay_effect_clear();
      break;
  }

  last_layer = layer;

  return state;
};

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }
}

void lighting_transform_user(LED_TYPE* frame) {
  #ifdef RGBW
  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    uint8_t min = frame[i].r;
    if (min > frame[i].g) { min = frame[i].g; }
    if (min > frame[i].b) { min = frame[i].b; }
    frame[i].r -= min;
    frame[i].g -= min;
    frame[i].b -= min;
    frame[i].w = min;
  }
  #endif

  overlay_apply(frame);
}
