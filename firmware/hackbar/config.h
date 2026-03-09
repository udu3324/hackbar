// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS

// Map logical LED order to physical WS2812 index order (0-based):
// encoder: 1,2
// key 1: 3,16
// key 2: 4,15
// key 3: 5,14
// key 4: 6,13
// key 5: 7,12
// key 6: 8,11
// key 7: 9,10
#define RGBLIGHT_LED_MAP {0, 1, 2, 15, 3, 14, 4, 13, 5, 12, 6, 11, 7, 10, 8, 9}

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT