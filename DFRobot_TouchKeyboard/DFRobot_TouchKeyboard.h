/*!
 * @file DFRobot_TouchKeyboard.h
 * @brief 定义DFRobot_Sensor 类的基础结构
 * @n 这是一个虚拟的传感器，IIC地址不可改变,不对应任何实物，可以通过IIC和SPI口来控制它，假设它有下面这些功能
 * @n 向寄存器0里写入数据，点亮不同颜色的LED灯
 * @n 从寄存器1里读出数据，高四位表示光线强度，低四位表示声音强度
 * @n 从寄存器2 bit0里写入数据，写1表示正常模式，写0表示低功耗模式
 * @n 从寄存器3 读取数据，读到的是芯片版本0xDF
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */

#ifndef __DFRobot_TouchKeyboard_H__
#define __DFRobot_TouchKeyboard_H__

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define TOUCH_KEY_NONE 255

///查错系统
//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

class DFRobot_TouchKeyboard
{
public:
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
   /*
   这是键盘索引值和按键对应关系表
     * -----------------------------------------------------
     * |键盘值 |    1    |    2    |    3    |    A    | 
     * -----------------------------------------------------
	 * |索引值 |    0    |    1    |    2    |    3    | 
     * -----------------------------------------------------
	 
	 * -----------------------------------------------------
     * |键盘值 |    4    |    5    |    6    |    B    | 
     * -----------------------------------------------------
	 * |索引值 |    4    |    5    |    6    |    7    | 
     * -----------------------------------------------------
     
     * -----------------------------------------------------
     * |键盘值 |    7    |    8    |    9    |    C    | 
     * -----------------------------------------------------
	 * |索引值 |    8    |    9    |    10   |    11   | 
     * -----------------------------------------------------
	 
	 * -----------------------------------------------------
     * |键盘值 |    *    |    0    |    #    |    D   | 
     * -----------------------------------------------------
	 * |索引值 |    12   |    13   |    14   |    15  | 
     * -----------------------------------------------------
   */
	 uint8_t getIndex(void);
	 
	  /**
   * @brief 获取按键值（即按键所代表的值）函数
   * @n 根据索引值查表可得
   * @return 无返回值
   */
	uint8_t getKeyValue(void);
private:

	 /**
   * @brief 获取按键原始值函数
   * @n 通过不同按键按下触发通电，每一个按键对应唯一的原始值
   * @return 返回值为按键原始值
   */
	uint8_t getValueRaw(void);

private:
	
	///定义数据表，不同的引脚插线方式对应数据是一样的，差别不过是顺序而已
	///{，，，}三位分别代表“按键对应的符原始值”，“按键对应的值”，“每一个按键的索引值”
	//static const uint8_t _kvmap[16][3];
	
	///定义键盘默认的引脚值，依次为1号到8号线的引脚（在接头上有标记1和8，由此依次决定序号）
	uint8_t _PA0;
	uint8_t _PA1;
	uint8_t _PA2;
	uint8_t _PA3;
	uint8_t _PB0;
	uint8_t _PB1;
	uint8_t _PB2; 
	uint8_t _PB3;
	
	///定义时间戳，用来记录上一次按键按下时间
	uint64_t _timestamp;
	
	///定义interval为两次按键相距的时间间隙
    uint32_t _interval;
 };
 #endif