#include "Communication.h"

std::wstring Communication::getOpenCOM() {
    wchar_t comName[12];

    for (int i = 1; i <= 256; i++) {
        _snwprintf_s(comName, 10, L"\\\\.\\COM%d", i); 
        HANDLE hPort = CreateFileW(comName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
        if (hPort != INVALID_HANDLE_VALUE) {
            std::wstringstream ws;
            // stringstream ws;
            ws << L"COM" << i; 
            CloseHandle(hPort);
            return ws.str(); // wstringstream to wstring
        }
    }
    return L"ERROR";

}

//Initialisation de la communication
bool Communication::begin() {

    std::wstring com = getOpenCOM();
    if (com == L"ERROR") {
        std::cerr << "ERROR-PC: No COM ports available" << std::endl;
        return false;
    }
    hSerial = CreateFileW(com.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << " ERROR-PC: Error opening serial port" << std::endl;
        return false;
    }
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR); // vide le buffer du serial
    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    if (!configureSerialPort()) {
        std::cerr << "ERROR-PC: Error configuring serial port" << std::endl;
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
        std::cerr << "ERROR-PC: Error getting serial port state" << std::endl;
        return false;
    }
    //parametres du port
    // ! Pas touche 
    dcbSerialParams.BaudRate = BAUD;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "ERROR-PC: Error setting serial port state" << std::endl;
        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = TIMEOUT_READ;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "ERROR-PC: Error setting serial port timeouts" << std::endl;
        return false;
    }
    return true;
}

int Communication::createSeed() {
	time_t initTime = time(nullptr);
    int a = 0;
	while (a == 0) {
		a = readMsg(MSG_ID_FROM_MISC);
		clear();
	    if (a == MSG_DATA_ERROR) {
		    return 0;
	    }
	}
	time_t finalTime = time(nullptr);
	int seed = difftime(finalTime, initTime);
	return seed;
}


void Communication::sendMsg(Frame frame) {
    // Creation de message
    unsigned char msg[MSG_SIZE] = { frame.id, frame.data, 0 };

    // Checksum via XOR de tous les bytes
    unsigned char checksum = 0;
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
Frame Communication::readMsg() {
    unsigned char msg[MSG_SIZE] = { 0 };
    DWORD bytesRead;
    DWORD startTime = GetTickCount();

    // Read the first byte
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            if (GetTickCount() - startTime > TIMEOUT_READ) { // Timeout after TIMEOUT_READ ms
                return errorFrame;
            }
            continue;
        }
        break;
    }

    // Read the rest of the message
    if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
        return errorFrame;
    }

    // Validate the checksum
    unsigned char checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        return errorFrame;
    }

    Frame frame = { msg[0], msg[1], msg[2] };
    return frame;
}

// DESCRIPTION: Cherche et lit un message avec un ID, et retourne la valeur de data.
//              Retourne -1 si le message est invalide
// ! P.S: Utiliser cette fonction plutot que la version sans ID; Plus stable et fiable!
// Je recommande de faire un Communication::clear() apres la lecture, ca evite les problemes de backlogs dans le buffer
int Communication::readMsg(unsigned char id) {
    unsigned char msg[MSG_SIZE] = { 0 };
    DWORD bytesRead;
    DWORD startTime = GetTickCount();

    // Synchronize avec le debut du message MSG_ID_FROM_ARDUINO
    while (true) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            if (GetTickCount() - startTime > TIMEOUT_READ) {
                return -1;
            }
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

    unsigned char checksum = 0;
    for (int i = 0; i < MSG_SIZE - 1; i++) {
        checksum ^= msg[i];
    }
    if (checksum != msg[MSG_SIZE - 1]) {
        return -1;
    }

    /*for (int i = 0; i < MSG_SIZE; i++) {
        cout << (int)msg[i] << " ";
    }
    cout << endl;*/
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

unsigned char Communication::convertBoolsToByte(bool p_sw[8]) {
    unsigned char b = 0;
    for (int i = 0; i < 8; i++) {
        b |= (p_sw[i] << i); // Met le bit i � 1 si p_sw[i] est vrai
    }
    return b;
}

void Communication::byteToBoolArray(unsigned char b, bool arr[8]) {
    for (int i = 0; i < 8; i++) {
        arr[i] = (b >> i) & 1; // Met arr[i] � vrai si le bit i de b est � 1
    }
}