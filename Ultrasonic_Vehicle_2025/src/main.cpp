#include <Arduino.h>
#include "main_controller.h"

main_controller ctrl;
motor_controller motor_test;

void setup() 
{
    Serial.begin(SERIAL_BAUDRATE);
    motor_test.init();
    // ctrl.init();
}

void loop() 
{
    motor_test.setTurn(30);
    // ctrl.update();
}
