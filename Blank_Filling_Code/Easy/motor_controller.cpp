#include "motor_controller.h"

motor_controller::motor_controller()
    : leftPin(MOTOR_LEFT_PIN),
      rightPin(MOTOR_RIGHT_PIN),
      baseSpeed(MOTOR_BASE_SPEED),
      turnSpeed(0),
      lastPwmUpdate(0)
{}

void motor_controller::init()
{
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);

    stop();
}

void motor_controller::setTurn(int turn)
{
    turnSpeed = constrain(turn, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);
    applyOutput();
}

void motor_controller::applyOutput()
{
    unsigned long now = millis();
    if (now - lastPwmUpdate < PWM_UPDATE_INTERVAL_MS) return;
    lastPwmUpdate = now;

    int leftSpeed  = baseSpeed + turnSpeed;
    int rightSpeed = baseSpeed - turnSpeed;

    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void motor_controller::search(int speed)
{
    unsigned long now = millis();
    if (now - lastPwmUpdate < PWM_UPDATE_INTERVAL_MS) return;
    lastPwmUpdate = now;
    
    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void motor_controller::driveMotor(int pin, int speed)
{
    // speed: 0 ~ MAX_SPEED
    speed = constrain(speed, 0, MOTOR_MAX_SPEED);

    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void motor_controller::stop()
{
    analogWrite(leftPin,  MOTOR_MAX_SPEED);
    analogWrite(rightPin, MOTOR_MAX_SPEED);
}
