#include <Arduino.h>
#include "driver/mcpwm.h"

// 要实现的功能：0.4s生成方波，0.4s沉默

void setup() 
{
    Serial.begin(115200);
    
    // 配置MCPWM
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 4);  // 引脚4作为PWM输出
    
    mcpwm_config_t pwm_config = 
    {
        .frequency = 40000,      // 40kHz方波
        .cmpr_a = 50.0,         // 50%占空比
        .cmpr_b = 50.0,
        .duty_mode = MCPWM_DUTY_MODE_0,
        .counter_mode = MCPWM_UP_COUNTER,
    };
    
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void loop() 
{
    delay(1000);
}
