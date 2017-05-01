// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

extern keymap_config_t keymap_config;

// Symbolic names for macro IDs.
#define _QWERTY  0 // QUERTY layer
#define _LOWER   1 // Lower layer
#define _RAISE   2 // Raise layer
#define _CUSTOM  3 // Custom layer (LOWER + RAISE)
#define _BL      4 // Backlight
#define _MOB     5 // Mobile#
#define _CUS1    6 // Custom macro 1
#define _CUS2    7 // Custom macro 2
#define _FNL     8 // Play final countdown

// Macro shortcuts.
#define QWERTY  M(_LOWER)
#define LOWER   M(_LOWER)
#define RAISE   M(_RAISE)
#define CUSTOM  M(_CUSTOM)
#define BL      M(_BL)
#define MOB     M(_MOB)
#define CUS1    M(_CUS1)
#define CUS2    M(_CUS2)
#define FNL     M(_FNL)

// Func macro definitions.
#define LWR_PGDN FUNC(0) // Tap for PgDn, hold for LOWER
#define RSE_PGUP FUNC(1) // Tap for PgUp, hold for RAISE
#define CTL_CAPS FUNC(2) // Tap for Caps, hold for Ctrl (DOESN'T SEEM TO WORK)
#define SFT_ENT  FUNC(3) // Tap for Enter, hold for Shift
#define ZM_NRM   FUNC(4) // Zoom normal
#define ZM_IN    FUNC(5) // Zoom out
#define ZM_OUT   FUNC(6) // Zoom in
#define EM_UNDO  FUNC(7) // Emacs Undo

// Enable these functions using FUNC(n) macro.
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(_LOWER, KC_PGDN),
    [1] = ACTION_LAYER_TAP_KEY(_RAISE, KC_PGUP),
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_CAPS),
    [3] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
    [4] = ACTION_MODS_KEY(MOD_LCTL, KC_0),
    [5] = ACTION_MODS_KEY(MOD_LCTL, KC_MINS),
    [6] = ACTION_MODS_KEY(MOD_LCTL, KC_PLUS),
    [7] = ACTION_MODS_KEY(MOD_LCTL, KC_UNDS),
 };


#define TD_SCLN TD(0) // Tap for semicolon, double tap for colon
#define TD_QUOT TD(1) // Tap for single quot, double tap for double quote

// Enable these double tap calls using TD(n) macro
qk_tap_dance_action_t tap_dance_actions[] = {
  // action to do when TD(1) is tap-danced
  [0] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
  [1] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT))
};



#ifdef AUDIO_ENABLE
// C# B C# F# | - . D C# D C# B
// |-. D C# D F# | -. B A B A G# B | A G# A B A B C# B A G# F D C# C# C# D C# B C#
#define FINAL_COUNTDOWN_SOUND  \
E__NOTE(_CS6  ),      \
E__NOTE(_B5  ),      \
H__NOTE(_CS6  ),      \
H__NOTE(_FS5  ),      \
H__NOTE(_REST  ),      \
E__NOTE(_D6  ),      \
E__NOTE(_CS6  ),      \
Q__NOTE(_D6  ),      \
Q__NOTE(_CS6  ),      \
H__NOTE(_B5  ),      \
H__NOTE(_REST  ),      \
E__NOTE(_DS6  ),      \
E__NOTE(_CS6  ),      \
H__NOTE(_D6  ),      \
H__NOTE(_FS5  ),      \
HD_NOTE(_REST  ),      \
E__NOTE(_B5  ),      \
E__NOTE(_A5  ),      \
H__NOTE(_B5  ),      \
H__NOTE(_A5  ),      \
H__NOTE(_GS5  ),      \
H__NOTE(_B5  ),      \
HD_NOTE(_A5  ),      \
E__NOTE(_GS5  ),      \
E__NOTE(_A5  ),      \
HD_NOTE(_B5  ),      \
E__NOTE(_A5  ),      \
E__NOTE(_B5  ),      \
H__NOTE(_CS6  ),      \
H__NOTE(_B5  ),      \
H__NOTE(_A5  ),      \
H__NOTE(_GS5  ),      \
W__NOTE(_FS5  ),      \
W__NOTE(_D6  ),      \
WD_NOTE(_CS6  ),      \
S__NOTE(_REST  ),      \
E__NOTE(_CS6  ),      \
E__NOTE(_D6  ),      \
E__NOTE(_CS6  ),      \
E__NOTE(_B5  ),      \
WD_NOTE(_CS6  ),



float tone_startup[][2]         = SONG(STARTUP_SOUND);
float tone_qwerty[][2]          = SONG(QWERTY_SOUND);
float tone_colemak[][2]         = SONG(COLEMAK_SOUND);
float music_scale[][2]          = SONG(MUSIC_SCALE_SOUND);
float tone_final_countdown[][2] = SONG(FINAL_COUNTDOWN_SOUND);
float tone_goodbye[][2]         = SONG(GOODBYE_SOUND);
#endif

// This config can be found at Keyboard layout editor site: http://goo.gl/zjXL2l
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /* QWERTY */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT},
    {KC_LCTL, KC_DEL,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_BSPC, KC_RCTL}
},
[_RAISE] = { /* RAISE */
    {KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_POWER},
    {KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO},
    {KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
[_LOWER] = { /* LOWER */
    {KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL},
    {KC_TRNS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_MINS},
    {KC_TRNS, KC_LABK, KC_RABK, KC_LBRC, KC_RBRC, KC_END,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSLS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
[_CUSTOM] = { /* CUSTOM */
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, FNL,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MOB,     KC_TRNS, CUS1,    CUS2,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
}
};

// Set a layer persistantly.
void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
    case _RAISE: // Raised layer.
	if (record->event.pressed) {
	    layer_on(_RAISE);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	} else {
	    layer_off(_RAISE);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	}
	break;
    case _LOWER: // Lowered layer.
	if (record->event.pressed) {
	    layer_on(_LOWER);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	} else {
	    layer_off(_LOWER);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	}
	break;
    case _BL: // Backlight
	if (record->event.pressed) {
	    register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
	    backlight_step();
#endif
	} else {
	    unregister_code(KC_RSFT);
	}
	break;
    case _MOB: // Your mobile# here.
	return MACRODOWN(T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(4),
			 END);
    case _CUS1: // Your custom macro 1
	return MACRODOWN(T(E), T(M), T(A), T(C), T(S), T(SPC), END);
    case _CUS2: // Your custom macro 2
	return MACRODOWN(T(L), T(S), T(SPC), T(MINS), T(L), T(ENT), END);
    case _FNL:
       if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            decrease_tempo(100);
            PLAY_NOTE_ARRAY(tone_final_countdown, false, 0);
            increase_tempo(100);
          #endif
       }
       return MACRO_NONE; 
    };
    return MACRO_NONE;
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

