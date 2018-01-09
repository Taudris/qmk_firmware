#ifndef LIGHTING_USER_H
#define LIGHTING_USER_H

#include "rgblight_types.h"

//Implement this to modify LED values on both sides. Processing performed on master and results are sent to the slave.
void lighting_task_user(LED_TYPE* frame);

//Implement this to transform LED values on one or both sides. Processing is performed on both master and slave.
//Slave does not have QMK state information, so only use this to map logical LEDs to physical LEDs.
void lighting_transform_user(LED_TYPE* frame);

void lighting_task(void);
void lighting_slave_task(void);

#endif
