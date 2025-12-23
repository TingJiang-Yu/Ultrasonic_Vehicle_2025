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
    /*======= Your Code =======*/

    /*======= Your Code =======*/

    // B 端在硬件上已拉高
    stop();
}

void motor_controller::setTurn(int turn)
{
    // turn 是“速度差分量”，不做反相
    turnSpeed = constrain(turn, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);
    applyOutput();
}

void motor_controller::applyOutput()
{
    unsigned long now = millis();
    if (now - lastPwmUpdate < PWM_UPDATE_INTERVAL_MS) return;
    lastPwmUpdate = now;

    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void motor_controller::search(int speed)
{
    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void motor_controller::driveMotor(int pin, int speed)
{
    /*======= Your Code =======*/

    /*======= Your Code =======*/
}

void motor_controller::stop()
{
    /*======= Your Code =======*/

    /*======= Your Code =======*/
}
