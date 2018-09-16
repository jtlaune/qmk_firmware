#include QMK_KEYBOARD_H
#include "timer.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  ALT_MX,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Timing for MT custom keycodes
#define TAPPING_TERM 150
static uint16_t start[1];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | C/Esc|   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Sh/Ent|
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |Alt/Mx| Del  |      | GUI  |Lower |Space |  |Space |Raise |  Next | Vol- | Vol+| Play |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT), \
  ALT_MX, KC_DEL,  _______, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Lower
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |  |  ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------|  |-----+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      |  |  _  |   +  |  {   |   }  |  |   |      |
 * |------+------+------+------+------|------|  |-----+------+------+------+------+------|
 * | Shift|      |      |      |      |      |  |     |      |      |      |      |Enter |
 * |------+------+------+------+------+------|  |-----+------+------+------+------+------|
 * | Alt  |  Del |      | GUI  |      |      |  |     |      |      |PgUp  |PgDn  |      |
 * `-----------------------------------------'  `----------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_LCTL, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______, \
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT, \
  KC_LALT, KC_DEL, _______, KC_LGUI, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______ \
),

/* Raise
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  Ctrl|      |      |      |      |      |  |   -  |   =  |   [  |   ]  |  \   |      |
 * +------+------+------+------+------|------|  |------+------+------+------+------|------|
 * |Shift |      |      |      |      |      |  |      |WhlDn |WhlUp |      |      |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Alt  | Del  |      | GUI  |      |      |  |      |      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_LCTL, _______, _______, _______, _______, _______,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,  _______,\
  KC_LSFT, _______, _______, _______, _______, _______,  _______, KC_WH_D, KC_WH_U, _______, _______, KC_ENT, \
  KC_LALT, KC_DEL, _______, KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Reset|Aud on|Audoff|Qwerty|      |LEFT  | DOWN |UP    |RIGHT |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   AU_ON, AU_OFF, QWERTY, _______,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case ALT_MX:
      if (record->event.pressed){
        start[0] = timer_read();
        SEND_STRING(SS_DOWN(X_LALT));
      } else {
          if (timer_elapsed(start[0]) > TAPPING_TERM) {
      	  SEND_STRING(SS_UP(X_LALT));
          } else {
      	  SEND_STRING("x");
      	  SEND_STRING(SS_UP(X_LALT));
      	  }
      }
      return false;
  }
  return true;
}
