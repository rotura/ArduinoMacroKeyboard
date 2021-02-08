# ArduinoMacroKeyboard
Arduino based mini macro keyboard configurable with a Java App (https://github.com/rotura/ArduinoMacroController) after first load of the sketch.

## Configuration:
Apart of the Java App, the Arduino can be configured throw the serial por with the following commands:
- **Return actual configuration**: "&".
- **Send a configuration to store in variable**: "key_to_configure,value#". More than one sequence can be sent in the same Serial line.
  - **key_to_configure**: An integer from 0 to 5 for key configuration or "R", "G" or "B" for RGB led configuration.
  - **value**: Value to store in the key o led:
    - **Key**: The combination of keys that will be send by the arduino when the key is pressed. Example: "0,ctrl+1#".
    - **RGB**: Integer number between 0 and 255: Example: "R,200#"
- **Send a configuration to store in the EEPROM**: Just change the final "#" of the command for a "%".

## Keys configuration available:
- **Raw text**: Up to 19 characters (For EEPROM saving, using more only store the data on the variables).
- **Special keys**: This keys are entered as text in the key's fields (if you press the key in the field the correspond text will be written). Only work 1 Special key for key configured. If more than one Special key or a Special key with other character is written in the field, the data will be send but the Arduino will catch only the first Special key and ignore the rest of the data. Available special keys are:
  - **Space bar**: "space" or "".
  - **Enter**: "enter" or "return".
  - **Right arrow**: "rarrow".
  - **Left arrow**: "larrow".
  - **Up arrow**: "uarrow".
  - **Down arrow**: "darrow".
  - **Control**: "ctrl".
  - **Shift**: "shift".
  - **Alt**: "alt".
  - **Windows or Cmd(Mac)**: "gui".
  - **Tab**: "tab".
  - **Esc**: "esc".
  - **F1-F24**: "F1", "F2", etc. Only upper case work. Lower case will send it as Raw text
- **Combinations**: Combination of keys pressed. All **Special keys** can be combined with single keys or between them using "+" as separator. Example: "ctrl+shift+t", "alt+tab", "ctrl+alt+F1".

## Hardware:
- Microcontroller: Arduino Leonardo, Arduino Pro micro or compatible (based on Leonardo).
- Switches: Up to 6, but the code can be moddified to add more.
- RGB led: Optional. 5v with (-) commun.

### 3D printed case:
Comming soon.

### Wiring diagram:
![Wiring diagram](https://github.com/rotura/ArduinoMacroKeyboard/blob/main/wiring_diagram.jpg)


