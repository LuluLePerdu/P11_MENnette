//#include "ShakeItModel.h"
//#include <algorithm>
//
//random_device rd;
//mt19937 gen(rd());
//uniform_int_distribution<int> distr(0, 1023);
//
//ShakeItModel::ShakeItModel(QObject* parent) : QObject(parent), realValue(0), targetValue(0) {}
//ShakeItModel::~ShakeItModel() {}
//
//int ShakeItModel::interpolateLength(float value) {
//    value = std::max(0.0f, std::min(value, static_cast<float>(MAX_BARGRAPH_VALUE)));
//    float lenVal = (realValue - targetValue) * 0.2f;
//    targetValue += lenVal;
//    return static_cast<int>(targetValue / MAX_BARGRAPH_VALUE * MAX_BARGRAPH_LENGTH);
//}
//
//int ShakeItModel::getMaxLength() const {
//    return MAX_BARGRAPH_LENGTH;
//}
//
//int ShakeItModel::getMaxValue() const {
//    return MAX_BARGRAPH_VALUE;
//}
//
//int ShakeItModel::getValue() const {
//    return realValue;
//}
//
//void ShakeItModel::setValue(float value) {
//    value = std::max(0.0f, std::min(value, static_cast<float>(MAX_BARGRAPH_VALUE)));
//    realValue = value;
//    targetValue = realValue;
//    emit lengthChanged(interpolateLength(value));
//}
//
//int ShakeItModel::getLength() {
//    return interpolateLength(realValue);
//}
