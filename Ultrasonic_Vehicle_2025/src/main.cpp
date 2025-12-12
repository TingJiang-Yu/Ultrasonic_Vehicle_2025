#include "motor_controller.h"
#include "pid_controller.h"

MotorController motor;

void setup() 
{
    motor.init();
    Serial.begin(115200);
}

void loop() 
{
    motor.setLeftSpeed(250);
    motor.setRightSpeed(250);
    delay(3000);
    motor.setLeftSpeed(-250);
    motor.setRightSpeed(-250);
    delay(3000);
    // 空闲
}
