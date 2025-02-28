#pragma once
#include <random>

using namespace std;


class ShakeItModel
{
public:
	ShakeItModel();
	~ShakeItModel();
	int getLength();
	int getMaxLength() const;
	int getMaxValue() const;
	void setValue(float value);
	int getValue() const;
	float realValue;

private:
	float magnitude();
	float targetValue;
	int interpolateLength(float value);
	const int MAX_BARGRAPH_LENGTH = 100;
	const int MAX_BARGRAPH_VALUE = 1023;

};
