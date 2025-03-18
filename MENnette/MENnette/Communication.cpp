#include "Communication.h"

Communication::Communication() {
    errorFrame = { MSG_ID_ERROR, 0, 0 };
	this->begin();
}

Communication::~Communication() {
    // Destructor implementation (if needed)
}

bool Communication::begin() {
    hSerial = CreateFileW(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << " ERROR-PC: Error opening serial port" << endl;
		return false;
    }
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR); // vide le buffer du serial
    this_thread::sleep_for(chrono::milliseconds(1000));


    if (!configureSerialPort()) {
        cerr << "ERROR-PC: Error configuring serial port" << endl;
        CloseHandle(hSerial);
        return false;
    }
	return true;
}

bool Communication::configureSerialPort() {

    DCB dcbSerialParams = { 0 };
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

void Communication::sendMsg(Frame frame) {
    // Creation de message
    uint8_t msg[MSG_SIZE] = { frame.id, frame.data, 0 };

    // Checksum via XOR de tous les bytes
    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    msg[MSG_SIZE - 1] = checksum;
    //cout << "LOG-PC: Sending message:  ";
    for (int i = 0; i < MSG_SIZE; i++) {
        cout << setw(3) << (int)msg[i] << " ";
    }
    cout << endl;

    // envoie
    DWORD bytesWritten;
    if (!WriteFile(hSerial, msg, MSG_SIZE, &bytesWritten, NULL)) {
        //cerr << "WARNING-PC: Error writing to serial port" << endl;
    }
}

int Communication::readMsg() {
    uint8_t msg[MSG_SIZE] = { 0 };
    Frame frame;
    DWORD bytesRead;
    uint8_t startByte = msg[0];

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            //cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
            return -1;
        }
        if (msg[0] == startByte) {
            break;
        }
    }

    // Lecture 
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        //cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
        return -1;
    }

    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        //cerr << "WARNING-PC: Checksum error! Message ignored" << endl;
        return -1;
    }

    /*cout << "LOG-PC: Received message: ";
    for (int i = 0; i < MSG_SIZE; i++) {
        cout << setw(3) << (int)msg[i] << " ";
    }
    cout << endl;*/
    //frame = { msg[0], msg[1], msg[2] };
    return msg[1];
}

int Communication::readMsg(uint8_t id) {
    uint8_t msg[MSG_SIZE] = { 0 };
    DWORD bytesRead;

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            //cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
            return -1;
        }
        if (msg[0] == id) {
            break;
        }
    }

    // Lecture 
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        //cerr << "WARNING-PC: Not enough bytes read! Message ignored" << endl;
        return -1;
    }

    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        //cerr << "WARNING-PC: Checksum error! Message ignored" << endl;
        return -1;
    }

    /*cout << "LOG-PC: Received message: ";
    for (int i = 0; i < MSG_SIZE; i++) {
        cout << setw(3) << (int)msg[i] << " ";
    }
    cout << endl;*/
    //Frame frame = { msg[0], msg[1], msg[2] };
    return msg[1];
}

HANDLE Communication::getSerialPort() {
	return hSerial;
}

void Communication::setSerialPort(HANDLE hSerial) {
	this->hSerial = hSerial;
}

void Communication::closeSerialPort() {
	CloseHandle(hSerial);
}

void Communication::clear() {
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
}