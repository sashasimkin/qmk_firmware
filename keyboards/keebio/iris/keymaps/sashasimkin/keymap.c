#include QMK_KEYBOARD_H

/**
 * Cool Function where a single key does CMD+TAB
 * Copy & slight adjustment: https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
 */
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

#define _QWERTY_MAC 0
#define _QWERTY_GAME 1
#define _LOWER 5
#define _RAISE 6
#define _FN 7
#define _ADJUST 8

enum custom_keycodes {
  QWERTY_MAC = SAFE_RANGE,
  QWERTY_GAME,
  LOWER,
  RAISE,
  FN,
  ADJUST,

  ALT_TAB,
  SWITCH_LANG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY_MAC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  CTL_T(KC_A),    OPT_T(KC_S),    SFT_T(KC_D),    CMD_T(KC_F),    KC_G,                               KC_H,    RCMD_T(KC_J),    RSFT_T(KC_K),    ROPT_T(KC_L),    RCTL_T(KC_SCLN), KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,           SWITCH_LANG,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SGUI(KC_X),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, LOWER,   KC_SPC,                    KC_ENT,  RAISE,   FN
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_QWERTY_GAME] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,           KC_LGUI,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SGUI(KC_X),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, LOWER,   KC_SPC,                    KC_ENT,  RAISE,   FN
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


//   [_LOWER] = LAYOUT(
//   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
//      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
//   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
//      QK_BOOT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
//   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
//      KC_DEL,  _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                            KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
//   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//      BL_STEP, _______, _______, _______, KC_DOWN, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
//   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
//                                     _______, _______, KC_DEL,                    KC_DEL,  _______, KC_P0
//                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
//   ),


  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                       ┌────────┬────────┬────────┬────────┬────────┬────────┐
     LCTL(KC_ESC), _______, _______,   _______, _______,  _______,                                                  _______, _______, _______, _______, _______, LCTL(KC_DEL),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                                       ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL(KC_GRV), _______, _______, _______, _______, _______,                                      _______, _______, _______, KC_LPRN, KC_RPRN, LCTL(KC_BSPC),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                                       ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL(KC_TAB), _______, MS_WHLL, MS_WHLR, MS_WHLU, KC_LPRN,                                                 KC_RPRN, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                                     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL(KC_LSFT), _______, _______, _______, MS_WHLD, KC_LCBR, KC_MPLY,                  _______,  KC_RCBR, _______, _______, _______, LCTL(KC_SLSH), _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘                                     └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_ENT,                                                LSFT(KC_INS), _______, _______
                                // └────────┴────────┴────────┘                                              └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______,  KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,  _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_PGUP, _______, _______,                            KC_MNXT, _______, KC_UP  , _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, LCMD(KC_LEFT), KC_PGDN, LCMD(KC_RGHT), _______,                KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    //  _______, _______, KC_HOME, KC_PGDN, KC_END , _______,                            KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, KC_MPLY,          _______, KC_MPRV, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT, DB_TOGG, EE_CLR,  _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                            _______, _______, LCTL(KC_UP), _______, DF(_QWERTY_GAME), _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,                            _______, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_RGHT), _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BL_STEP, _______, _______, _______, _______, _______, _______,          _______, _______, DF(_QWERTY_MAC), _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬──f──┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // case QWERTY_GAME:
    //   if (record->event.pressed) {
    //     set_single_persistent_default_layer(_QWERTY_GAME);
    //   }
    //   return false;
    //   break;
    // case QWERTY_MAC:
    //   if (record->event.pressed) {
    //     set_single_persistent_default_layer(_QWERTY_MAC);
    //   }
    //   return false;
    //   break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        update_tri_layer(_LOWER, _FN, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        update_tri_layer(_LOWER, _FN, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_LOWER, _FN, _ADJUST);
      } else {
        layer_off(_FN);
        update_tri_layer(_LOWER, _FN, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LCMD);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case SWITCH_LANG:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_SPC);
      } else {
        unregister_code(KC_LCTL);
        unregister_code(KC_SPC);
      }
      break;
  }
  return true;
}

// The very important timer.
void matrix_scan_user(void) {
  if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1000) {
    unregister_code(KC_LCMD);
    is_alt_tab_active = false;
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            if(IS_LAYER_ON(_FN) || IS_LAYER_ON(_LOWER)) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_VOLU);
            }
        } else {
            if(IS_LAYER_ON(_FN) || IS_LAYER_ON(_LOWER)) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
    // else if (index == 1) {
    //     if (clockwise) {
    //         tap_code(KC_PGDN);
    //     } else {
    //         tap_code(KC_PGUP);
    //     }
    // }
    return false;
}
