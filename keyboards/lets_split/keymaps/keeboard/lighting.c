#include "lets_split.h"
#include "split_util.h"
#include "ws2812.h"
#include "i2c.h"
#include "led_tables.h"

extern rgblight_config_t rgblight_config;

static uint8_t is_lighting_dirty = 0;

__attribute__ ((weak))
void lighting_task_user(LED_TYPE* frame) {
}

__attribute__ ((weak))
void lighting_transform_user(LED_TYPE* frame) {
}

void rgblight_set(void) {
  is_lighting_dirty = 1;
}

static uint8_t i2c_transaction(LED_TYPE* frame) {
  uint8_t err;

  err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_WRITE);
  if (err) { goto i2c_error; }

  // go to start of led data
  err = i2c_master_write(SLAVE_BUFFER_LEDS_OFFSET);
  if (err) { goto i2c_error; }

  //write led data
  for (uint8_t i = 0; i < SLAVE_BUFFER_LEDS_SIZE; i++) {
    uint8_t b = ((uint8_t*)(void*)frame)[i];
    err = i2c_master_write(b);
    if (err) { goto i2c_error; }
  }

  //write the led data ready flag
  i2c_master_write(1);

  i2c_master_stop();

  return 0;

i2c_error: // the cable is disconnected, or something else went wrong
  i2c_reset_state();
  return err;
}

void lighting_task(void) {
  if (!is_lighting_dirty) { return; }

  LED_TYPE frame[RGBLED_NUM];
  uint8_t i2c_result;

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

  //send leds to slave
  i2c_result = i2c_transaction(frame);

  //if leds were sent successfully, clear the dirty flag
  if (!i2c_result) {
    is_lighting_dirty = 0;
  }

  //prep frame for local leds
  lighting_transform_user(frame);

  //send to leds
  ws2812_setleds(frame, RGBLED_NUM);
}

void lighting_slave_task(void) {
  LED_TYPE frame[RGBLED_NUM];

  //check led data ready flag
  if (!i2c_slave_buffer[SLAVE_BUFFER_LEDFLAG_OFFSET]) { return; }

  //clear flag before reading buffer
  //if the master sends led data before the loop finishes, doing this first ensures we'll re-read it on the next run
  i2c_slave_buffer[SLAVE_BUFFER_LEDFLAG_OFFSET] = 0;

  //read frame from i2c buffer
  for (uint8_t i = 0; i < SLAVE_BUFFER_LEDS_SIZE; i++) {
    ((uint8_t*)(void*)frame)[i] = i2c_slave_buffer[SLAVE_BUFFER_LEDS_OFFSET+i];
  }

  //prep frame for local leds
  lighting_transform_user(frame);

  //send to leds
  ws2812_setleds(frame, RGBLED_NUM);
}
