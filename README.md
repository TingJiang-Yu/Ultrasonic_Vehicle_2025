# 超声波跟随小车2025

## 使用方法：

打开`Ultrasonic_Vehicle_2025`文件夹，打开`src`文件夹，可以看到所有的文件

目前搭建了一个基础的框架，但还要根据实际情况更改

大体的思路：
- `main_controller`作为上层控制，直接调用底层库函数，采集底层的信息，处理信息并产生命令，有点类似于`int main()`函数
  - `motor_controller`作为电机控制板底层，负责驱动电机（如果有现成的库，就不用这个了）
  - `pid_controller`作为$PID$算法库，如果需要就用
  - `ultrasonic_controller`作为超声波模块底层，负责驱动超声波模块

