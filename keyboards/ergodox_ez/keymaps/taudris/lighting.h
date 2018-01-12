#ifndef LIGHTING_USER_H
#define LIGHTING_USER_H

#include "rgblight_types.h"

void lighting_task_user(LED_TYPE* frame);
void lighting_transform_user(LED_TYPE* frame);

void lighting_task(void);

#endif
