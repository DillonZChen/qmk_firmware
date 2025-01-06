#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER0 1
#define _LOWER1 2
#define _RAISE 3
#define _ADJUST 4

#define _LOWER_TAP_TIME 200

enum custom_keycodes {
    /* layers */
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,

    /* macros */
    UNDO,
    REDO,
    TM_COPY,  // terminal copy
    TM_PSTE,  // terminal paste
    // snap windows
    WN_UP,
    WN_DOWN,
    WN_LEFT,
    WN_RGHT,
    // manipulate workspaces
    WS_UP,
    WS_DOWN,
    WS_LEFT,
    WS_RGHT, 
};

bool lower0_up = false;
bool lower0_tapped = false;
uint16_t lower_tap_timer = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_HOME,          KC_END,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, LOWER,   KC_ENT,                    KC_SPC,  RAISE,   KC_RALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER0] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_SPC,  KC_PGUP, KC_EQL , KC_UP,   KC_PLUS, KC_MINS,                            KC_UNDS, _______, KC_LBRC, KC_RBRC, _______, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,                            _______, _______, KC_LCBR, KC_RCBR, KC_COLN, KC_DQUO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, UNDO,    REDO,    TM_COPY, TM_PSTE, _______, _______,          _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,  _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, QK_BOOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, WN_UP,   _______, KC_F11,                             KC_F12,  _______, _______, _______, KC_PSCR, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, WN_LEFT, WN_DOWN, WN_RGHT, _______,                            _______, _______, KC_LBRC, KC_RBRC, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, KC_END,           _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, WS_UP,   _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, _______, WS_LEFT, WS_DOWN, WS_RGHT, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* layers*/
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                if (!lower0_tapped) {
                    layer_on(_LOWER0);
                    update_tri_layer(_LOWER0, _RAISE, _ADJUST);
                    lower0_up = true;
                } else {
                    layer_on(_LOWER1);
                }
            } else {
                if (lower0_up) {
                    lower0_up = false;
                    layer_off(_LOWER0);
                    update_tri_layer(_LOWER0, _RAISE, _ADJUST);
                    lower0_tapped = true;
                    lower_tap_timer = timer_read();
                } else {
                    layer_off(_LOWER1);
                }
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER0, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER0, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        
        /* macros */
        case UNDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_Z)));
            }
            return false;
        case REDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_Z))));
            }
            return false;
        case TM_COPY:
            // this does not work in terminal
            // if (record->event.pressed) {
            //     SEND_STRING(SS_LCTL(SS_LSFT("c")));
            // }
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_C);
                unregister_code(KC_C);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
        case TM_PSTE:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_V);
                unregister_code(KC_V);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
        case WN_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_UP)));
            }
            return false;
        case WN_DOWN:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
            }
            return false;
        case WN_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
            }
            return false;
        case WN_RGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
            }
            return false;
        case WS_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_UP))));
            }
            return false;
        case WS_DOWN:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DOWN))));
            }
            return false;
        case WS_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_LEFT))));
            }
            return false;
        case WS_RGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_RGHT))));
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (lower0_tapped) {
    if (timer_elapsed(lower_tap_timer) > _LOWER_TAP_TIME) {
      lower0_tapped = false;
    }
  }
}
