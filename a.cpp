// * Autheur: Zakary Romdhane
// * Date: 2025/03/16
// * Description: Programme PC pour la communcation avec un Arduino via serial
// *              Cree pour la S2.
// *              

#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

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

void sendMsg(HANDLE hSerial, Frame frame);
Frame readMsg(HANDLE hSerial);
bool configureSerialPort(HANDLE hSerial);

int main() {
    string com;
    cout << "Entrer le port de communication du Arduino: ";
    cin >> com;
    
    wstring comW(com.begin(), com.end());
    HANDLE hSerial = CreateFileW(comW.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << " ERROR-PC: Error opening serial port" << endl;
        return -1;
    }
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR); // vide le buffer du serial

    if (!configureSerialPort(hSerial)) {
        cerr << "ERROR-PC: Error configuring serial port" << endl;
        CloseHandle(hSerial);
        return -1;
    }
    Frame frame = {MSG_ID_FROM_PC, 255, 2, 3, 4, 5, 6, 7, 0};

    while (true) {
        sendMsg(hSerial, frame);
        Frame test = readMsg(hSerial);
        this_thread::sleep_for(chrono::milliseconds(33));
    }

    CloseHandle(hSerial);
    return 0;
}

//grosse criss de fonction de config, a modifier si votre arduino geek out
bool configureSerialPort(HANDLE hSerial) {
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "ERROR-PC: Error getting serial port state" << endl;
        return false;
    }
    //parametres du port
    // ! Pas touche 
    dcbSerialParams.BaudRate = BAUD;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cerr << "ERROR-PC: Error setting serial port state" << endl;
        return false;
    }
    return true;
}

void sendMsg(HANDLE hSerial, Frame frame) {
    // Creation de message
    uint8_t msg[MSG_SIZE] = {frame.id, frame.ledState, frame.potentiometer, frame.joystickX, frame.joystickY, frame.accelerometerX, frame.accelerometerY, frame.accelerometerZ, 0};

    // Checksum via XOR de tous les bytes
    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    msg[MSG_SIZE - 1] = checksum;
    cout << "LOG-PC: Sending message:  ";
    for (int i = 0; i < MSG_SIZE; i++) {
        cout << setw(3) << (int)msg[i] << " ";
    }
    cout << endl;

    // envoie
    DWORD bytesWritten;
    if (!WriteFile(hSerial, msg, MSG_SIZE, &bytesWritten, NULL)) {
        cerr << "WARNING-PC: Error writing to serial port" << endl;
    }
}

Frame readMsg(HANDLE hSerial) {
    uint8_t msg[MSG_SIZE] = {0}; 
    DWORD bytesRead;
    uint8_t startByte = MSG_ID_FROM_ARDUINO;

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
            return errorFrame;
        }
        if (msg[0] == startByte) {
            break;
        }
    }

    // Lecture 
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
        return errorFrame;
    }

    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        cerr << "WARNING-PC: Checksum error! Message ignored" << endl;
        return errorFrame;
    }

    cout << "LOG-PC: Received message: ";
    for (int i = 0; i < MSG_SIZE; i++) {
        cout << setw(3) << (int)msg[i] << " ";
    }
    cout << endl;
    Frame frame = {msg[0], msg[1], msg[2], msg[3], msg[4], msg[5], msg[6], msg[7], msg[8]};
    return frame;
}
