/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _EXTRA01,
    _EXTRA02
};

enum custom_keycodes {
#ifdef VIA_ENABLE
  //QWERTY = USER00,
  BASE = QK_KB_0,
  //QWERTY = CS00, // qmk v1.1.1
#else
  QWERTTY = SAFE_RANGE,
#endif
  LOWER,
  RAISE,
  ADJUST,
  EXTRA01,
  EXTRA02,
  MJMODE,
  SJMODE,
  JOYRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,       KC_U,      KC_I,     KC_O,      KC_P,     KC_BSLS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,       KC_J,      KC_K,     KC_L,      KC_SCLN,  KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,       KC_M,      KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT,
        KC_LCTL, KC_LALT, _______, _______, LOWER,   KC_SPC,      KC_BSPC,    RAISE,     _______,  _______,   KC_LALT,  KC_LCTL,
        _______, _______, _______, _______,_______, _______,      _______,    KC_LEFT,   KC_UP,    KC_ENTER,  KC_DOWN,  KC_RIGHT
    ),

    [1] = LAYOUT(
        QK_BOOT,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,     KC_7,      KC_8,     KC_9,      KC_0,     QK_BOOT,
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,    KC_F8,     KC_F9,    KC_F10,    KC_F11,   KC_F12,
        KC_1,     KC_2,    KC_1,    KC_2,    KC_1,    KC_2,      KC_3,     KC_4,      KC_1,     KC_2,      KC_1,     KC_2,
        QK_BOOT,  _______, _______, KC_2,    KC_1,    KC_2,      KC_3,     KC_4,      _______,  _______,   KC_1,     QK_BOOT,
        _______,  _______, _______, _______, _______, _______,   _______,  KC_LEFT,   KC_UP,    KC_ENTER,  KC_DOWN,  KC_RIGHT
    ),

    [2] = LAYOUT(
        QK_BOOT,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,     KC_7,      KC_8,     KC_9,      KC_0,     QK_BOOT,
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,    KC_F8,     KC_F9,    KC_F10,    KC_F11,   KC_F12,
        KC_1,     KC_2,    KC_1,    KC_2,    KC_1,    KC_2,      KC_3,     KC_4,      KC_1,     KC_2,      KC_1,     KC_2,
        QK_BOOT,  _______, _______, KC_2,    KC_1,    KC_2,      KC_3,     KC_4,      _______,  _______,   KC_1,     QK_BOOT,
        _______,  _______, _______, _______, _______, _______,   _______,  KC_LEFT,   KC_UP,    KC_ENTER,  KC_DOWN,  KC_RIGHT
    ),
    
    [3] = LAYOUT(
        QK_BOOT,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,     KC_7,      KC_8,     KC_9,      KC_0,     QK_BOOT,
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,    KC_F8,     KC_F9,    KC_F10,    KC_F11,   KC_F12,
        KC_1,     KC_2,    KC_1,    KC_2,    KC_1,    KC_2,      KC_3,     KC_4,      KC_1,     KC_2,      KC_1,     KC_2,
        QK_BOOT,  _______, _______, KC_2,    KC_1,    KC_2,      KC_3,     KC_4,      _______,  _______,   KC_1,     QK_BOOT,
        _______,  _______, _______, _______, _______, _______,   _______,  KC_LEFT,   KC_UP,    KC_ENTER,  KC_DOWN,  KC_RIGHT
    )
};

#if 1
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
#else
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
#endif

#if 1
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
         //print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_BASE);
      }
      return false;
      //break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      //break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      //break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      //break;
#if 0
    case MJMODE:
      if (record->event.pressed) {
        joysitck_mode_master_INC();
        user_config.MjMode = MjMode;
        eeconfig_update_user(user_config.raw); 
      }
      //dprintf("mjoymode \n");
      return false;

    case SJMODE:
      if (record->event.pressed) {
        //joysitck_mode_slave_INC();
        zoom_mode_slave_INC();
        user_config.SjMode = SjMode;
        eeconfig_update_user(user_config.raw); 
      }
      return false;

    case JOYRST:
      if (record->event.pressed) {
        JoyOriginReset();
      }
      return false;
#endif
  }
  return true;
}
#endif