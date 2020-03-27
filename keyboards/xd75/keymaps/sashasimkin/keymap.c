#include QMK_KEYBOARD_H

#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)

#define MO_FN      MO(L_FN)

#define COMMA   UC(0x002C)
#define L_PAREN UC(0x0028)
#define R_PAREN UC(0x0029)
#define EQUALS  UC(0x003D)
#define TIMES   UC(0x00D7)
#define DIVIDE  UC(0x00F7)
#define MINUS   UC(0x2212)

#define ALT_TAB LALT(KC_TAB)
#define ALTS_TB LSFT(LALT(KC_TAB))


void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}

enum layers {
  L_BASE,
  L_FN,
};

enum custom_keycodes {
  CLEAR = SAFE_RANGE,
  SPRD_LV,
  DSFT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
    }
    return false;

  case SPRD_LV:
    if (record->event.pressed) {
      SEND_STRING(":green_heart:");
    }
    return false;

  case DSFT:
    if (record->event.pressed) {
      tap_code(KC_LSFT);
      tap_code(KC_LSFT);
    }
    return false;

  default:
    return true;
  }
}

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD + 3); // sets mode to Fast breathing without saving
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* Base layer - NOT USED
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
    * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │PSc|Ins| 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │ ` │ Q │ W │ E │ R │ T │   |   | Y │ U │ I │ O │ P │Bsp│Del│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Tab│ A │ S │ D │ F │ G │ ↓ | ↑ | H │ J │ K │ L │ ; │ ' │Ent│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │LSf│ Z │ X │ C │ V │ B │ ← | → | N │ M │ , │ . │ / │ \ |RSf│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │LCt│Mnu│LGu│FnL│LAl│Spc│ - │ = │Spc│RAl│FnL│RGu│PgU│PgD│Rct│
    * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
    */
    // KC_LSFT  -  KC_RSFT
  // [L_BASE] = LAYOUT_ortho_5x15( \  // NOT USED
  //   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PSCR, KC_INS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F11,  KC_F12,   \
  //   KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_DEL,  \
  //   KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MINS, KC_EQL,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,   \
  //   KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, KC_RSPC,  \
  //   KC_LCTL, KC_APP,  KC_LGUI, MO_FN,    LALT_T(KC_LBRC), LALT_T(KC_SPC), KC_SPC,  KC_SPC, RALT_T(KC_SPC),  RALT_T(KC_RBRC), MO_FN,      KC_RGUI, KC_PGUP, KC_PGDN, KC_RCTL   \
  // ),

   /* Base layer
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
    * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │PSc|Ins| 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │ ` │ Q │ W │ E │ R │ T | Y │ U │ I │ O │ P │ [ | ] │Bsp│Del│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Tab│ A │ S │ D │ F │ G | H │ J │ K │ L │ ; │ ' │Ins|Prc│Ent│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │LSf│ Z │ X │ C │ V │ B | N │ M │ , │ . │ / │ \ │   |   |RSf│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │LCt│Mnu│LGu│FnL│LAl│Spc│Spc│Spc│Spc│RAl│FnL│RGu│PgU│PgD│Rct│
    * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
    */
  [L_BASE] = LAYOUT_ortho_5x15( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,    KC_F11,  KC_F12,   \
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,  \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_INS, KC_PSCR, KC_QUOT, KC_ENT,   \
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, _______, _______, KC_RSPC,  \
    KC_LCTL, KC_APP,  KC_LGUI, MO_FN,    KC_LALT, KC_SPC, KC_SPC,  KC_SPC, KC_SPC,  KC_RALT, MO_FN,      KC_RGUI, KC_PGUP, KC_PGDN, KC_RCTL   \
  ),
   /* Rest of the keys
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
    * │Rst│F1 │F2 │F3 │F4 │F5 │   |   |F6 │F7 │F8 │F9 │F10│F11│F12│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │   │   │   │   │LAp│PAp│Btm│Top│Nxt|   │ ↑ │SLv│   │   │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │   │   │   │   │Lwn│Nwm│PgD│PgU│Ply| ← │ ↓ │ → │   │   │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │   │   │   │   │Ptb│Ntb│Hom│End│Prv|VoD│VoU│Mut│   │   │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
    * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
    */
  [L_FN] = LAYOUT_ortho_5x15( \
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    RGB_TOG, RGB_MOD, RGB_RMOD, ALT_TAB, ALTS_TB, _______, _______, _______,  KC_MNXT, _______, KC_UP,   SPRD_LV, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN,  KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, \
    DSFT,    _______, _______, _______, _______, _______, KC_HOME, KC_END,   KC_MPRV, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, BOTTOM,  TOP,      _______, _______, _______, _______, _______, _______, _______  \
  ),

};
