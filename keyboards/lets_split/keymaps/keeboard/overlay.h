#ifndef OVERLAY_USER_H
#define OVERLAY_USER_H

#include "rgblight_types.h"

void overlay_color_set(uint8_t hue, uint8_t sat);
void overlay_color_clear(void);

void overlay_apply(LED_TYPE* frame);

#endif
