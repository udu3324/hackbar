// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _L0 = 0,
    _L1
};

enum custom_keycodes {
    REC_TOG = SAFE_RANGE,     // Alt+F9
    INSTANT_REPLAY,           // Alt+Shift+F10
    RGB_TG,                   // RGB toggle
    RGB_MD,                   // RGB mode cycle
    RGB_BR                    // RGB brightness up
};

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM layer0_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_CYAN},   // Encoder LEDs
    {2, 14, HSV_TEAL}   // Key LEDs
);

const rgblight_segment_t PROGMEM layer1_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_GOLDENROD},
    {2, 14, HSV_MAGENTA}
);

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0_lights,
    layer1_lights
);
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_1x8(
        TG(1),
        KC_Q,
        KC_W,
        KC_E,
        KC_R,
        KC_T,
        KC_Y,
        KC_U
    ),

    [_L1] = LAYOUT_1x8(
        TG(1),
        KC_PSCR,          // screenshot
        REC_TOG,          // record toggle (Alt+F9)
        INSTANT_REPLAY,   // instant replay (Alt+Shift+F10)
        RGB_TG,           // RGB on/off
        RGB_MD,           // cycle RGB effects
        RGB_BR,           // increase brightness
        LGUI(KC_L)        // lock screen
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case REC_TOG:
            tap_code16(A(KC_F9));
            return false;
        case INSTANT_REPLAY:
            tap_code16(A(S(KC_F10)));
            return false;
#ifdef RGBLIGHT_ENABLE
        case RGB_TG:
            rgblight_toggle();
            return false;
        case RGB_MD:
            rgblight_step();
            return false;
        case RGB_BR:
            rgblight_increase_val();
            return false;
#endif
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
    rgblight_set_layer_state(1, false);
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);  // Start with breathing effect
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _L0));
    rgblight_set_layer_state(1, layer_state_cmp(state, _L1));
    return state;
}
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0) return true;

    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return false;
}