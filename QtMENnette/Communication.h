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

#define BAUD 9600
#define MSG_SIZE 3
#define TIMEOUT_READ 20 //50

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
    int seed = 98212321;


private:
    Communication() { this->begin(); }
    ~Communication() { this->closeSerialPort(); }
    Frame errorFrame = { MSG_ID_ERROR, 0, 0 };
    HANDLE hSerial;
	bool connected = false;
};