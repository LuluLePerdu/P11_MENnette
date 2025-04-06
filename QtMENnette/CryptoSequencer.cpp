#include "CryptoSequencer.h"
#include <qmessagebox.h>


CryptoSequencer::CryptoSequencer()
{
	this->initialize();
}

CryptoSequencer::CryptoSequencer(int range)
{
	m_range = range;
    this->initialize();
}

CryptoSequencer::~CryptoSequencer()
{
}

void CryptoSequencer::initialize() {
    Communication& comm = Communication::getInstance();
	comm.clear();
    std::default_random_engine randomEngine(comm.seed);
    target = (std::rand() % 255);
    char digits[15] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'F'}; 

    for (int i = 0; i < CODE_LENGTH; i++) {

        code[i] = digits[std::rand() % 15];
    }
	code[CODE_LENGTH] = '\0';
}

std::string CryptoSequencer::updateSequence() {
	if (isOver) {
		return "GAME COMPLETED!";
	}
    Communication& comm = Communication::getInstance();
    int keyInput = -1;
    int usrInput = -1;

    std::vector<unsigned char> idsToRead = { MSG_ID_AR_KEYPAD, MSG_ID_AR_POTENTIOMETER };
    std::map<unsigned char, unsigned char> lcture = comm.readMultipleMsgs(idsToRead);
    if (lcture.find(MSG_ID_AR_KEYPAD) != lcture.end()) {
        keyInput = lcture[MSG_ID_AR_KEYPAD];
    }

    if (lcture.find(MSG_ID_AR_POTENTIOMETER) != lcture.end()) {
        usrInput = lcture[MSG_ID_AR_POTENTIOMETER];
    }

    comm.clear();
    char characters[32] = "!@/\\$%?&*()=+#|\\*-[]^<>}{`;:,.'";

    std::string outputCode(CODE_LENGTH, ' ');
    for (int i = 0; i < 10; i++) {
        outputCode[i] = characters[std::rand() % 32];
    }


    if (usrInput == -2) {
        return "NO CONTROLLER";
    }

    if (usrInput >= 0) {
        int distance = static_cast<int>(CODE_LENGTH * std::abs(target - usrInput) / m_range);
        if (distance > CODE_LENGTH) distance = CODE_LENGTH;

        for (int i = 0; i < CODE_LENGTH - distance; i++) {
            outputCode[i] = code[i];
        }
        lastInput = usrInput;
    }
    else {
        int distance = static_cast<int>(CODE_LENGTH * std::abs(target - lastInput) / m_range);
        if (distance > CODE_LENGTH) distance = CODE_LENGTH;

        for (int i = 0; i < CODE_LENGTH - distance; i++) {
            outputCode[i] = code[i];
        }
    }

    if (keyInput >= 0) {
        if (checkCode(keyInput)) {
			isOver = true;
            return "CODE OK";
            
        }

    }

    return outputCode;
}

bool CryptoSequencer::checkCode(int keyInput) {
    if (receivedCodeLength >= CODE_LENGTH) {
        receivedCodeLength = 0;
        return false;
    }
    if (keyInput == 66) {
        keyInput = '0';
    }
    switch (keyInput)
    {
    case '*':
		keyInput = 'A';
		break;
	case '#':
		keyInput = 'B';
		break;
	case 'D':
		keyInput = 'C';
		break;
	case 'C':
		keyInput = 'D';
		break;
    /*case '0':
		keyInput = 'E';
		break;*/
    case 'A': 
		keyInput = 'F';
		break;
    default:
        break;
    }

    if (receivedCodeLength < CODE_LENGTH) {
        receivedCode[receivedCodeLength++] = static_cast<char>(keyInput);
    }

    if (receivedCodeLength == CODE_LENGTH) {
		receivedCode[receivedCodeLength] = '\0';
        if (strcmp(receivedCode, code) == 0) {
            receivedCodeLength = 0;
            return true;
        }
        else {
            receivedCodeLength = 0;
			wrongCode = true;
            return false;
        }
    }

    // Still collecting digits
    return false;
}

std::string CryptoSequencer::randomizeString(std::string input, float percent) {
    if (input.empty()) {
        return "";  // Handle empty string case
    }

    std::string output = input;
    std::random_device rd;
    std::mt19937 mt(rd());

    const char characters[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm$%?&*()=+#|*-[]^<>}{`;:,.";
    int charLength = static_cast<int>(strlen(characters)) - 1;

    std::uniform_int_distribution<int> charDist(0, std::max(0, charLength));
    std::uniform_int_distribution<int> posDist(0, std::max(0, static_cast<int>(input.size()) - 1));

    int numChanges = std::max(0, static_cast<int>(input.size() * percent));

    for (int i = 0; i < numChanges; ++i) {
        if (!input.empty()) {
            int pos = posDist(mt);
            output[pos] = characters[charDist(mt)];
        }
    }

    return output;
}

std::string CryptoSequencer::getUserCode() {
	if (receivedCodeLength == 0) {
		return "NO CODE";
	}
	std::string userCode;
	for (int i = 0; i < receivedCodeLength; i++) {
		userCode += receivedCode[i];
	}
	return userCode;
}