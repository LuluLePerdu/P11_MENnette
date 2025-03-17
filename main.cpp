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
#define MSG_ID_ERROR 71

struct Frame { 
  uint8_t id;
  uint8_t ledState;
  uint8_t potentiometer;
  uint8_t joystickX;
  uint8_t joystickY;
  uint8_t accelerometerX;
  uint8_t accelerometerY;
  uint8_t accelerometerZ;
  uint8_t checksum;
};

Frame errorFrame = {MSG_ID_ERROR, 0, 0, 0, 0, 0, 0, 0, 0};

void sendMsg(); 
Frame readMsg();
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
  // * Code de base! Modifiez a votre guise. 
  // Cependant, faite en sorte que vous envoyez des message a une frequence maximal de la clock du programme PC + 1ms
  // Sinon, il y a un backlog de message qui se cree dans le buffer, et un ping substantiel se manifeste
  // 2025-03-17: clock_pc=33ms --> lowest=delay(34)
  
  Frame frame = readMsg();
  sendMsg();
  delay(50);  
}


void sendMsg() {
  // * Si le code bug et que le buffer reste rempli, decommenter les 3 lignes suivantes
  // while (Serial.available()) {
  //   Serial.read();
  // }
  
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
  byte pot = uint8_t(analogRead(PIN_POT)/4); // 0-1023 -> 0-255
  byte jstickX = uint8_t(analogRead(PIN_JSTICK_X)/4);
  byte jstickY = uint8_t(analogRead(PIN_JSTICK_Y)/4);
  byte accelX = uint8_t(analogRead(PIN_ACCEL_X)/4);
  byte accelY = uint8_t(analogRead(PIN_ACCEL_Y)/4);
  byte accelZ = uint8_t(analogRead(PIN_ACCEL_Z)/4);
  
  //Creation de message
  byte msg[MSG_SIZE] = {MSG_ID_FROM_ARDUINO, b1, pot, jstickX, jstickY, accelX, accelY, accelZ, 0};
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


Frame readMsg(){
  byte msg[MSG_SIZE];
  if (Serial.available() < MSG_SIZE) { 
    Serial.println("WARING-AR: Not enough bytes available! Message ignored");
    return errorFrame;  
  }
  int a = Serial.readBytes(msg, MSG_SIZE);
  if (a != MSG_SIZE) { 
    Serial.println("WARING-AR: Not enough bytes read! Message ignored");
    return errorFrame; 
  }
  if (msg[0] != MSG_ID_FROM_PC) { 
    Serial.println("WARING-AR: Invalid message! Message ignored");
    return errorFrame; 
  }
 
  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE - 1; i++) {
    checksum ^= msg[i];
  }
  if (checksum != msg[MSG_SIZE - 1]) { 
    Serial.println("WARING-AR: Checksum error! Message ignored");
    return errorFrame;  
    }

  Frame frame = {msg[0], msg[1], msg[2], msg[3], msg[4], msg[5], msg[6], msg[7], msg[8]};
  return frame;
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
