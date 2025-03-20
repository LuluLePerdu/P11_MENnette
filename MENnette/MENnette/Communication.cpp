#include "Communication.h"

//Initialisation de la communication
bool Communication::begin() {
    hSerial = CreateFileW(L"COM4", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
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

//Config de base
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

    // envoie
    DWORD bytesWritten;
    if (!WriteFile(hSerial, msg, MSG_SIZE, &bytesWritten, NULL)) {
        //cerr << "WARNING-PC: Error writing to serial port" << endl;
    }
}

// DESCRIPTION: Lit le message le plus recent du buffer serial et retourne la valeur apres l'ID.
//              Retourne -1 si le message est invalide
// P.S: Est techniquement fonctionnel, mais je ne recommande pas de l'utiliser; Tres volatile et indeterministe
// ! Utiliser plutot la version avec un ID si possible!
// -Zakary
int Communication::readMsg() {
    uint8_t msg[MSG_SIZE] = { 0 };
    Frame frame;
    DWORD bytesRead;
    uint8_t startByte = msg[0];

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            return -1;
        }
        if (msg[0] == startByte) {
            break;
        }
    }

    // Lecture 
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        return -1;
    }

    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        return -1;
    }
    return msg[1];
}


// DESCRIPTION: Cherche et lit un message avec un ID, et retourne la valeur de data.
//              Retourne -1 si le message est invalide
// ! P.S: Utiliser cette fonction plutot que la version sans ID; Plus stable et fiable!
// Je recommande de faire un Communication::clear() apres la lecture, ca evite les problemes de backlogs dans le buffer
int Communication::readMsg(uint8_t id) {
    uint8_t msg[MSG_SIZE] = { 0 };
    DWORD bytesRead;

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            return -1;
        }
        if (msg[0] == id) {
            break;
        }
    }
    // Lecture 
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        return -1;
    }

    uint8_t checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        return -1;
    }

	for (int i = 0; i < MSG_SIZE; i++) {
		cout << (int)msg[i] << " ";
	}
	cout << endl;
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

// DESCRIPTION: Vide le buffer du serial. Peut etre utile pour eviter les problemes de backlog lors de la lecture
void Communication::clear() {
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
}

uint8_t Communication::convertBoolsToByte(bool p_sw[8]) {
    byte b = 0;
    for (int i = 0; i < 8; i++) {
        b |= (p_sw[i] << i); // Met le bit i à 1 si p_sw[i] est vrai
    }
    return b;
}

void Communication::byteToBoolArray(byte b, bool arr[8]) {
    for (int i = 0; i < 8; i++) {
        arr[i] = (b >> i) & 1; // Met arr[i] à vrai si le bit i de b est à 1
    }
}