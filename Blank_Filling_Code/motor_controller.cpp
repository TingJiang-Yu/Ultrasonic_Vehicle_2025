#include "motor_controller.h"

motor_controller::motor_controller()
    : leftPin(MOTOR_LEFT_PIN),
      rightPin(MOTOR_RIGHT_PIN),
      baseSpeed(BASE_SPEED),
      turnSpeed(0),
      lastPwmUpdate(0)
{}

void motor_controller::init()
{
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);

    // B 端在硬件上已拉高
    stop();
}

void motor_controller::setTurn(int turn)
{
    // turn 是“速度差分量”，不做反相
    turnSpeed = constrain(turn, -MAX_SPEED, MAX_SPEED);
    applyOutput();
}

void motor_controller::applyOutput()
{
    unsigned long now = millis();
    if (now - lastPwmUpdate < PWM_UPDATE_INTERVAL_MS) return;
    lastPwmUpdate = now;
    
}

void motor_controller::search(int speed)
{
    unsigned long now = millis();
    if (now - lastPwmUpdate < PWM_UPDATE_INTERVAL_MS) return;
    lastPwmUpdate = now;

    speed = constrain(speed, 0, MAX_SPEED);
}

void motor_controller::driveMotor(int pin, int speed)
{
    
}

void motor_controller::stop()
{
    
}
