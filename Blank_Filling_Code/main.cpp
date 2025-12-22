#include <Arduino.h>
#include "main_controller.h"

main_controller ctrl;
ultrasonic_controller usc;

void setup() 
{
    Serial.begin(SERIAL_BAUDRATE);
    ctrl.init();
}

void loop() 
{
    ctrl.update();
}
