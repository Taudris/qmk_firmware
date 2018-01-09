/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"
#include "matrix.h"
#include "rgblight_types.h"

/* I2C is required for this layout */
#define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

/* Number of LEDs per side (one side gets mirrored to the other) */
#undef RGBLED_NUM
#define RGBLED_NUM 9

/* Other QMK RGB settings */
#define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 24
#define RGBLIGHT_VAL_STEP 17

/* Do not touch the code below unless you know what you're getting into */
#ifndef ROWS_PER_HAND
#define ROWS_PER_HAND (MATRIX_ROWS/2)
#endif

#define SLAVE_BUFFER_MATRIX_OFFSET (0)
#define SLAVE_BUFFER_MATRIX_SIZE (sizeof(matrix_row_t) * ROWS_PER_HAND)

#define SLAVE_BUFFER_LEDS_OFFSET (SLAVE_BUFFER_MATRIX_SIZE)
#define SLAVE_BUFFER_LEDS_SIZE (RGBLED_NUM * sizeof(LED_TYPE))

#define SLAVE_BUFFER_LEDFLAG_OFFSET (SLAVE_BUFFER_MATRIX_SIZE + SLAVE_BUFFER_LEDS_SIZE)
#define SLAVE_BUFFER_LEDFLAG_SIZE (1)

#define SLAVE_BUFFER_SIZE ( \
  SLAVE_BUFFER_MATRIX_SIZE + \
  SLAVE_BUFFER_LEDS_SIZE + \
  SLAVE_BUFFER_LEDFLAG_SIZE \
)

#endif
