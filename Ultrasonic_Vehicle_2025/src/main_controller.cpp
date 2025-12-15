#include "main_controller.h"

main_controller::main_controller() 
    : currentState(STATE_SEARCH),
      lastStateChangeTime(0),
      targetDistance(FOLLOW_TARGET_DISTANCE) 
    {}

// ================= 初始化 =================
void main_controller::init() 
{
    Serial.begin(SERIAL_BAUDRATE);
    
    // 初始化子系统
    sonic.init();
    motor.init();
    sonic.startMeasurement();
    
    currentState = STATE_SEARCH;
    lastStateChangeTime = millis();
}

// ================= 主控制循环 =================
void main_controller::update() 
{
    // 更新超声波传感器数据
    sonic.updateADC();
    
    // 根据状态执行相应控制
    switch (currentState) 
    {
    case STATE_SEARCH:
        handleSearchState();
        break;
        
    case STATE_FOLLOW:
        handleFollowState();
        break;
        
    case STATE_STOP:
        handleStopState();
        break;
    }
}

// ================= 搜索状态 =================
void main_controller::handleSearchState() 
{
    // 检查是否有信号
    if (sonic.hasValidSignal()) 
    {
        setState(STATE_FOLLOW);
        return;
    }
    
    // 没有信号，原地旋转搜索
    searchRotation();
    
    // 每2秒输出一次搜索状态
    static uint32_t lastPrintTime = 0;
    uint32_t now = millis();
    if (now - lastPrintTime > 2000) lastPrintTime = now;
}

// ================= 跟随状态 =================
void main_controller::handleFollowState() 
{
    // 检查信号是否丢失
    if (!sonic.hasValidSignal()) 
    {
        setState(STATE_SEARCH);
        return;
    }
    
    // 获取方向偏差
    float directionBias = sonic.getDirectionBias();
    
    // 简单的跟随控制算法
    int baseSpeed = BASE_SPEED;
    int leftSpeed = baseSpeed;
    int rightSpeed = baseSpeed;
    
    // 根据方向偏差调整左右轮速度
    if (fabs(directionBias) > 0.1) 
    {
        // 有显著偏差，需要转向
        float turnFactor = 100.0 * directionBias;
        leftSpeed -= turnFactor;
        rightSpeed += turnFactor;
        
        // 限制速度范围
        leftSpeed = constrain(leftSpeed, -MAX_SPEED, MAX_SPEED);
        rightSpeed = constrain(rightSpeed, -MAX_SPEED, MAX_SPEED);
    }
    
    // 执行移动
    moveCar(leftSpeed, rightSpeed);
}

// ================= 停止状态 =================
void main_controller::handleStopState() 
{
    motor.stop();
}

// ================= 状态切换 =================
void main_controller::setState(ControlState newState) 
{
    if (currentState == newState) return;
    
    // 退出当前状态的处理
    switch (currentState) 
    {
    case STATE_SEARCH:
        motor.stop();
        break;
    case STATE_FOLLOW:
        motor.stop();
        break;
    case STATE_STOP:
        break;
    }
    
    // 更新状态
    currentState = newState;
    lastStateChangeTime = millis();
}

// ================= 搜索旋转 =================
void main_controller::searchRotation() 
{
    // 简单的左右交替旋转搜索
    static bool rotateRight = true;
    static uint32_t lastRotateTime = 0;
    uint32_t now = millis();
    
    if (now - lastRotateTime > 1000) 
    {
        // 每1秒切换旋转方向
        rotateRight = !rotateRight;
        lastRotateTime = now;
    }
    
    // 执行旋转
    if (rotateRight) 
    {
        // 右转
        motor.setLeftSpeed(BASE_SPEED / 2);
        motor.setRightSpeed(-BASE_SPEED / 2);
    } 
    else 
    {
        // 左转
        motor.setLeftSpeed(-BASE_SPEED / 2);
        motor.setRightSpeed(BASE_SPEED / 2);
    }
}

// ================= 移动控制 =================
void main_controller::moveCar(int leftSpeed, int rightSpeed) 
{
    // 直接设置电机速度
    motor.setLeftSpeed(leftSpeed);
    motor.setRightSpeed(rightSpeed);
}