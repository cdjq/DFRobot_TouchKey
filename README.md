# DFRobot_TouchKeyboard
数据手册上抄一下芯片的描述

该键盘带有8P杜邦头，间距2.54mm。可插上排针，然后连接到Arduino，使用非常简单。键盘背面白色贴纸可揭
去，能牢固粘贴于机箱表面。你可以用它输入数字参数等信息，特别是对于LCD模块，GSM/GPRS模块等需要参数
输入的模块。薄膜防水耐用，可经受几万次按压。

![正反面svg效果图](https://github.com/cdjq/DFRobot_TouchKeyboard/blob/master/resources/images/TouchKeyboardsvg1.png)

## 产品链接    www.dfrobot.com
    SKU：薄膜数字键盘
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

1、读取按键的值并显示

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
DFRobot_TouchKeyboard();
   /**
   * @brief 初始化函数
   * @n 引脚为默认值
   * @param interval含义为执行两次begin函数之间需要的时间间隙
   * @return 无返回值
   */
   uint8_t begin(uint32_t interval);
 
   /**
   * @brief 初始化函数
   * @n 对引脚值进行了修改
   * @param interval含义为执行两次begin函数之间需要的时间间隙
   * @param userPA0到PB3依次为参数类型
   * @return 无返回值
   */
    uint8_t begin(uint32_t interval,
	        uint8_t userPA0,uint8_t userPA1,uint8_t userPA2,uint8_t userPA3,
	        uint8_t userPB0,uint8_t userPB1,uint8_t userPB2,uint8_t userPB3);

   /**
   * @brief 设置高低电平以定位按键位置
   * @return 无返回值
   */
   uint8_t groupALow(void);
	
   /**
   * @brief 设置高低电平以定位按键位置
   * @return 无返回值
   */
   uint8_t groupBLow(void);
	 
  /**
   * @brief 获取索引值函数
   * @n 根据原始值查表可得
   * @return 返回值为按键索引值
   */
   uint8_t getIndex(void);
	 
   /**
   * @brief 获取按键值（即按键所代表的值）函数
   * @n 根据索引值查表可得
   * @return 无返回值
   */
   uint8_t getKeyValue(void);
   
  /**
   * @brief 获取按键原始值函数
   * @n 通过不同按键按下触发通电，每一个按键对应唯一的原始值
   * @return 返回值为按键原始值
   */
    uint8_t getValueRaw(void);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |       ×      |              |             | 
mPython/ESP32      |      √       |              |             | 
micro:bit          |      ×       |              |             | 


## History
- data 2019-8-9


## Credits

Written by John(yzm19971997@gmail.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





