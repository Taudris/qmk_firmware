#ifndef OVERLAY_EFFECT_USER_H
#define OVERLAY_EFFECT_USER_H

enum overlay_effects {
  OVERLAY_EFFECT_NONE = 0,
  OVERLAY_EFFECT_STROBE_AND_BREATHE
};

void overlay_effect_set(uint16_t hue, uint8_t sat, uint8_t effect);
void overlay_effect_set_effect(uint8_t effect);
void overlay_effect_clear(void);

void overlay_effect_task(void);

#endif
