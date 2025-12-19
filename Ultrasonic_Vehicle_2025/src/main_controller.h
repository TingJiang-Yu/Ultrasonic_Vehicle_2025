#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_

#include<Arduino.h>
#include "pid_controller.h"
#include "motor_controller.h"
#include "ultrasonic_controller.h"

class main_controller 
{
private:
    pid_controller* pid;
    motor_controller* motor;
    ultrasonic_controller* ultrasonic;

    float dir_d; // 声源方向的期望位置
    float dir_t; // 声源方向的当前位置
    float dir_output; // PID输出值
    
public:
    main_controller();
    bool init();
    bool update();
};

#endif // MAIN_CONTROLLER_H_