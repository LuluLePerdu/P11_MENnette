#pragma once
#include <random>
#include <QObject>

using namespace std;

class ShakeItModel : public QObject
{
    Q_OBJECT
public:
    explicit ShakeItModel(QObject* parent = nullptr);
    ~ShakeItModel();
    int getLength(); 
    int getMaxLength() const;
    int getMaxValue() const;
    void setValue(float value);
    int getValue() const;

signals:
    void lengthChanged(int value);

private:
    float magnitude();
    float targetValue;
    int interpolateLength(float value);
    const int MAX_BARGRAPH_LENGTH = 100;
    const int MAX_BARGRAPH_VALUE = 1023;
    float realValue;
};
