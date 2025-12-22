#include "main_controller.h"

main_controller::main_controller()
{
    pid = new pid_controller();
    motor = new motor_controller();
    ultrasonic = new ultrasonic_controller();

    dir_d = PID_DESIRED_DATA;
    dir_t = 0.0f;
    dir_output = 0.0f;

    lastSignalTime = 0;
    state = SEARCHING;
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
    unsigned long now = millis();

    if (ultrasonic->available())
    {
        
    }
    else
    {
        
    }

    return true;
}
