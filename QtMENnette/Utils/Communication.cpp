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

// DESCRIPTION: Demande un seed (premier muon recu) OU timeout de 5 secondes
int Communication::createSeed() {
    time_t initTime = time(nullptr);
    sendMsg({ MSG_ID_PC_MUON, 1, 0 }); // Demande de seed
    int a = -1;
    while (a < 0) {
        if (difftime(time(nullptr), initTime) >= 5.0) {
            return 0; // Timeout
        }
        a = readMsg(MSG_ID_AR_MUON);
    }
    time_t finalTime = time(nullptr);
    int seed = difftime(finalTime, initTime);
    return seed;
}

//Initialisation de la communication
bool Communication::begin() {

    std::wstring com = getOpenCOM();
    if (com == L"ERROR") {
        std::cerr << "ERROR-PC: No COM ports available" << std::endl;
        return false;
    }
	//com.c_str()
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
    connected = true;
	seed = createSeed();
    return true;
}


void Communication::sendMsg(Frame frame) {
	if (!connected) {
		return;
	}
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
	if (!connected) {
        Frame frame = { MSG_ID_ERROR, MSG_DATA_NOT_CONNECTED, 0 };
        return frame;
	}
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
int Communication::readMsg(int id) {
    if (!connected) {
        return MSG_DATA_NOT_CONNECTED;
    }

    unsigned char msg[MSG_SIZE] = { 0 };
    DWORD bytesRead;
    DWORD startTime = GetTickCount();

    while (GetTickCount() - startTime < TIMEOUT_READ) {
		// essai de lire un byte
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            continue;
        }
        if (msg[0] == id) {
            if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
                return MSG_DATA_ERROR_INCOMPLETE;
            }

            //checksum
            unsigned char checksum = 0;
            for (int i = 0; i < MSG_SIZE - 1; i++) {
                checksum ^= msg[i];
            }
            if (checksum != msg[MSG_SIZE - 1]) {
                return MSG_DATA_ERROR_CHECKSUM;
            }

            return msg[1];
        }
		// si pas le ID, on lit le reste du message pour le retirer d buffer!!!!!
        else {
            unsigned char discard[MSG_SIZE - 1];
            if (!ReadFile(hSerial, discard, MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
                //jsp ca marche
                continue;
            }
        }
    }

    return MSG_DATA_ERROR_TIMEOUT;
}

std::map<unsigned char, unsigned char> Communication::readMultipleMsgs(const std::vector<unsigned char>& ids) {
    std::map<unsigned char, unsigned char> results;
    if (!connected) {
        return results;
    }

    unsigned char msg[MSG_SIZE] = { 0 };
    DWORD bytesRead;
    DWORD startTime = GetTickCount();

    while (GetTickCount() - startTime < TIMEOUT_READ && results.size() < ids.size()) {
        if (!ReadFile(hSerial, &msg[0], 1, &bytesRead, NULL) || bytesRead < 1) {
            continue;
        }

        bool isTargetId = false;
        for (unsigned char targetId : ids) {
            if (msg[0] == targetId) {
                isTargetId = true;
                break;
            }
        }

        if (!ReadFile(hSerial, &msg[1], MSG_SIZE - 1, &bytesRead, NULL) || bytesRead < MSG_SIZE - 1) {
            continue; 
        }

        if (isTargetId) {
            unsigned char checksum = 0;
            for (int i = 0; i < MSG_SIZE - 1; i++) {
                checksum ^= msg[i];
            }

            if (checksum == msg[MSG_SIZE - 1]) {
                if (results.find(msg[0]) == results.end()) {
                    results[msg[0]] = msg[1];
                }
            }
        }
    }

    return results;
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
        b |= (p_sw[i] << i); // Met le bit i à 1 si p_sw[i] est vrai
    }
    return b;
}

void Communication::byteToBoolArray(unsigned char b, bool arr[8]) {
    for (int i = 0; i < 8; i++) {
        arr[i] = (b >> i) & 1; // Met arr[i] à vrai si le bit i de b est à 1
    }
}

void Communication::buzz(unsigned char strength){
	sendMsg({ MSG_ID_PC_MOTOR, strength, 0 });
}

void Communication::sendTime(unsigned char time){
	sendMsg({ MSG_ID_PC_TIMER, time, 0 });
}