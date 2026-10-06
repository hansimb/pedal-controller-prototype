# Project requirements

- 3 physical potentiometers with
- 3 corresponding digital potentiometers (modules)
- 2 buttons,
  - BUTTON 1 (foot switch) has 2 functions:
    1. Normal press - ON/OFF
       - Not actually shutting power off but for end user it functions as it is power of
       - Changing state to: STAND_BY
       - Disables digital potentiometer outputs
       - STAND_BY -> ACTIVE does not load preset
    2. Long press - load preset
       - Cycle preset states: OFF, ORANGE, RED, EDIT/BLINK, SAVED
  - BUTTON 2 has one function:
    1. Long press, 2 seconds - cycle presets
- 2 presets
- 2 LEDs,
  - LED 1: (white) ON/OFF LED
  - LED 2: preset indicator LED
    - OFF - no preset
    - ORANGE - preset1
    - RED - preset2
    - when editing the unsaved preset led is blinking
    - when saving the preset, LED blinks quickly 3 times
- Potentiometers has to be responsive / real-time
- On wall power off to on -> correct values has to be readed from physical potentiometers to digital ones
- Button timing (B1 & B2):
  - short press has to be limited for short press e.g. 1 -> ma
  - Betweern 1 to 3 seconds it does nothing, to prevent accidental wrong function
  - 3 seconds or more for long press
