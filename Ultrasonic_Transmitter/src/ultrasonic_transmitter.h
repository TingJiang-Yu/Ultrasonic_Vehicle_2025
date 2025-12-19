// ultrasonic_transmitter.h
#ifndef ULTRASONIC_TRANSMITTER_H
#define ULTRASONIC_TRANSMITTER_H

#define ULTRASONIC_TX_PIN 25  // 定义发射引脚

#include <stdint.h>

class Ultrasonic_Transmitter
{
private:
    uint8_t tx_pin;  // 发射引脚存储变量
public:
    Ultrasonic_Transmitter();                  // 构造函数
    void begin();                              // 初始化函数
    void transmit(uint8_t cycles = 8);         // 发射信号函数, 可指定周期数
};

#endif