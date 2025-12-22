#include <Arduino.h>
#include "main_controller.h"

main_controller ctrl;
ultrasonic_controller usc;

void setup() 
{
    Serial.begin(SERIAL_BAUDRATE);
    usc.init();
    // ctrl.init();
}

void loop() 
{
    long timeDiff = usc.getTimeDiff();
    Serial.print("Left Time: ");
    Serial.print(usc.getLeftTime());
    Serial.print(" Right Time: ");
    Serial.print(usc.getRightTime());
    Serial.print("Time diff: ");
    Serial.println(timeDiff);
    delay(500);
    // ctrl.update();
}
