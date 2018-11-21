#ifndef ACTIVITY_TIMER_USER_H
#define ACTIVITY_TIMER_USER_H

void activity_timer_triggered_user(void);
void activity_timer_reset_user(void);

void activity_timer_init(uint16_t timeout_seconds);
void activity_timer_task(void);
void activity_timer_reset(void);

#endif
