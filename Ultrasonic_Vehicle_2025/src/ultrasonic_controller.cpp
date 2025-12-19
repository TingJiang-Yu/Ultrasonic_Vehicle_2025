#include "ultrasonic_controller.h"

// 初始化静态成员
ultrasonic_controller* ultrasonic_controller::instance = nullptr;

// 构造函数
ultrasonic_controller::ultrasonic_controller()
{   
    leftPin = ULTRASONIC_RX_LEFT_PIN;
    rightPin = ULTRASONIC_RX_RIGHT_PIN;

    leftTime = 0;
    rightTime = 0;
    leftDetected = false;
    rightDetected = false;

    lastLeftTime = 0;
    lastRightTime = 0;
    debounceTime = 50;
    
    instance = this;
}

// 初始化函数
void ultrasonic_controller::init() 
{
    // 配置引脚
    pinMode(leftPin, INPUT_PULLUP);
    pinMode(rightPin, INPUT_PULLUP);
    
    // 附加中断
    attachInterrupt(digitalPinToInterrupt(leftPin), leftISR, RISING);
    attachInterrupt(digitalPinToInterrupt(rightPin), rightISR, RISING);
}

// 左接收器中断服务函数（静态）
void ultrasonic_controller::leftISR() 
{
    if (instance) 
    {
        unsigned long now = micros();
        // 防抖处理
        if (now - instance->lastLeftTime > instance->debounceTime) 
        {
            instance->leftTime = now;
            instance->leftDetected = true;
            instance->lastLeftTime = now;
        }
    }
}

// 右接收器中断服务函数（静态）
void ultrasonic_controller::rightISR() 
{
    if (instance) 
    {
        unsigned long now = micros();
        // 防抖处理
        if (now - instance->lastRightTime > instance->debounceTime) 
        {
            instance->rightTime = now;
            instance->rightDetected = true;
            instance->lastRightTime = now;
        }
    }
}

// 检查是否有新数据
bool ultrasonic_controller::available() 
{
    return leftDetected && rightDetected;
}

// 获取时间差
long ultrasonic_controller::getTimeDiff() 
{
    if (leftDetected && rightDetected) 
    {
        long diff = (long)(leftTime - rightTime);
        
        leftDetected = false;
        rightDetected = false;
        
        return diff;
    }
    return 0;
}

// 获取左接收器时间戳
unsigned long ultrasonic_controller::getLeftTime() 
{
    return leftTime;
}

// 获取右接收器时间戳
unsigned long ultrasonic_controller::getRightTime() 
{
    return rightTime;
}

// 手动重置检测标志
void ultrasonic_controller::reset() 
{
    leftDetected = false;
    rightDetected = false;
}