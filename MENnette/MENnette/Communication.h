#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

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

class Communication {
public:
    static Communication& getInstance() {
        static Communication instance;
        return instance;
    }
    Communication(Communication const&) = delete;
    void operator=(Communication const&) = delete;

    bool begin();
    bool configureSerialPort();
    void sendMsg(Frame frame);
    int readMsg();
    int readMsg(uint8_t id);
	HANDLE getSerialPort();
	void setSerialPort(HANDLE hSerial);
	void closeSerialPort();
    void clear();

private:
    Communication() { this->begin(); }
    ~Communication() {}
    Frame errorFrame = { MSG_ID_ERROR, 0, 0 };;
	HANDLE hSerial;
};