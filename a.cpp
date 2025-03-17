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

int ledState = 0;
int inc = 0;

void sendMsg(HANDLE hSerial);
void readMsg(HANDLE hSerial);
bool configureSerialPort(HANDLE hSerial);

int main() {
    string com;
    cout << "Entrer le port de communication du Arduino: ";
    cin >> com;

    // Open the serial port
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

    while (true) {
        sendMsg(hSerial);
        readMsg(hSerial);
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

void sendMsg(HANDLE hSerial) {
    // Creation de message
    // message bidon de base qui fait clignoter toute les leds
    byte msg[MSG_SIZE] = {MSG_ID_FROM_PC, ledState, 0, 0, 0, 0, 0, 0, 0};
    inc++;
    if (inc >= 15) {
        ledState == 0 ? ledState = 255 : ledState = 0;
        inc = 0;
    }

    // Checksum via XOR de tous les bytes
    byte checksum = 0;
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

void readMsg(HANDLE hSerial) {
    byte msg[MSG_SIZE] = {0}; 
    DWORD bytesRead;
    byte startByte = MSG_ID_FROM_ARDUINO;

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
            return;
        }
        if (msg[0] == startByte) {
            break;
        }
    }

    // Lecture 
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
        return;
    }

    byte checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        cerr << "WARNING-PC: Checksum error! Message ignored" << endl;
        return;
    }

    cout << "LOG-PC: Received message: ";
    for (int i = 0; i < MSG_SIZE; i++) {
        cout << setw(3) << (int)msg[i] << " ";
    }
    cout << endl;
}