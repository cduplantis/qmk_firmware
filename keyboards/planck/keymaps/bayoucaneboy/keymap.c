// This is sgoodwin's layout file for the Quantum project.
// It doesn't have Plover or Dvorak layers because he doesn't use that.
// It Also doesn't allow for swapping alt with CMD because that only happens in error.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keyboard_layers {
  LAYER_QWERTY = 0,
  LAYER_COLEMAK,
  LAYER_LOWER,
  LAYER_RAISE,
  LAYER_ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT,
};

enum macro_id {
  hello,
  finalCountdownId
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


// Double Tap Action codes; see below
#define TDA_SEMI_COLON   1
#define TDA_QUOT_DBLQUOT 2

// Double Tap code to make map easier to read
#define TD_SCLN TD(TDA_SEMI_COLON)
#define TD_QUOT TD(TDA_QUOT_DBLQUOT)

// LOWER TAPS
#define LT_SPC  LT(LOWER, KC_SPC)

// MOD TAPS
#define LT_SPC  LT(LOWER, KC_SPC)
#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)

#define FNL_CTDN M(finalCountdownId)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |  Esc |Enter |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |  {[  |  ]}  |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  DEL |  '   |   N  |   M  |   ,  |   .  |   /  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | SHIFT| Ctrl | Alt  | GUI  | LOWER|    Space    | RAISE| ENTER|      |      |SHIFT |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_QWERTY] = {
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_ESC,  KC_ENT,  KC_Y,  KC_U,    KC_I,    KC_O,    KC_P},
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LCBR, KC_RCBR, KC_H,  KC_J,    KC_K,    KC_L,    TD_SCLN},
  {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BSPC, TD_QUOT, KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH},
  {KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_ENT, _______, _______, MT_RSFT_ENT}
},


/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |SHEnt |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Hyper| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_COLEMAK] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT) },
  {ALL_T(KC_NO),  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   7  |   8  |   9  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  | Right|  Up  | Left | PgUp |  (   |   )  |   +  |   4  |   5  |   6  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Home | Down | End  | PgDn | Bksp |   |  |   -  |   1  |   2  |   3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SHIFT|      | Ctrl | Alt  | GUI  |  Space/Low  | RAISE|   +  |   0  |   .  |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_LOWER] = {
  {KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_7,    KC_8,    KC_9,    _______},
  {KC_TAB, KC_LEFT, KC_UP,    KC_RGHT, KC_PGUP, KC_LPRN, KC_RPRN, KC_PLUS, KC_4,    KC_5,    KC_6,    _______},
  {_______, KC_HOME, KC_DOWN,  KC_END,  KC_PGDN, KC_DEL, KC_PIPE, KC_MINS, KC_1,    KC_2,    KC_3,    _______},
  {_______, _______, _______,  _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |      |      |      |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |   <  |   >  |      |  F5  |  F6  |  F7  |  F8  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  F1  |  F2  |  F3  |  F4  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SHIFT|      | Ctrl | Alt  | GUI  |  Space/Low  | RAISE| Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_RAISE] = {
  {KC_GRV,  _______, _______, _______, _______, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {KC_DEL,  _______, _______, _______, _______, KC_LABK, KC_RABK, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______},
  {BACKLIT, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  FNL_CTDN |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|      |      |Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 s |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, FNL_CTDN},
  {_______, _______, _______, AU_ON,   AU_OFF,  _______, _______, QWERTY,  COLEMAK, _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
}



};


#ifdef AUDIO_ENABLE
// C# B C# F# | - . D C# D C# B
// |-. D C# D F# | -. B A B A G# B | A G# A B A B C# B A G# F D C# C# C# D C# B C#
#define FINAL_COUNTDOWN_SOUND  \
Q__NOTE(_CS5  ),      \
Q__NOTE(_B5  ),      \
H__NOTE(_CS5  ),      \
H__NOTE(_FS4  ),      \
HD_NOTE(_REST  ),      \
Q__NOTE(_D5  ),      \
Q__NOTE(_CS5  ),      \
H__NOTE(_D5  ),      \
H__NOTE(_CS5  ),      \
Q__NOTE(_B5  ),      \
QD_NOTE(_REST  ),      \
S__NOTE(_D5  ),      \
S__NOTE(_CS5  ),      \
Q__NOTE(_D5  ),      \
Q__NOTE(_FS4  ),      \
QD_NOTE(_REST  ),      \
S__NOTE(_B5  ),      \
S__NOTE(_A5  ),      \
E__NOTE(_B5  ),      \
E__NOTE(_A5  ),      \
E__NOTE(_GS4  ),      \
E__NOTE(_B5  ),      \
QD_NOTE(_A5  ),      \
S__NOTE(_GS4  ),      \
S__NOTE(_A5  ),      \
QD_NOTE(_B5  ),      \
S__NOTE(_A5  ),      \
S__NOTE(_B5  ),      \
E__NOTE(_CS5  ),      \
E__NOTE(_B5  ),      \
E__NOTE(_A5  ),      \
E__NOTE(_GS4  ),      \
Q__NOTE(_F4  ),      \
Q__NOTE(_D5  ),      \
HD_NOTE(_CS5  ),      \
S__NOTE(_CS5  ),      \
S__NOTE(_D5  ),      \
S__NOTE(_CS5  ),      \
E__NOTE(_B5  ),      \
W__NOTE(_CS5  ),



float tone_startup[][2]         = SONG(STARTUP_SOUND);
float tone_qwerty[][2]          = SONG(QWERTY_SOUND);
float tone_colemak[][2]         = SONG(COLEMAK_SOUND);
float music_scale[][2]          = SONG(MUSIC_SCALE_SOUND);
float tone_final_countdown[][2] = SONG(FINAL_COUNTDOWN_SOUND);
float tone_goodbye[][2]         = SONG(GOODBYE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  // action to do when TD(1) is tap-danced
  [TDA_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
  [TDA_QUOT_DBLQUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<LAYER_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<LAYER_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(LAYER_LOWER);
        update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
      } else {
        layer_off(LAYER_LOWER);
        update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(LAYER_RAISE);
        update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
      } else {
        layer_off(LAYER_RAISE);
        update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
      }
      return false;
      break;
    case BACKLIT:
/**      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      **/
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif

//const uint16_t PROGMEM fn_actions[] = {
//  [0] = ACTION_MACRO(FNL_CTDN)
//}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
     case finalCountdownId:
       if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_final_countdown, false, 0);
          #endif
         return MACRO_NONE;
       }
  }
  return MACRO_NONE;
}
