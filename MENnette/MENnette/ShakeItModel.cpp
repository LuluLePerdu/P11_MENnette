#pragma once
#include "shakeitmodel.h"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distr(0, 1023);

ShakeItModel::ShakeItModel(){
}
ShakeItModel::~ShakeItModel(){
}

int ShakeItModel::getLength() {
	return interpolateLength(distr(gen));
}

int ShakeItModel::getMaxLength() const{
	return MAX_BARGRAPH_LENGTH;
}

int ShakeItModel::getMaxValue() const{
	return MAX_BARGRAPH_VALUE;
}

int ShakeItModel::interpolateLength(float value) {
	value = value < 0 ? 0 : value;
	value = value > MAX_BARGRAPH_VALUE ? MAX_BARGRAPH_VALUE : value;
	return static_cast<int>(value / MAX_BARGRAPH_VALUE * MAX_BARGRAPH_LENGTH);
}