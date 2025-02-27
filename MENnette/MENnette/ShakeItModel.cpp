#pragma once
#include "shakeitmodel.h"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distr(0, 1023);

ShakeItModel::ShakeItModel(){
	value = 0;
}
ShakeItModel::~ShakeItModel(){
}

int ShakeItModel::getLength() {
	//return interpolateLength(distr(gen));
	return interpolateLength(this->value);
}

int ShakeItModel::getMaxLength() const{
	return MAX_BARGRAPH_LENGTH;
}

int ShakeItModel::getMaxValue() const{
	return MAX_BARGRAPH_VALUE;
}

void ShakeItModel::setValue(float value) {
	this->value = value;
}

int ShakeItModel::interpolateLength(float value) {
	value = value < 0 ? 0 : value;
	value = value > MAX_BARGRAPH_VALUE ? MAX_BARGRAPH_VALUE : value;
	return static_cast<int>(value / MAX_BARGRAPH_VALUE * MAX_BARGRAPH_LENGTH);
}