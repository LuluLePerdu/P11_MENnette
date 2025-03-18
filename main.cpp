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

#define BAUD 115200      
#define MSG_SIZE 3
#define MSG_ID_ERROR 71

#define MSG_ID_JOYSTICK 101
#define MSG_ID_POTENTIOMETER 102
#define MSG_ID_ACCELEROMETER 103
#define MSG_ID_BUTTON 104

#define MSG_ID_PC_LED 201
#define MSG_ID_PC_MOTOR 202
#define MSG_ID_PC_LCD 203
#define MSG_ID_PC_STATE 204
#define MSG_ID_FROM_MISC 242

struct Frame { 
  uint8_t id;
  uint8_t data;
  uint8_t checksum;
};

Frame errorFrame = {MSG_ID_ERROR, 0, 0};

void sendMsg(Frame frame); 
Frame readMsg();
Frame readMsg(byte id);
void serialEvent();
byte convertBoolsToByte(bool p_sw[8]);
void byteToBoolArray(byte b, bool arr[8]);

void setup() {
  Serial.begin(BAUD);              
}

void loop() {
  // * Code de base! Modifiez a votre guise. 
  // Cependant, faite en sorte que vous envoyez des message a une frequence maximal de la clock du programme PC + 1ms
  // Sinon, il y a un backlog de message qui se cree dans le buffer, et un ping substantiel se manifeste
  // 2025-03-17: clock_pc=33ms --> lowest=delay(34)
  
  sendMsg(errorFrame);
  Frame frame = readMsg();
  delay(50);  
}

void sendMsg(Frame frame) {
  // * Si le code bug et que le buffer reste rempli, decommenter les 3 lignes suivantes
  // while (Serial.available()) {
  //   Serial.read();
  // }
  
  //Creation de message
  byte msg[MSG_SIZE] = {frame.id, frame.data, frame.checksum};
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
  // if (msg[0] != MSG_ID_FROM_PC) { 
  //   Serial.println("WARING-AR: Invalid message! Message ignored");
  //   return errorFrame; 
  // }
 
  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE - 1; i++) {
    checksum ^= msg[i];
  }
  if (checksum != msg[MSG_SIZE - 1]) { 
    Serial.println("WARING-AR: Checksum error! Message ignored");
    return errorFrame;  
    }

  Frame frame = {msg[0], msg[1], msg[2]};
  return frame;
}

Frame readMsg(byte id){
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
  if (msg[0] != id) { 
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

  Frame frame = {msg[0], msg[1], msg[2]};
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
