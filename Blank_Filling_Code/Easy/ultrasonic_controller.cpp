#include "ultrasonic_controller.h"

ultrasonic_controller* ultrasonic_controller::instance = nullptr;

ultrasonic_controller::ultrasonic_controller()
{
    leftPin  = ULTRASONIC_RX_LEFT_PIN;
    rightPin = ULTRASONIC_RX_RIGHT_PIN;

    leftTime = 0;
    rightTime = 0;
    leftDetected = false;
    rightDetected = false;

    instance = this;
}

void ultrasonic_controller::init()
{
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);

    attachInterrupt(digitalPinToInterrupt(leftPin),  leftISR,  FALLING);
    attachInterrupt(digitalPinToInterrupt(rightPin), rightISR, FALLING);
}

void IRAM_ATTR ultrasonic_controller::leftISR()
{
    if (instance && !instance->leftDetected)
    {
        instance->leftTime = micros();
        instance->leftDetected = true;
    }
}

void IRAM_ATTR ultrasonic_controller::rightISR()
{
    if (instance && !instance->rightDetected)
    {
        instance->rightTime = micros();
        instance->rightDetected = true;
    }
}

bool ultrasonic_controller::available()
{
    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

int16_t ultrasonic_controller::getTimeDiff()
{
    // 还没有获得完整检测
    if (!leftDetected || !rightDetected) return 0;

    long diff = 0;

    noInterrupts();
    diff = (long)leftTime - (long)rightTime;
    leftDetected = false;
    rightDetected = false;
    interrupts();
    
    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void ultrasonic_controller::reset()
{
    noInterrupts();
    leftDetected = false;
    rightDetected = false;
    interrupts();
}
