#include "motor_controller.h"

motor_controller::motor_controller() 
    : leftAPin(MOTOR_LEFT_A_PIN), 
      leftBPin(MOTOR_LEFT_B_PIN),
      rightAPin(MOTOR_RIGHT_A_PIN), 
      rightBPin(MOTOR_RIGHT_B_PIN),
      currentLeftSpeed(0), 
      currentRightSpeed(0),
      leftDirection(true),
      rightDirection(true)
      {}

void motor_controller::init() 
{   
    pinMode(leftAPin, OUTPUT);
    pinMode(leftBPin, OUTPUT);
    pinMode(rightAPin, OUTPUT);
    pinMode(rightBPin, OUTPUT);
    
    analogWrite(leftAPin, 0);
    analogWrite(leftBPin, 0);
    analogWrite(rightAPin, 0);
    analogWrite(rightBPin, 0);

    stop();
}

void motor_controller::setSpeed(int leftSpeed, int rightSpeed) 
{
    setLeftSpeed(leftSpeed);
    currentLeftSpeed += BASE_SPEED;
    setRightSpeed(rightSpeed);
    currentRightSpeed += BASE_SPEED;
}

void motor_controller::setSpeed(int speed) 
{
    if (speed > 0) {
        setLeftSpeed(speed);
        setRightSpeed(-speed);
    } else if (speed < 0) {
        setLeftSpeed(-speed);
        setRightSpeed(speed);
    } else {
        stop();
        return;
    }
    currentLeftSpeed += BASE_SPEED;
    currentRightSpeed += BASE_SPEED;
}

void motor_controller::stop() {
    brakeAllMotors();
    currentLeftSpeed = 0;
    currentRightSpeed = 0;
}

void motor_controller::setLeftSpeed(int speed) {
    speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
    
    if (speed > 0) {
        leftDirection = true;
        currentLeftSpeed = speed;
    } else if (speed < 0) {
        leftDirection = false;
        currentLeftSpeed = speed;
    } else {
        currentLeftSpeed = 0;
    }
}

void motor_controller::setRightSpeed(int speed) {
    speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
    
    if (speed > 0) {
        rightDirection = true;
        currentRightSpeed = speed;
    } else if (speed < 0) {
        rightDirection = false;
        currentRightSpeed = speed;
    } else {
        currentRightSpeed = 0;
    }
}

int motor_controller::constrainSpeed(int speed) 
{
    if (speed > MAX_SPEED) return MAX_SPEED;
    if (speed < MIN_SPEED) return MIN_SPEED;
    return speed;
}

void motor_controller::brakeAllMotors() {
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
