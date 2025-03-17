// * Autheur: Zakary Romdhane
// * Date: 2025/03/16
// * Description: Programme Arduino pour la communcation avec un ordinateur via serial
// *              Cree pour la S2.
// *              L'envoie de donnee de la mannette est fait par matrcie de 9 bytes
#include <Arduino.h>

// ! A MODIFIER POUR LES VRAIS PINS! ! !
#define PIN_ACCEL_X 33
#define PIN_ACCEL_Y 35
#define PIN_ACCEL_Z 37 
#define PIN_JSTICK_X 38 
#define PIN_JSTICK_Y 40 
#define PIN_SW_5 30
#define PIN_SW_4 32
#define PIN_SW_3 34
#define PIN_SW_2 36
#define PIN_LED_1 22
#define PIN_LED_2 24
#define PIN_LED_3 26
#define PIN_LED_4 28
#define PIN_POT A15

#define BAUD 9600       
#define MSG_SIZE 9
#define MSG_ID_FROM_ARDUINO 142
#define MSG_ID_FROM_PC 242



uint8_t inc = 0;    
bool state_LED1 = false;
bool state_LED2 = false;
bool state_LED3 = false;
bool state_LED4 = false;
bool state_SW2 = false;
bool state_SW3 = false;
bool state_SW4 = false;
bool state_SW5 = false;

uint8_t value_pot = 0;
uint8_t value_jstickX = 0;
uint8_t value_jstickY = 0;
uint8_t value_accelX = 0;
uint8_t value_accelY = 0;
uint8_t value_accelZ = 0;




void sendMsg(); 
void readMsg();
void serialEvent();
byte convertBoolsToByte(bool p_sw[8]);
void byteToBoolArray(byte b, bool arr[8]);

void setup() {
  Serial.begin(BAUD);              
  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_POT, INPUT);
}

void loop() {
  readMsg();
  sendMsg();
  delay(50);  
}


void sendMsg() {
  while (Serial.available()) {
    Serial.read();
  }
  
  //Boutons
  bool sw[8] = { digitalRead(PIN_LED_1),
                  digitalRead(PIN_LED_2),
                  digitalRead(PIN_LED_3),
                  digitalRead(PIN_LED_4),
                  digitalRead(PIN_SW_2),
                  digitalRead(PIN_SW_3),
                  digitalRead(PIN_SW_4),
                  digitalRead(PIN_SW_5) };
  byte b1 = convertBoolsToByte(sw);
  // byte b1 = inc++;
  if (inc > 255) inc = 0;
  byte pot = uint8_t(analogRead(PIN_POT)/4); // 0-1023 -> 0-255
  byte jstickX = uint8_t(analogRead(PIN_JSTICK_X)/4);
  byte jstickY = uint8_t(analogRead(PIN_JSTICK_Y)/4);
  byte accelX = uint8_t(analogRead(PIN_ACCEL_X)/4);
  byte accelY = uint8_t(analogRead(PIN_ACCEL_Y)/4);
  byte accelZ = uint8_t(analogRead(PIN_ACCEL_Z)/4);
  
  byte msg[MSG_SIZE] = {MSG_ID_FROM_ARDUINO, b1, pot, jstickX, jstickY, accelX, accelY, accelZ, 0};
  // byte msg[MSG_SIZE] = {142, 11, 22, 33, 44, 0, 0, 0, 0};
  // bool sw2[8] = {state_LED1, state_LED2, state_LED3, state_LED4, state_SW2, state_SW3, state_SW4, state_SW5};
  // byte b2 = convertBoolsToByte(sw2);

  // byte msg[MSG_SIZE] = {142, b2, value_pot, value_jstickX, value_jstickY, value_accelX, value_accelY, value_accelZ, 0};
  
  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE-1; i++) {
    checksum ^= msg[i];
  }
  msg[MSG_SIZE-1] = checksum;

  // Envoie
  Serial.write(msg, MSG_SIZE);
  Serial.flush();

}


void readMsg(){
  byte msg[MSG_SIZE];
  if (Serial.available() < MSG_SIZE) { 
    // Serial.println("WARING: Not enough bytes available! Message ignored");
    return; 
  }
  int a = Serial.readBytes(msg, MSG_SIZE);
  if (a != MSG_SIZE) { 
    // Serial.println("WARING: Not enough bytes read! Message ignored");
    return; 
  }
  if (msg[0] != MSG_ID_FROM_PC) { 
    // Serial.println("WARING: Invalid message! Message ignored");
    return; 
  }
 

  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE - 1; i++) {
    checksum ^= msg[i];
  }
  if (checksum != msg[MSG_SIZE - 1]) { 
    // Serial.println("WARING: Checksum error! Message ignored");
    return; 
    }

  bool sw[8];
  byteToBoolArray(msg[1], sw);
  byte pot = msg[2];
  byte jstickX = msg[3];
  byte jstickY = msg[4];
  byte accelX = msg[5];
  byte accelY = msg[6];
  byte accelZ = msg[7];
  
  // digitalWrite(LED_BUILTIN, ledState);
  // ledState = !ledState;
  if (state_LED1 != sw[0]) {
    state_LED1 = sw[0];
    digitalWrite(PIN_LED_1, state_LED1 ? HIGH : LOW);
  }
  if (state_LED2 != sw[1]) {
    state_LED2 = sw[1];
    digitalWrite(PIN_LED_2, state_LED2 ? HIGH : LOW);
  }
  state_LED1 = sw[0];
  state_LED2 = sw[1];
  state_LED3 = sw[2];
  state_LED4 = sw[3];
  state_SW2 = sw[4];
  state_SW3 = sw[5];
  state_SW4 = sw[6];
  state_SW5 = sw[7];

  value_pot = uint8_t(pot);
  value_jstickX = uint8_t(jstickX);
  value_jstickY = uint8_t(jstickY);
  value_accelX = uint8_t(accelX);
  value_accelY = uint8_t(accelY);
  value_accelZ = uint8_t(accelZ);
  
}

byte convertBoolsToByte(bool p_sw[8]) {
  byte b = 0;
  for (int i = 0; i < 8; i++) {
    b |= (p_sw[i] << i); // Met le bit i à 1 si p_sw[i] est vrai
  }
  return b;
}

void byteToBoolArray(byte b, bool arr[8]) {
  for (int i = 0; i < 8; i++) {
    arr[i] = (b >> i) & 1; // Met arr[i] à vrai si le bit i de b est à 1
  }
}