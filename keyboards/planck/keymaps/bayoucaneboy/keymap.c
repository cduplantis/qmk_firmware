/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "planck.h"

#define TAPPING_TERM 250

extern keymap_config_t keymap_config;

static bool option_interrupted[2] = { 0, 0 };

static uint16_t space_cadet_timer[5] = { 0, 0, 0, 0, 0 };

enum planck_layers {
  QWERTY_LAYER,
  COLEMAK_LAYER,
  LOWER_LAYER,
  RAISE_LAYER,
  PLOVER_LAYER,
  NAVIGATION_LAYER,
  ADJUST_LAYER
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE, // querty, the base keyboard mode
  COLEMAK,        // toggles colemake keyboard mode
  PLOVER,         // toggles plover keyboard mode
  BACKLIT,        // toggles backlite
  EXT_PLV,        // exits plover mode
  SEND_VERSION,   // sends the version information
  SEND_MAKE,      // sends the make command to console, should be run in the qmk_firmwire folder
  KC_LHAO,        // left hyper angle open <
  KC_RHAC,        // right hyper angle close >
  KC_LOBO,        // left option brace open {
  KC_ROBC,        // right option brace close }};
};

enum macro_keycodes {
  KC_ALT_TAB,
  KC_CMD_TAB,
  KC_CTL_TAB,
  KC_CMD_SLSH,
  KC_AG_FIND,
  KC_AG_AGAIN,
  KC_AG_UNDO,
  KC_AG_CUT,
  KC_AG_COPY,
  KC_AG_PASTE,
};

#define LOWER MO(LOWER_LAYER)
#define RAISE MO(RAISE_LAYER)


#define NAV_L LT(NAVIGATION_LAYER, KC_LBRC)
#define NAV_R LT(NAVIGATION_LAYER, KC_RBRC)

#define CTL_ESC CTL_T(KC_ESC)
#define CTL_ENT CTL_T(KC_ENT)

// Macros for Cmd-[x] vs Ctrl-[x] based on current AG_NORM or AG_SWAP settings
#define AG_FIND     M(KC_AG_FIND)
#define AG_AGAIN    M(KC_AG_AGAIN)
#define AG_UNDO     M(KC_AG_UNDO)
#define AG_CUT      M(KC_AG_CUT)
#define AG_COPY     M(KC_AG_COPY)
#define AG_PSTE     M(KC_AG_PASTE)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * | Ctrl |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shft(|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter)|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Nav [ | HYP < | Alt { | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[QWERTY_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, CTL_ENT,
    NAV_L,   KC_LHAO, KC_LOBO, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_ROBC, KC_RHAC, NAV_R
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[COLEMAK_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______,
    _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Bksp    |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[LOWER_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Delete   |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[RAISE_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, KC_DEL, KC_DEL, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|¸¸¸
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[PLOVER_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),


/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+[------+------+--]----|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[NAVIGATION_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, AG_FIND, KC_AG_AGAIN, KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT,     XXXXXXX,     _______,
    _______, AG_UNDO, AG_CUT,  AG_COPY, AG_PSTE, XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
    _______, _______, _______, _______, _______, KC_LSHIFT,   KC_LSHIFT,   KC_RALT,     _______,     _______,     _______,     _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |{}
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|------|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[ADJUST_LAYER] = LAYOUT_planck_grid(
 // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    SEND_VERSION, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, SEND_MAKE ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, _______,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, LOWER_LAYER, RAISE_LAYER, ADJUST_LAYER);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(QWERTY_LAYER);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(COLEMAK_LAYER);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(RAISE_LAYER);
        layer_off(LOWER_LAYER);
        layer_off(ADJUST_LAYER);
        layer_on(PLOVER_LAYER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(PLOVER_LAYER);
      }
      return false;
      break;
    case SEND_VERSION:
      if (record->event.pressed) {
        // SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "(" QMK_BUILDDATE ")");
        // SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION " (" QMK_BUILDDATE ")");
      }
      return false;
    case SEND_MAKE:
      if (record->event.pressed) {
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":dfu\n");
      }
      return false;
    case KC_LHAO: {
      if (record->event.pressed) {
        space_cadet_timer[0] = timer_read();
        register_mods(
          MOD_BIT(KC_LSHIFT) |
          MOD_BIT(KC_LGUI)   |
          MOD_BIT(KC_LALT)   |
          MOD_BIT(KC_LCTRL)
        );
      }
      else {
        unregister_mods(
          MOD_BIT(KC_LCTRL) |
          MOD_BIT(KC_LALT)  |
          MOD_BIT(KC_LGUI)
        );
        if (timer_elapsed(space_cadet_timer[0]) < TAPPING_TERM) {
          register_code(KC_COMMA);
          unregister_code(KC_COMMA);
        }
        unregister_mods(MOD_BIT(KC_LSHIFT));
      }
      return false;
    }
    case KC_RHAC: {
      if (record->event.pressed) {
        space_cadet_timer[1] = timer_read();
        register_mods(
          MOD_BIT(KC_RSHIFT) |
          MOD_BIT(KC_RGUI)   |
          MOD_BIT(KC_RALT)   |
          MOD_BIT(KC_RCTRL)
        );
      }
      else {
        unregister_mods(
          MOD_BIT(KC_RCTRL) |
          MOD_BIT(KC_RALT)  |
          MOD_BIT(KC_RGUI)
        );
        if (timer_elapsed(space_cadet_timer[1]) < TAPPING_TERM) {
          register_code(KC_DOT);
          unregister_code(KC_DOT);
        }
        unregister_mods(MOD_BIT(KC_RSHIFT));
      }
      return false;
    }

    case KC_LOBO: {
      if (record->event.pressed) {
        option_interrupted[0] = false;
        space_cadet_timer[2] = timer_read();
        register_mods(MOD_BIT(KC_LALT));
      } else {
        unregister_mods(MOD_BIT(KC_LALT));
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(KC_RALT)) { // is opposite side option down?
            option_interrupted[0] = true;
            option_interrupted[1] = true;
          }
        #endif
        if (!option_interrupted[0] && timer_elapsed(space_cadet_timer[2]) < TAPPING_TERM) {
          tap_code16(S(KC_LBRACKET));
        }
      }
      return false;
    }

    case KC_ROBC: {
      if (record->event.pressed) {
        option_interrupted[1] = false;
        space_cadet_timer[3] = timer_read();
        register_mods(MOD_BIT(KC_RALT));
      }
      else {
        unregister_mods(MOD_BIT(KC_RALT));
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(KC_LALT)) { // is opposite side option down?
            option_interrupted[0] = true;
            option_interrupted[1] = true;
          }
        #endif
        if (!option_interrupted[1] && timer_elapsed(space_cadet_timer[3]) < TAPPING_TERM) {
          tap_code16(S(KC_RBRACKET));
        }
      }
      return false;
    }
  }
  return true;
}

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }

    bool use_cmd = true;    // Use, for example, Cmd-Tab, Cmd-C, Cmd-V, etc.
    // Compare to MAGIC_SWAP_ALT_GUI and MAGIC_UNSWAP_ALT_GUI configs, set in:
    // quantum/quantum.c
    if (keymap_config.swap_lalt_lgui == 1 && keymap_config.swap_ralt_rgui == 1) {
      use_cmd = false;      // ... or, Alt-Tab, Ctrl-C, Ctrl-V, etc.
    }

    switch (id) {
      case KC_AG_FIND:
        return use_cmd ? MACRODOWN( D(LGUI), T(F), END ) : MACRODOWN( D(LCTRL), T(F), END );
      case KC_AG_AGAIN:
        return use_cmd ? MACRODOWN( D(LGUI), T(G), END ) : MACRODOWN( D(LCTRL), T(G), END );
      case KC_AG_UNDO:
        return use_cmd ? MACRODOWN( D(LGUI), T(Z), END ) : MACRODOWN( D(LCTRL), T(Z), END );
      case KC_AG_CUT:
        return use_cmd ? MACRODOWN( D(LGUI), T(X), END ) : MACRODOWN( D(LCTRL), T(X), END );
      case KC_AG_COPY:
        return use_cmd ? MACRODOWN( D(LGUI), T(C), END ) : MACRODOWN( D(LCTRL), T(C), END );
      case KC_AG_PASTE:
        return use_cmd ? MACRODOWN( D(LGUI), T(V), END ) : MACRODOWN( D(LCTRL), T(V), END );
    }

    return MACRO_NONE;
}
