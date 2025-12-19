// MotorController.h - ESP32版本
#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include "config.h"

class motor_controller {
private:
    // 电机引脚
    int leftAPin, leftBPin;
    int rightAPin, rightBPin;
    
    // 当前状态
    int currentLeftSpeed;
    int currentRightSpeed;
    bool leftDirection;  // true=前进, false=后退
    bool rightDirection;

public:
    motor_controller();
    void init();
    void setSpeed(int leftSpeed, int rightSpeed);
    void setSpeed(int speed);
    void stop();
    
private:
    // 速度控制
    void setLeftSpeed(int speed);  // -255 to 255
    void setRightSpeed(int speed); // -255 to 255

    // 限制速度范围
    int constrainSpeed(int speed);
    
    void brakeAllMotors();
};

#endif