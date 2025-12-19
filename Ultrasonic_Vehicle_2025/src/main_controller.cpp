#include "main_controller.h"

main_controller::main_controller() 
{
    pid = new pid_controller();
    dir_d = PID_DESIRED_DATA;
    dir_t = 0.0f;
    dir_output = 0.0f;

    motor = new motor_controller();
    ultrasonic = new ultrasonic_controller();
}

bool main_controller::init() 
{
    motor->init();

    ultrasonic->init();

    pid->init(&dir_d, &dir_output);
    pid->SetK(PID_KP, PID_KI, PID_KD);
    pid->SetL(PID_MAX_INTEGRAL, PID_MIN_OUTPUT, PID_MAX_OUTPUT);

    return true;
}

bool main_controller::update() 
{
    if (ultrasonic->available()) 
    {
        long timeDiff = ultrasonic->getTimeDiff();
        dir_t = (float)timeDiff;
        pid->Calc(dir_t);
        motor->setSpeed(dir_output);
    }
    return true;
}