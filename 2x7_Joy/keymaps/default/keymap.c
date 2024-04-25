#include QMK_KEYBOARD_H
#include <joystick.h>


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {  
    [0] = LAYOUT_ortho_2x7(
        KC_Q,   KC_W,   KC_E,   KC_Y,   KC_U,   KC_I,   KC_O,
        KC_A,   KC_S,   KC_D,   KC_H,   KC_J,   KC_K,   KC_L
    )
};


joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F0, 900, 575, 285),
    JOYSTICK_AXIS_IN(F1, 900, 575, 285), //values can be modified depending on joystick
};

static bool precision = false;
static uint16_t precision_mod = 64;
static uint16_t axis_val = 127;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int16_t precision_val = axis_val;
    if (precision) {
        precision_val -= precision_mod;
    }

    switch (keycode) {
        case KC_P8:
            joystick_set_axis(1, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_P2:
            joystick_set_axis(1, record->event.pressed ? precision_val : 0);
            return false;
        case KC_P4:
            joystick_set_axis(0, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_P6:
            joystick_set_axis(0, record->event.pressed ? precision_val : 0);
            return false;
        case KC_P0:
            precision = record->event.pressed;
            return false;
    }
    return true;
}

