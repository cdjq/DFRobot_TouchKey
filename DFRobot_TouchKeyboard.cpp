/*!
 * @file DFRobot_TouchKeyboard.cpp
 * @brief 定义键盘类的基础结构，基础方法的实现
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [John](yzm19971997@gmail.com)
 * @version  V1.0
 * @date  2019-08-19
 * @https://github.com/cdjq/DFRobot_TouchKeyboard
 */

#include <DFRobot_TouchKeyboard.h>
#include <string.h>

 static const uint8_t _kvmap[16][3]={{119,1,0},{183,2,1},{215,3,2},{231,'A',11},
								 {123,4,3},{187,5,4},{219,6,5},{235,'B',12},
								 {125,7,6},{189,8,7},{221,9,8},{237,'C',13},
								 {126,'*',10},{190,0,9},{222,'#',14},{238,'D',15}};

DFRobot_TouchKeyboard::DFRobot_TouchKeyboard()
#ifdef ARDUINO_ARCH_AVR
	:_PA0(12),_PA1(11),_PA2(10),_PA3(9),_PB0(8),_PB1(7),_PB2(6),_PB3(5)
#elif defined (ESP_PLATFORM)
	:_PA0(P12),_PA1(P11),_PA2(P10),_PA3(P9),_PB0(P8),_PB1(P7),_PB2(P6),_PB3(P5)
#else
	:_PA0(12),_PA1(11),_PA2(10),_PA3(9),_PB0(8),_PB1(7),_PB2(6),_PB3(5)
#endif	
{

}

///实现默认初始化函数，引脚采用默认值，可根据高低电平得到每一个按键的原始值
uint8_t DFRobot_TouchKeyboard::begin(uint32_t interval)
{
	groupBLow();
	groupALow();
	_interval=interval;
	_timestamp = millis();
	return 0;
}

///实现初始化函数，引脚采用自定义值，可根据高低电平得到每一个按键的代码值
uint8_t DFRobot_TouchKeyboard::begin(uint32_t interval,
		uint8_t userPA0,uint8_t userPA1,uint8_t userPA2,uint8_t userPA3,
		uint8_t userPB0,uint8_t userPB1,uint8_t userPB2,uint8_t userPB3)
{
	_PA0 = userPA0;
	_PA1 = userPA1;
	_PA2 = userPA2;
	_PA3 = userPA3;
	_PB0 = userPB0;
	_PB1 = userPB1;
	_PB2 = userPB2;
	_PB3 = userPB3;
	return begin(interval);
}

///将其中四个引脚设为上拉电平，另外四个为低电平
///读取单个引脚为上拉电阻的代码值，以四位的方式存储
uint8_t DFRobot_TouchKeyboard::groupBLow(void)
{
	pinMode(_PA0,INPUT_PULLUP);
    pinMode(_PA1,INPUT_PULLUP);
    pinMode(_PA2,INPUT_PULLUP);
    pinMode(_PA3,INPUT_PULLUP);
    pinMode(_PB0,OUTPUT);
    pinMode(_PB2,OUTPUT);
    pinMode(_PB1,OUTPUT); 
    pinMode(_PB3,OUTPUT);
    digitalWrite(_PB0,LOW);digitalWrite(_PB1,LOW);digitalWrite(_PB2,LOW);digitalWrite(_PB3,LOW);
    delay(10);
    return digitalRead(_PA0) + (digitalRead(_PA1)<<1) + (digitalRead(_PA2)<<2) + (digitalRead(_PA3)<<3);
}

///将另外四个引脚设为上拉电平，余下四个为低电平
///读取单个引脚为上拉电阻的代码值，以四位的方式存储
uint8_t DFRobot_TouchKeyboard::groupALow(void)
{
	pinMode(_PB0,INPUT_PULLUP);
    pinMode(_PB1,INPUT_PULLUP);
    pinMode(_PB2,INPUT_PULLUP);
    pinMode(_PB3,INPUT_PULLUP);
    pinMode(_PA0,OUTPUT);
    pinMode(_PA2,OUTPUT);
    pinMode(_PA1,OUTPUT);
    pinMode(_PA3,OUTPUT);
    digitalWrite(_PA0,LOW);digitalWrite(_PA1,LOW);digitalWrite(_PA2,LOW);digitalWrite(_PA3,LOW);
    delay(10);
    return digitalRead(_PB0) + (digitalRead(_PB1)<<1) + (digitalRead(_PB2)<<2) + (digitalRead(_PB3)<<3);
}

///实现获取按键原始值函数，并以八位的形式存储在变量v中，返回值为v
///时间判断，若不满足条件，将直接进行等待
uint8_t DFRobot_TouchKeyboard::getValueRaw(void)
{
	while(millis() < _timestamp);
	_timestamp = millis()+_interval;
	uint8_t v = groupALow()+(groupBLow()<<4);
	DBG(v);
	return v;
}

///实现获取按键索引值函数
///去得到按下某一键后V的值，去列表中去比对，若一致时得到对应的索引值temp
uint8_t DFRobot_TouchKeyboard::getIndex()
{   
	int temp=-1;
	uint8_t v = getValueRaw();
	DBG(v);
	if(v != TOUCH_KEY_NONE){
		DBG("198");
		for(int i=0;i<16;i++){
			if(_kvmap[i][0]==v){
				DBG(i);
				DBG(_kvmap[i][0]);
				temp=_kvmap[i][2];
				break;
			}	
		}
	}
	return temp;
}

///实现获取按键显示值函数
///判断索引值对应大小，判断按键的值是符号还是数字，进行输出
///以查表的索引值进行读取按键的显示值
uint8_t DFRobot_TouchKeyboard::getKeyValue()
{
	uint8_t ret = TOUCH_KEY_NONE;
	uint8_t index = getIndex();
	//sizeof用法意义在于可根据结构调整，得到相应的子数组大小
	for(uint8_t i=0;i<sizeof(_kvmap)/sizeof(_kvmap[0]);i++){
		if(_kvmap[i][2] == index){
			DBG(index);
			if(index<10){
				ret=_kvmap[i][1];
				DBG(ret);
			}
			if(index>=10&&index<=15){
				ret=_kvmap[i][1];
				DBG(char(_kvmap[i][1]));
			}
		}		
	}
	return ret;
}






	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	