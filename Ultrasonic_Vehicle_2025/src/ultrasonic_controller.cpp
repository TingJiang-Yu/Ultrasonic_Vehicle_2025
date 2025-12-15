#include "ultrasonic_controller.h"
#include "config.h"

template<class elemType>
void swap(elemType& a, elemType& b)
{
    elemType temp = a;
    a = b;
    b = temp;
}

ultrasonic_controller ultrasonic;

void ultrasonic_controller::init() {
    // 初始化ADC引脚
    pinMode(ADC_LEFT_PIN, INPUT);
    pinMode(ADC_RIGHT_PIN, INPUT);
    
    // 初始化变量
    historyIndex = 0;
    leftSignalCurrent = 0;
    rightSignalCurrent = 0;
    lastSampleTime = 0;
    ambientNoiseLevel = 0;
    maxSignalLevel = 0;
    
    // 初始化历史缓冲区
    for (int i = 0; i < ADC_HISTORY_SIZE; i++) 
    {
        leftSignalHistory[i] = 0;
        rightSignalHistory[i] = 0;
    }
    
    // 校准环境噪声
    calibrateNoiseFloor();
}

void ultrasonic_controller::startMeasurement() 
{
    // 重置最大值记录
    maxSignalLevel = ambientNoiseLevel;
}

void ultrasonic_controller::updateADC() 
{
    uint32_t currentTime = millis();
    
    // 每10ms采样一次
    if (currentTime - lastSampleTime >= 10) 
    {
        lastSampleTime = currentTime;
        
        // 读取并处理ADC值
        uint16_t leftRaw = readAndProcessADC(ADC_LEFT_PIN);
        uint16_t rightRaw = readAndProcessADC(ADC_RIGHT_PIN);
        
        // 应用移动平均滤波
        leftSignalCurrent = movingAverage(leftSignalHistory, leftRaw);
        rightSignalCurrent = movingAverage(rightSignalHistory + ADC_HISTORY_SIZE, rightRaw);
        
        // 更新最大值（用于校准）
        if (leftSignalCurrent > maxSignalLevel) {
            maxSignalLevel = leftSignalCurrent;
        }
        if (rightSignalCurrent > maxSignalLevel) {
            maxSignalLevel = rightSignalCurrent;
        }
        
        historyIndex = (historyIndex + 1) % ADC_HISTORY_SIZE;
    }
}

uint16_t ultrasonic_controller::getLeftSignalStrength() 
{
    return leftSignalCurrent;
}

uint16_t ultrasonic_controller::getRightSignalStrength() 
{
    return rightSignalCurrent;
}

float ultrasonic_controller::getDirectionBias() 
{
    if (!hasValidSignal()) return 0.0;
    
    // 计算左右信号强度差
    int16_t diff = (int16_t)leftSignalCurrent - (int16_t)rightSignalCurrent;
    uint16_t sum = leftSignalCurrent + rightSignalCurrent;
    
    if (sum == 0) return 0.0;
    
    // 归一化到 -1.0 到 1.0
    float bias = (float)diff / sum;
    
    // 应用死区和滤波
    if (fabs(bias) < 0.1) bias = 0.0;
    
    return bias;
}

bool ultrasonic_controller::hasValidSignal() {
    uint16_t avgSignal = (leftSignalCurrent + rightSignalCurrent) / 2;
    
    // 信号必须高于噪声水平一定阈值
    return (avgSignal > ambientNoiseLevel + 50) && 
           (avgSignal < 4000);  // 防止ADC饱和
}

// =============== 私有方法 ===============

void ultrasonic_controller::calibrateNoiseFloor() 
{
    // 采集多个样本计算平均值
    const int calibrationSamples = 100;
    uint32_t leftSum = 0;
    uint32_t rightSum = 0;
    
    for (int i = 0; i < calibrationSamples; i++) 
    {
        leftSum += analogRead(ADC_LEFT_PIN);
        rightSum += analogRead(ADC_RIGHT_PIN);
        delay(1);
    }
    
    ambientNoiseLevel = (leftSum + rightSum) / (2 * calibrationSamples);
}

uint16_t ultrasonic_controller::readAndProcessADC(uint8_t pin) 
{
    // 读取原始ADC值
    uint16_t rawValue = analogRead(pin);
    
    // 简单的中值滤波（读取3次取中间值）
    uint16_t values[3];
    for (int i = 0; i < 3; i++) 
    {
        values[i] = analogRead(pin);
        delayMicroseconds(100);
    }
    
    // 排序取中值
    if (values[0] > values[1]) swap(values[0], values[1]);
    if (values[1] > values[2]) swap(values[1], values[2]);
    if (values[0] > values[1]) swap(values[0], values[1]);
    
    return values[1];
}

float ultrasonic_controller::calculateDirectionFromStereo(uint16_t left, uint16_t right) 
{
    // 简单的强度比方法
    if (left + right == 0) return 0.0;
    
    float ratio = (float)(left - right) / (left + right);
    
    // 应用非线性映射增强小角度灵敏度
    if (ratio > 0) ratio = pow(ratio, 0.7);
    else ratio = -pow(-ratio, 0.7);
    
    return constrain(ratio, -1.0, 1.0);
}

uint16_t ultrasonic_controller::movingAverage(uint16_t* buffer, uint16_t newValue) 
{
    // 更新缓冲区
    buffer[historyIndex] = newValue;
    
    // 计算移动平均值
    uint32_t sum = 0;
    for (int i = 0; i < ADC_HISTORY_SIZE; i++) sum += buffer[i];
    
    return sum / ADC_HISTORY_SIZE;
}