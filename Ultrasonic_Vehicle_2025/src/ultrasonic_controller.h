#ifndef ULTRASONIC_CONTROLLER_H
#define ULTRASONIC_CONTROLLER_H

#include <Arduino.h>
#include "config.h"

class ultrasonic_controller {
private:
    // ADC采样相关
    static const int SAMPLE_WINDOW = 100;  // 采样窗口大小 (ms)
    static const int ADC_HISTORY_SIZE = 20; // 历史数据缓冲区大小
    
    // 信号处理
    uint16_t leftSignalHistory[ADC_HISTORY_SIZE];
    uint16_t rightSignalHistory[ADC_HISTORY_SIZE];
    int historyIndex;
    
    // 当前值
    uint16_t leftSignalCurrent;
    uint16_t rightSignalCurrent;
    uint32_t lastSampleTime;
    
    // 校准参数
    uint16_t ambientNoiseLevel;  // 环境噪声水平
    uint16_t maxSignalLevel;     // 最大信号水平
    
    // 私有方法
    void calibrateNoiseFloor();
    uint16_t readAndProcessADC(uint8_t pin);
    float calculateDirectionFromStereo(uint16_t left, uint16_t right);
    
    // 移动平均滤波
    uint16_t movingAverage(uint16_t* buffer, uint16_t newValue);

public:
    // 初始化超声波控制器
    void init();
    
    // 开始测量
    void startMeasurement();
    
    // 更新ADC采样值（需要在主循环中调用或通过中断）
    void updateADC();
    
    // 获取左侧超声波信号强度 (0-4095)
    uint16_t getLeftSignalStrength();
    
    // 获取右侧超声波信号强度 (0-4095)
    uint16_t getRightSignalStrength();
    
    // 获取方向偏移 (-1.0 到 1.0，负值表示左偏，正值表示右偏)
    float getDirectionBias();
    
    // 检查是否有有效信号
    bool hasValidSignal();
};

// 全局实例
extern ultrasonic_controller ultrasonic;

#endif // ULTRASONIC_CONTROLLER_H