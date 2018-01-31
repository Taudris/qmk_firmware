NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
RGBLIGHT_CUSTOM_DRIVER = yes
SRC += overlay.c \
       overlay_effect.c \
       lighting.c \
       ws2812.c
