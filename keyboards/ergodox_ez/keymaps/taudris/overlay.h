#ifndef OVERLAY_USER_H
#define OVERLAY_USER_H

#include "rgblight_types.h"

void overlay_set(uint16_t hue, uint8_t sat);
void overlay_set_val(uint16_t hue, uint8_t sat, uint8_t val);
void overlay_clear(void);

void overlay_apply(LED_TYPE* frame);

#endif
