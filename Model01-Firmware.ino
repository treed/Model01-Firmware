// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

#include <Kaleidoscope-HostPowerManagement.h>

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

#include <Kaleidoscope-ShapeShifter.h>

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

#include "Kaleidoscope-LEDEffect-SolidColor.h"

#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Sleep:
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  }
}

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  */

enum { KEYMAP_DVORAK, KEYMAP_FUNCTION, KEYMAP_NUMPAD }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {

  [KEYMAP_DVORAK] = KEYMAP_STACKED
  (___,        Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
   Key_Tab,    Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, Key_PageUp,
   Key_Escape, Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   ___,        Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_PageDown,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(KEYMAP_FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8, Key_9, Key_0, LockLayer(KEYMAP_NUMPAD),
   Key_Enter,     Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                  Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_RightAlt,  Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Backslash,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(KEYMAP_FUNCTION)),

  [KEYMAP_FUNCTION] =  KEYMAP_STACKED
  (Key_Backtick,      Key_F1,           Key_F2,        Key_F3,      Key_F4,        Key_F5,           XXX,
   Key_Tab,          Key_PrintScreen,   Key_mouseBtnL, Key_mouseUp,    Key_mouseBtnR,    Key_mouseWarpEnd, Key_Home,
   Key_mouseWarpNW,  Key_mouseWarpNE,   Key_mouseL,    Key_mouseDn,    Key_mouseR,       Key_mouseScrollUp,
   Key_mouseWarpSW,  Key_mouseWarpSE,   Key_Insert,    Key_mouseBtnM,  Key_mouseScrollR, Key_mouseScrollDn,  Key_End,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftBracket,          Key_UpArrow,              Key_RightBracket, ___, Key_F12,
                               ___,                    Key_LeftArrow,            Key_DownArrow,            Key_RightArrow,   ___, Key_Equals,
   Key_PcApplication,          Key_Mute,               Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,              ___, ___,
   ___, ___, Key_Enter, ___,
   ___),


  [KEYMAP_NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, ___        , Key_KeypadDivide, Key_KeypadMultiply, Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad7, Key_Keypad8,      Key_Keypad9,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad4, Key_Keypad5,      Key_Keypad6,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_Keypad1, Key_Keypad2,      Key_Keypad3,        Key_KeypadDot,   Key_Enter,
   ___, ___, ___, Key_Keypad0,
   ___)
};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

static const kaleidoscope::ShapeShifter::dictionary_t shape_shift_dictionary[] PROGMEM = {
   {Key_mouseUp, Key_mouseScrollUp},
   {Key_mouseDn, Key_mouseScrollDn},
   {Key_mouseL, Key_mouseScrollL},
   {Key_mouseR, Key_mouseScrollR},
   {Key_NoKey, Key_NoKey}
};

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);



/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  Kaleidoscope.setup();

  Kaleidoscope.use(
    // LEDControl provides support for other LED modes
    &LEDControl,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    &NumPad,

    // The macros plugin adds support for macros
    &Macros,

    &ShapeShifter,
    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys,
    &HostPowerManagement

  );

  NumPad.numPadLayer = KEYMAP_NUMPAD;
  ShapeShifter.dictionary = shape_shift_dictionary;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = { 255, 0, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
