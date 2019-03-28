BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = yes # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
NKRO_ENABLE      = yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE   = no  # Unicode
ONEHAND_ENABLE   = no  # Allow swapping hands of keyboard
SLEEP_LED_ENABLE = no
API_SYSEX_ENABLE = no
RGBLIGHT_ENABLE  = yes

RGBLIGHT_CUSTOM_DRIVER = yes
SRC += activity_timer.c \
       lighting.c \
       overlay.c \
       overlay_effect.c \
       ws2812.c
