#ifndef ULTRASONIC_TIME_DIFF_H
#define ULTRASONIC_TIME_DIFF_H

#include <Arduino.h>
#include "config.h"

class ultrasonic_controller {
private:
    // 引脚定义
    uint8_t leftPin;
    uint8_t rightPin;
    
    // 时间变量
    volatile unsigned long leftTime;
    volatile unsigned long rightTime;
    volatile bool leftDetected;
    volatile bool rightDetected;
    
    // 防抖时间
    volatile unsigned long lastLeftTime;
    volatile unsigned long lastRightTime;
    unsigned long debounceTime;
    
    // 中断服务函数（声明为静态，但通过实例指针访问）
    static void leftISR();
    static void rightISR();
    
    static ultrasonic_controller* instance;

public:
    ultrasonic_controller();
    
    void init();
    
    bool available();
    
    // 获取时间差（微秒），正数表示左边先收到，负数表示右边先收到
    long getTimeDiff();
    
    // 获取原始时间戳（微秒）
    unsigned long getLeftTime();
    unsigned long getRightTime();
    
    // 手动重置检测标志
    void reset();
};

#endif