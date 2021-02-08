#include <EEPROM.h>
#include <Keyboard.h>
#define KEYCODE_F13 0x68
#define KEYCODE_F14 0x69
#define KEYCODE_F15 0x6A
#define KEYCODE_F16 0x6B
#define KEYCODE_F17 0x6C
#define KEYCODE_F18 0x6D
#define KEYCODE_F19 0x6E
#define KEYCODE_F20 0x6F
#define KEYCODE_F21 0x70
#define KEYCODE_F22 0x71
#define KEYCODE_F23 0x72
#define KEYCODE_F24 0x73

String keyValues[] = {"z","x","space","enter","uarrow","darrow" };
int rgb[] = {255,255,255};
int rgbChange = 0;
#define MAX_LENGHT 20
#define MY_SIZE 6
#define RGB_SIZE 3
#define RGB_EEPROM 200

// Keys
#define KEY_PIN_1 A0
#define KEY_PIN_2 A1
#define KEY_PIN_3 A2
#define KEY_PIN_4 A3
#define KEY_PIN_5 A6 // 4
#define KEY_PIN_6 A8 // 8

// RGB led
#define KEY_R 10
#define KEY_G 9
#define KEY_B 5


bool key1Pressed = 0;
bool key2Pressed = 0;
bool key3Pressed = 0;
bool key4Pressed = 0;
bool key5Pressed = 0;
bool key6Pressed = 0;

bool key1Pressed_l = 1;
bool key2Pressed_l = 1;
bool key3Pressed_l = 1;
bool key4Pressed_l = 1;
bool key5Pressed_l = 1;
bool key6Pressed_l = 1;

void setup() {
  Serial.begin(9600);
  pinMode(KEY_PIN_1, INPUT_PULLUP);
  pinMode(KEY_PIN_2, INPUT_PULLUP);
  pinMode(KEY_PIN_3, INPUT_PULLUP);
  pinMode(KEY_PIN_4, INPUT_PULLUP);
  pinMode(KEY_PIN_5, INPUT_PULLUP);
  pinMode(KEY_PIN_6, INPUT_PULLUP);
  pinMode(KEY_R, OUTPUT);
  pinMode(KEY_G, OUTPUT);
  pinMode(KEY_B, OUTPUT);
  chargeDefaultConf();
  led();
  Keyboard.begin();
}

void loop() {
  pressKeys();
  if(rgbChange){
    led();
  }
  if (Serial.available() > 0){
    serialConfiguration();
  }
}

// Execute keyboard actions
void pressKeys(){
  key1Pressed = digitalRead(KEY_PIN_1);
  key2Pressed = digitalRead(KEY_PIN_2);
  key3Pressed = digitalRead(KEY_PIN_3);
  key4Pressed = digitalRead(KEY_PIN_4);
  key5Pressed = digitalRead(KEY_PIN_5);
  key6Pressed = digitalRead(KEY_PIN_6);

  if(!key1Pressed && key1Pressed_l){
    keyboardPrint(0);
    key1Pressed_l = key1Pressed;
  } else if(key1Pressed && !key1Pressed_l){
    key1Pressed_l = key1Pressed;
    keyboardRelease(0);
  }
  
  if(!key2Pressed && key2Pressed_l){
    keyboardPrint(1);
    key2Pressed_l = key2Pressed;
  } else if(key2Pressed && !key2Pressed_l){
    key2Pressed_l = key2Pressed;
    keyboardRelease(1);
  }
  
  if(!key3Pressed && key3Pressed_l){
    keyboardPrint(2);
    key3Pressed_l = key3Pressed;
  } else if(key3Pressed && !key3Pressed_l){
    key3Pressed_l = key3Pressed;
    keyboardRelease(2);
  }

  if(!key4Pressed && key4Pressed_l){
    keyboardPrint(3);
    key4Pressed_l = key4Pressed;
  } else if(key4Pressed && !key4Pressed_l){
    key4Pressed_l = key4Pressed;
    keyboardRelease(3);
  }

  if(!key5Pressed && key5Pressed_l){
    keyboardPrint(4);
    key5Pressed_l = key5Pressed;
  } else if(key5Pressed && !key5Pressed_l){
    key5Pressed_l = key5Pressed;
    keyboardRelease(4);
  }

  if(!key6Pressed && key6Pressed_l){
    keyboardPrint(5);
    key6Pressed_l = key1Pressed;
  } else if(key6Pressed && !key6Pressed_l){
    key6Pressed_l = key6Pressed;
    keyboardRelease(5);
  }

  if(key1Pressed || key2Pressed || key3Pressed 
    || key4Pressed || key5Pressed || key6Pressed){
    // Delay to difference doble click and hold  
    delay(10);
  }
}

// Configure keyboard actions
void serialConfiguration(){
  String tempWord = "";
  char keyConfigured;
  char lastChar;
  int lenght = 0;
  if (Serial.available() > 0) {
    lastChar = Serial.read();
    // Si se recibe un '&' se envia la configuración actual
    if(lastChar == '&'){
      sendConfiguration();
    } else {
      tempWord += lastChar;
    }
  }
  // Si no es un '&' se recorre el serial para cargar configuración nueva
  while (lastChar != '#' && lastChar != '%' && Serial.available() > 0){
    // read the incoming byte:
    lastChar = Serial.read();
    if(lastChar == ','){
        keyConfigured = tempWord[0];
        tempWord = "";
    } else if(lastChar != '#' && lastChar != '%'){
      tempWord += lastChar;
      lenght++;    
    }
  }

  if(keyConfigured != NULL && lenght < MAX_LENGHT){
    switch (keyConfigured) {
      case '0':
        keyValues[0] = tempWord;
        if(lastChar == '%')
          writeStringToEEPROM(0 * MAX_LENGHT, tempWord + "#");
        break;
      case '1':
        keyValues[1] = tempWord;
        if(lastChar == '%')
          writeStringToEEPROM(1 * MAX_LENGHT, tempWord + "#");
      break;
      case '2':
        keyValues[2] = tempWord;
        if(lastChar == '%')
          writeStringToEEPROM(2 * MAX_LENGHT, tempWord + "#");
      break;
      case '3':
        keyValues[3] = tempWord;
        if(lastChar == '%')
          writeStringToEEPROM(3 * MAX_LENGHT, tempWord + "#");
      break;
      case '4':
        keyValues[4] = tempWord;
        if(lastChar == '%')
          writeStringToEEPROM(4 * MAX_LENGHT, tempWord + "#");
      break;
      case '5':
        keyValues[5] = tempWord;
        if(lastChar == '%')
          writeStringToEEPROM(5 * MAX_LENGHT, tempWord + "#");
      break;
      case 'R':
        rgb[0] = tempWord.toInt();
        if(lastChar == '%')
          writeStringToEEPROM(RGB_EEPROM, tempWord + "#");
        rgbChange = 1;
      break;
      case 'G':
        rgb[1] = tempWord.toInt();
        if(lastChar == '%')
          writeStringToEEPROM(RGB_EEPROM + (RGB_SIZE + 1), tempWord + "#");
        rgbChange = 1;
      break;
      case 'B':
        rgb[2] = tempWord.toInt();
        if(lastChar == '%')
          writeStringToEEPROM(RGB_EEPROM + 2 * (RGB_SIZE + 1), tempWord + "#");
        rgbChange = 1;
      break;
    }     
  }
}

void sendConfiguration(){
  for(int i=0; i < MY_SIZE; i++){
    Serial.print(String(i) + "," + keyValues[i] + "#");  
  }
  Serial.print(String('R') + "," + rgb[0] + "#");  
  Serial.print(String('G') + "," + rgb[1] + "#");  
  Serial.print(String('B') + "," + rgb[2] + "#");  
  Serial.print("&");  
}

void chargeDefaultConf(){
  for(int i=0; i < MY_SIZE; i++){
    String value = readStringFromEEPROM(i*MAX_LENGHT);
    value.trim();  
    if(value != ""){
      keyValues[i] = value;
      //Serial.println("Key " + String(i) + " configured as:" + value);
    } else {
      //Serial.println("No configuration for key: " + i);
    }
  }
  for(int i=0; i < RGB_SIZE; i++){
    String value = readRGBfromEEPROM(RGB_EEPROM + (i*(RGB_SIZE+1)));
    rgb[i] = value.toInt();
  }
}


  ////////////////////
 // EEPROM actions //
////////////////////
String readStringFromEEPROM(int addrOffset)
{
  String strToRead = ""; 
  for (int i = 0; i < MAX_LENGHT; i++)
  {
    char character = EEPROM.read(addrOffset + i);
    if(character != '#'){
      strToRead += character;
    } else {
      return strToRead;  
    }   
  }
}

String readRGBfromEEPROM(int addrOffset)
{
  String value = ""; 
  for (int i = 0; i <= RGB_SIZE; i++)
  {
    char character = EEPROM.read(addrOffset + i);
    if(character != '#'){
      value += character;
    } else {
      return value;  
    }   
  }
}

void writeStringToEEPROM(int addrOffset, String strToWrite)
{
  //Serial.println("Writting EPPROM: " + strToWrite);
  for (int i = 0; i < MAX_LENGHT; i++)
  {
    EEPROM.update(addrOffset + i, strToWrite[i]);
    if(strToWrite == '#'){
      break;
      }
  }
}

  ////////////////
 // IO actions //
////////////////
void keyboardPrint(int key){
    String value = keyValues[key];
    if(value.indexOf("+") > 0){
      keyboardPressCommand(value);
    } else if(containSpecialKey(value) || value.length() == 1){
      pressKey(value);  
    } else {
      Keyboard.print(value);
    }
  }

void keyboardRelease(int key){
    String value = keyValues[key];
    if(value.indexOf("+") > 0){
      keyboardReleaseCommand(value);
    } else if(containSpecialKey(value) || value.length() == 1){
     releaseKey(value);  
    } 
  }

  void keyboardPressCommand(String command){
    char str[command.length() + 1];
    command.toCharArray(str, command.length()+1);
    char * pch = strtok (str,"+");
    while (pch != NULL)
    {
      pressKey(pch);
      pch = strtok (0, "+");
    }
  }

  void keyboardReleaseCommand(String command){
    char str[command.length() + 1];
    command.toCharArray(str, command.length()+1);
    char * pch = strtok (str,"+");
    while (pch != NULL)
    {
      releaseKey(pch);
      pch = strtok (0, "+");
    }
  }

  void pressKey(String value){
    if(value.equals("ctrl")){
      Keyboard.press(KEY_LEFT_CTRL);
    } else if(value.equals("alt")){
      Keyboard.press(KEY_LEFT_ALT);
    } else if(value.equals("shift")){
      Keyboard.press(KEY_LEFT_SHIFT);
    } else if(value.equals("tab")){
      Keyboard.press(KEY_TAB);
    } else if(value.equals("gui")){
      Keyboard.press(KEY_LEFT_GUI);
    } else if(value.equals("esc")){
      Keyboard.press(KEY_ESC);
    } else if(value.equals("space")){
      Keyboard.press(0x20);  
    } else if(value.equals("enter")|| value.equals("return")){
      Keyboard.press(KEY_RETURN);  
    } else if(value.equals("larrow")){
      Keyboard.press(KEY_LEFT_ARROW);  
    } else if(value.equals("rarrow")){
      Keyboard.press(KEY_RIGHT_ARROW);  
    } else if(value.equals("uarrow")){
      Keyboard.press(KEY_UP_ARROW);  
    } else if(value.equals("darrow")){
      Keyboard.press(KEY_DOWN_ARROW);  
    } else if(value.equals("f3")){
      Keyboard.press(KEY_F3);  
    } else if(value.equals("f4")){
      Keyboard.press(KEY_F4);  
    } else if(value.equals("f5")){
      Keyboard.press(KEY_F5);  
    } else if(value.equals("f6")){
      Keyboard.press(KEY_F6);  
    } else if(value.equals("f7")){
      Keyboard.press(KEY_F7);  
    } else if(value.equals("f8")){
      Keyboard.press(KEY_F8);  
    } else if(value.equals("f9")){
      Keyboard.press(KEY_F9);  
    } else if(value.equals("f10")){
      Keyboard.press(KEY_F10);  
    } else if(value.equals("f11")){
      Keyboard.press(KEY_F11);  
    } else if(value.equals("f12")){
      Keyboard.press(KEY_F12);  
    } else if(value.equals("f13")){
      Keyboard.press(KEYCODE_F13);  
    } else if(value.equals("f14")){
      Keyboard.press(KEYCODE_F14);  
    } else if(value.equals("f15")){
      Keyboard.press(KEYCODE_F15);  
    } else if(value.equals("f16")){
      Keyboard.press(KEYCODE_F16);  
    } else if(value.equals("f17")){
      Keyboard.press(KEYCODE_F17);  
    } else if(value.equals("f18")){
      Keyboard.press(KEYCODE_F18);  
    } else if(value.equals("f19")){
      Keyboard.press(KEYCODE_F19);  
    } else if(value.equals("f20")){
      Keyboard.press(KEYCODE_F20);  
    } else if(value.equals("f21")){
      Keyboard.press(KEYCODE_F21);  
    } else if(value.equals("f22")){
      Keyboard.press(KEYCODE_F22);  
    } else if(value.equals("f23")){
      Keyboard.press(KEYCODE_F23);  
    } else if(value.equals("f24")){
      Keyboard.press(KEYCODE_F24);  
    } else if(value.equals("f1")){
      Keyboard.press(KEY_F1);  
    } else if(value.equals("f2")){
      Keyboard.press(KEY_F2);  
    } else {
      Keyboard.press(value[0]);  
    }
  }

  void releaseKey(String value){
    if(value.equals("ctrl")){
      Keyboard.release(KEY_LEFT_CTRL);
    } else if(value.equals("alt")){
      Keyboard.release(KEY_LEFT_ALT);
    } else if(value.equals("shift")){
      Keyboard.release(KEY_LEFT_SHIFT);
    } else if(value.equals("tab")){
      Keyboard.release(KEY_TAB);
    } else if(value.equals("gui")){
      Keyboard.release(KEY_LEFT_GUI);
    } else if(value.equals("esc")){
      Keyboard.release(KEY_ESC);
    } else if(value.equals("space")){
      Keyboard.release(0x20);  
    } else if(value.equals("enter")|| value.equals("return")){
      Keyboard.release(KEY_RETURN);  
    } else if(value.equals("larrow")){
      Keyboard.release(KEY_LEFT_ARROW);  
    } else if(value.equals("rarrow")){
      Keyboard.release(KEY_RIGHT_ARROW);  
    } else if(value.equals("uarrow")){
      Keyboard.release(KEY_UP_ARROW);  
    } else if(value.equals("darrow")){
      Keyboard.release(KEY_DOWN_ARROW);  
    } else if(value.equals("f3")){
      Keyboard.release(KEY_F3);  
    } else if(value.equals("f4")){
      Keyboard.release(KEY_F4);  
    } else if(value.equals("f5")){
      Keyboard.release(KEY_F5);  
    } else if(value.equals("f6")){
      Keyboard.release(KEY_F6);  
    } else if(value.equals("f7")){
      Keyboard.release(KEY_F7);  
    } else if(value.equals("f8")){
      Keyboard.release(KEY_F8);  
    } else if(value.equals("f9")){
      Keyboard.release(KEY_F9);  
    } else if(value.equals("f10")){
      Keyboard.release(KEY_F10);  
    } else if(value.equals("f11")){
      Keyboard.release(KEY_F11);  
    } else if(value.equals("f12")){
      Keyboard.release(KEY_F12);  
    } else if(value.equals("f13")){
      Keyboard.release(KEYCODE_F13);  
    } else if(value.equals("f14")){
      Keyboard.release(KEYCODE_F14);  
    } else if(value.equals("f15")){
      Keyboard.release(KEYCODE_F15);  
    } else if(value.equals("f16")){
      Keyboard.release(KEYCODE_F16);  
    } else if(value.equals("f17")){
      Keyboard.release(KEYCODE_F17);  
    } else if(value.equals("f18")){
      Keyboard.release(KEYCODE_F18);  
    } else if(value.equals("f19")){
      Keyboard.release(KEYCODE_F19);  
    } else if(value.equals("f20")){
      Keyboard.release(KEYCODE_F20);  
    } else if(value.equals("f21")){
      Keyboard.release(KEYCODE_F21);  
    } else if(value.equals("f22")){
      Keyboard.release(KEYCODE_F22);  
    } else if(value.equals("f23")){
      Keyboard.release(KEYCODE_F23);  
    } else if(value.equals("f24")){
      Keyboard.release(KEYCODE_F24);  
    } else if(value.equals("f1")){
      Keyboard.release(KEY_F1);  
    } else if(value.equals("f2")){
      Keyboard.release(KEY_F2);  
    } else {
      Keyboard.release(value[0]);  
    }
  }

  boolean containSpecialKey(String value){
     if(value.equals("f1") || value.equals("f2")|| value.equals("f24")|| value.equals("f23")|| value.equals("f22")|| value.equals("f21")|| value.equals("f20")|| value.equals("f19")|| value.equals("f18")
            || value.equals("f17")|| value.equals("f16")|| value.equals("f15")|| value.equals("f14")|| value.equals("f13")|| value.equals("f12")|| value.equals("f11")|| value.equals("f10")
            || value.equals("f9")|| value.equals("f8")|| value.equals("f7")|| value.equals("f6")|| value.equals("f5")|| value.equals("f4")|| value.equals("f3")|| value.equals("darrow")
            || value.equals("uarrow")|| value.equals("rarrow")|| value.equals("larrow")|| value.equals("enter")|| value.equals("return")|| value.equals("esc")|| value.equals("gui")|| value.equals("tab")
            || value.equals("shift")|| value.equals("alt")|| value.equals("ctrl") || value.equals("space")){
      return true;    
    } else {
      return false;
    }
  }

  void led(){
    rgbChange = 0;
    analogWrite(KEY_R,rgb[0]);
    analogWrite(KEY_G,rgb[1]);
    analogWrite(KEY_B,rgb[2]);  
  }

