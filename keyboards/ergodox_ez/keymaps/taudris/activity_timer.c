#include "quantum.h"
#include "activity_timer.h"
#include "rgblight.h"

__attribute__ ((weak))
void activity_timer_triggered_user(void) {
  rgblight_disable();
}

__attribute__ ((weak))
void activity_timer_reset_user(void) {
  rgblight_enable();
}

static uint16_t seconds_timeout;
static uint16_t timer_last;
static uint16_t seconds_elapsed;
static bool timer_tripped;


static void set(void) {
  timer_tripped = true;
}

static void reset(void) {
  timer_last = timer_read();
  seconds_elapsed = 0;
  timer_tripped = false;
}


void activity_timer_init(uint16_t timeout_seconds) {
  seconds_timeout = timeout_seconds;
  reset();
}

void activity_timer_task(void) {
  if (timer_tripped) { return; }

  uint16_t timer = timer_read();
  uint16_t elapsed = timer_elapsed(timer_last);

  while (elapsed > 1000) {
    seconds_elapsed++;
    elapsed -= 1000;
    timer_last = timer;
  }

  if (seconds_elapsed >= seconds_timeout) {
    activity_timer_triggered_user();
    set();
  }
}

void activity_timer_reset(void) {
  if (timer_tripped) {
    activity_timer_reset_user();
  }

  reset();
}
