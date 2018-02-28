#ifndef CONFIG_USER_H
#define CONFIG_USER_H
#include "../../config.h"


#undef IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define ONESHOT_TAP_TOGGLE 2

#define FORCE_NKRO

#undef IS_COMMAND
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) \
)

#define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM false
#define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS false
#define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS false

#undef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 8

#undef RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 64

#undef RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 16

#endif
