#pragma once
#include "ShakeItModel.h"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distr(0, 1023);

ShakeItModel::ShakeItModel(){
	realValue = 0;
	targetValue = 0;
}
ShakeItModel::~ShakeItModel(){
}

int ShakeItModel::getLength() {
	//return interpolateLength(distr(gen));
	return interpolateLength(realValue);
}

int ShakeItModel::getMaxLength() const{
	return MAX_BARGRAPH_LENGTH;
}

int ShakeItModel::getMaxValue() const{
	return MAX_BARGRAPH_VALUE;
}

int ShakeItModel::getValue() const {
	return realValue;
}

void ShakeItModel::setValue(float value) {
	value = value < 0 ? 0 : value;
	value = value > MAX_BARGRAPH_VALUE ? MAX_BARGRAPH_VALUE : value;
	realValue = value;
}

int ShakeItModel::interpolateLength(float value) {
	value = value < 0 ? 0 : value;
	value = value > MAX_BARGRAPH_VALUE ? MAX_BARGRAPH_VALUE : value;

	float lenVal = (realValue - targetValue) * 0.2;
	targetValue += lenVal;
	return static_cast<int>(targetValue / MAX_BARGRAPH_VALUE * MAX_BARGRAPH_LENGTH);

}