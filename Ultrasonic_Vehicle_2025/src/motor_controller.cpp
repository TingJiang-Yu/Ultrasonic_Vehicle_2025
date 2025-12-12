#include "motor_controller.h"

MotorController::MotorController() 
    : leftAPin(MOTOR_LEFT_A_PIN), 
      leftBPin(MOTOR_LEFT_B_PIN),
      rightAPin(MOTOR_RIGHT_A_PIN), 
      rightBPin(MOTOR_RIGHT_B_PIN),
      currentLeftSpeed(0), 
      currentRightSpeed(0),
      leftDirection(true),
      rightDirection(true),
      pwmFrequency(PWM_FREQUENCY),
      pwmResolution(PWM_RESOLUTION) 
      {}

// ================= 初始化函数 =================
void MotorController::init() 
{   
    // 设置引脚模式
    pinMode(leftAPin, OUTPUT);
    pinMode(leftBPin, OUTPUT);
    pinMode(rightAPin, OUTPUT);
    pinMode(rightBPin, OUTPUT);
    
    // 初始化PWM为0
    analogWrite(leftAPin, 0);
    analogWrite(leftBPin, 0);
    analogWrite(rightAPin, 0);
    analogWrite(rightBPin, 0);

    // 初始停止
    stop();
}

int MotorController::constrainSpeed(int speed) 
{
    if (speed > MAX_SPEED) return MAX_SPEED;
    if (speed < MIN_SPEED) return MIN_SPEED;
    return speed;
}

void MotorController::stop() {
    brakeAllMotors();
    currentLeftSpeed = 0;
    currentRightSpeed = 0;
}

// ================= 独立控制 =================

void MotorController::setLeftSpeed(int speed) {
    speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
    
    if (speed > 0) {
        // 前进
        analogWrite(leftAPin, speed);
        analogWrite(leftBPin, 0);
        leftDirection = true;
        currentLeftSpeed = speed;
    } else if (speed < 0) {
        // 后退
        analogWrite(leftAPin, 0);
        analogWrite(leftBPin, -speed);
        leftDirection = false;
        currentLeftSpeed = speed;
    } else {
        // 停止
        analogWrite(leftAPin, 0);
        analogWrite(leftBPin, 0);
        currentLeftSpeed = 0;
    }
}

void MotorController::setRightSpeed(int speed) {
    speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
    
    if (speed > 0) {
        // 前进
        analogWrite(rightAPin, speed);
        analogWrite(rightBPin, 0);
        rightDirection = true;
        currentRightSpeed = speed;
    } else if (speed < 0) {
        // 后退
        analogWrite(rightAPin, 0);
        analogWrite(rightBPin, -speed);
        rightDirection = false;
        currentRightSpeed = speed;
    } else {
        // 停止
        analogWrite(rightAPin, 0);
        analogWrite(rightBPin, 0);
        currentRightSpeed = 0;
    }
}

void MotorController::brakeAllMotors() {
    analogWrite(leftAPin, MAX_SPEED);
    analogWrite(leftBPin, MAX_SPEED);
    analogWrite(rightAPin, MAX_SPEED);
    analogWrite(rightBPin, MAX_SPEED);
    delay(50);
    analogWrite(leftAPin, 0);
    analogWrite(leftBPin, 0);
    analogWrite(rightAPin, 0);
    analogWrite(rightBPin, 0);
}
