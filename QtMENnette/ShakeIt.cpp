#include "ShakeIt.h"

ShakeIt::ShakeIt()
{
}
ShakeIt::~ShakeIt()
{
}
void ShakeIt::initialize()
{
	Communication& comm = Communication::getInstance();
	std::default_random_engine randomEngine(comm.seed);
	target = (std::rand() % 255);
	
}

int ShakeIt::update()
{
	Communication& comm = Communication::getInstance();
	int input = comm.readMsg(MSG_ID_AR_ACCELEROMETER);

	return input;
}