// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _L0 = 0,
    _L1
};

enum custom_keycodes {
    REC_TG,                   // Alt+F9
    INSTANT_REPLAY,           // Alt+Shift+F10
    RGB_TG,                   // RGB toggle
    RGB_BRI,                  // RGB brightness increase
    RGB_BRD                   // RGB brightness decrease
};

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM layer0_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_CYAN},
    {1, 1, HSV_OFF},
    {2, 14, HSV_CYAN}
);

const rgblight_segment_t PROGMEM layer1_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_OFF},
    {1, 1, HSV_GREEN},
    {2, 14, HSV_GREEN}
);

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0_lights,
    layer1_lights
);
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_1x8(
        TG(1),
        KC_B,     // misc
        KC_LEFT,  // ddr/mania
        KC_DOWN,  // ddr/mania
        KC_UP,    // ddr/mania
        KC_RIGHT, // ddr/mania
        KC_Z,     // osu
        KC_X      // osu
    ),

    [_L1] = LAYOUT_1x8(
        TG(1),
        KC_PSCR,          // screenshot
        KC_PAGE_UP,       // shareX gif record
        KC_PAGE_DOWN,     // shareX video record
        REC_TG,           // nvidia record (Alt+F9)
        INSTANT_REPLAY,   // nvidia instant replay (Alt+Shift+F10)
        RGB_TG,           // rgb on/off
        LGUI(KC_L)        // lock screen
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case REC_TG:
            tap_code16(A(KC_F9));
            return false;
        case INSTANT_REPLAY:
            tap_code16(A(S(KC_F10)));
            return false;
#ifdef RGBLIGHT_ENABLE
        case RGB_TG:
            rgblight_toggle();
            return false;
        case RGB_BRI:
            rgblight_increase_val();
            return false;
        case RGB_BRD:
            rgblight_decrease_val();
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