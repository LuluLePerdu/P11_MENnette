#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

#define BAUD 9600 
#define MSG_SIZE 3
#define TIMEOUT_READ 50

#define MSG_ID_ERROR 71
#define MSG_DATA_ERROR 71
#define MSG_ID_OK 72
#define MSG_DATA_OK 72


#define MSG_ID_AR_JOYSTICK 101
#define MSG_ID_AR_POTENTIOMETER 102
#define MSG_ID_AR_ACCELEROMETER 103
#define MSG_ID_AR_BUTTON 104
#define MSG_ID_AR_SHAKED 105
#define MSG_ID_AR_MUON 106

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

class Communication {
public:
    static Communication& getInstance() {
        static Communication instance;
        return instance;
    }
    Communication(Communication const&) = delete;
    void operator=(Communication const&) = delete;

    wstring getOpenCOM();
    bool begin();
    bool configureSerialPort();
	int createSeed();
    void sendMsg(Frame frame);
    Frame readMsg();
    int readMsg(uint8_t id);
    HANDLE getSerialPort();
    void setSerialPort(HANDLE hSerial);
    void closeSerialPort();
    void clear();
    uint8_t convertBoolsToByte(bool p_sw[8]);
    void byteToBoolArray(uint8_t b, bool arr[8]);
    int seed = 0;


private:
    Communication() { this->begin(); }
    ~Communication() { this->closeSerialPort(); }
    Frame errorFrame = { MSG_ID_ERROR, 0, 0 };
    HANDLE hSerial;
};