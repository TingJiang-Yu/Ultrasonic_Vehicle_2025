#include <Arduino.h>
#include "main_controller.h"

main_controller ctrl;

void setup() 
{
    Serial.begin(115200);
    ctrl.init();
}

void loop() 
{
    ctrl.update();
}
