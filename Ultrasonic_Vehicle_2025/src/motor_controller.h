// MotorController.h - ESP32版本
#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include <driver/ledc.h>  // ESP32 LEDC PWM库
#include "config.h"

class MotorController {
private:
    // 电机引脚
    int leftAPin, leftBPin;
    int rightAPin, rightBPin;
    
    // PWM通道
    int leftAChannel, leftBChannel;
    int rightAChannel, rightBChannel;
    
    // 当前状态
    int currentLeftSpeed;
    int currentRightSpeed;
    bool leftDirection;  // true=前进, false=后退
    bool rightDirection;
    
    // PWM配置
    int pwmFrequency;
    int pwmResolution;
    
public:
    // 构造函数
    MotorController();
    
    // 初始化电机
    void init();

    void stop();
    
    // 速度控制
    void setLeftSpeed(int speed);  // -255 to 255
    void setRightSpeed(int speed); // -255 to 255
    
private:
    // 限制速度范围
    int constrainSpeed(int speed);
    
    // 设置单个PWM输出
    void setPWMOutput(int channel, int duty);
    
    void brakeAllMotors();
};

#endif