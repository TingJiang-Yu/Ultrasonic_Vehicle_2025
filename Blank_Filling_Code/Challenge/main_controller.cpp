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
    /*======= Your Code =======*/

    /*======= Your Code =======*/

    return true;
}

bool main_controller::update()
{
    unsigned long now = millis();

    if (ultrasonic->available())
    {
        /*======= Your Code =======*/

        /*======= Your Code =======*/
    }
    else
    {
        /*======= Your Code =======*/

        /*======= Your Code =======*/
    }

    return true;
}
