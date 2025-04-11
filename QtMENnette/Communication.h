// * Autheur: Zakary Romdhane
// * Date: 2025/03/16
// * Modification: 2025/04/10
// * Description: Communication custom pour l'ardunio du projet de session S2 2025 de l'équipe P11

#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>

#include <map>
//using namespace std; 
//! NE PAS UTILISER NAMESPACE STD! BYTES AMBIGUS AVEC windows.h (?!)

#define BAUD 9600   // A METTRE A 115200? 
                    // NON! 
#define MSG_SIZE 3
#define TIMEOUT_READ 5//50//20?//10?

#define MSG_ID_ERROR 71
#define MSG_DATA_ERROR -1
#define MSG_ID_OK 72
#define MSG_DATA_OK 72
#define MSG_DATA_NOT_CONNECTED -2
#define MSG_DATA_ERROR_INCOMPLETE -10
#define MSG_DATA_ERROR_CHECKSUM -11
#define MSG_DATA_ERROR_TIMEOUT -12


#define MSG_ID_AR_JOYSTICK 101
#define MSG_ID_AR_POTENTIOMETER 102
#define MSG_ID_AR_ACCELEROMETER 103
#define MSG_ID_AR_BUTTON 104
#define MSG_ID_AR_SHAKED 105
#define MSG_ID_AR_KEYPAD 106
#define MSG_ID_AR_MUON 107

#define MSG_ID_PC_LED 201
#define MSG_ID_PC_MOTOR 202
#define MSG_ID_PC_LCD 203
#define MSG_ID_PC_STATE 204
#define MSG_ID_PC_TIMER 205
#define MSG_ID_PC_MUON 207
#define MSG_ID_FROM_MISC 242

struct Frame {
    unsigned char id;
    unsigned char data;
    unsigned char checksum;
};

class Communication {
public:
    static Communication& getInstance() {
        static Communication instance;
        return instance;
    }
    Communication(Communication const&) = delete;
    void operator=(Communication const&) = delete;

    std::wstring getOpenCOM();
    bool begin();
    bool configureSerialPort();
	int createSeed();
    void sendMsg(Frame frame);
    Frame readMsg();
    int readMsg(int id);
	std::map<unsigned char, unsigned char> readMultipleMsgs(const std::vector<unsigned char>& ids);
    HANDLE getSerialPort();
    void setSerialPort(HANDLE hSerial);
    void closeSerialPort();
    void clear();
    unsigned char convertBoolsToByte(bool p_sw[8]);
    void byteToBoolArray(unsigned char b, bool arr[8]);
    int seed = 0;
	void buzz(unsigned char strength);
	void sendTime(unsigned char time);


private:
    Communication() { this->begin(); }
    ~Communication() { this->closeSerialPort(); }
    Frame errorFrame = { MSG_ID_ERROR, 0, 0 };
    HANDLE hSerial;
	bool connected = false;
};