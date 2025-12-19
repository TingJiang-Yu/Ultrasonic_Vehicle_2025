// ultrasonic_transmitter.cpp
#include "ultrasonic_transmitter.h"
#include <Arduino.h>

// 默认频率与周期计算
constexpr unsigned long ULTRASONIC_FREQ_HZ = 40000UL;
constexpr unsigned long ULTRASONIC_PERIOD_US = 1000000UL / ULTRASONIC_FREQ_HZ; // 25
constexpr unsigned int ULTRASONIC_HALF_US = ULTRASONIC_PERIOD_US / 2;            // 12
constexpr unsigned int ULTRASONIC_REST_US = ULTRASONIC_PERIOD_US - ULTRASONIC_HALF_US; // 13

Ultrasonic_Transmitter::Ultrasonic_Transmitter() : tx_pin(ULTRASONIC_TX_PIN)
{
}

void Ultrasonic_Transmitter::begin()
{
    pinMode(tx_pin, OUTPUT);   // 设置发射引脚为输出模式
    digitalWrite(tx_pin, LOW); // 初始化为低电平
}

void Ultrasonic_Transmitter::transmit(uint8_t cycles)
{
    // 产生40kHz超声波信号（大多数超声波模块的标准频率）
    // 一个周期为 ~25 微秒（1/40000 秒），高低电平分别取 ULTRASONIC_HALF_US 和 ULTRASONIC_REST_US
    for (uint8_t i = 0; i < cycles; ++i)
    {
        digitalWrite(tx_pin, HIGH);
        delayMicroseconds(ULTRASONIC_HALF_US);
        digitalWrite(tx_pin, LOW);
        delayMicroseconds(ULTRASONIC_REST_US);
    }
}

// 注意：software delayMicroseconds 的精度受中断和函数开销影响；
// 如需更稳定的40kHz信号，建议使用硬件定时器或 `tone()`/PWM 输出并对其进行门控。