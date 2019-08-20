/*
 * @file TouchKeyboard.ino
 * @brief 以默认引脚值插入，读取键盘按键的值
 * @n 实验现象：最快每秒读取一次按下键盘按键的值，并打印到串口
 *
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [John](yzm19971997@gmail.com)
 * @version  V1.0
 * @date  2019-08-19
 * @https://github.com/cdjq/DFRobot_TouchKeyboard
 */
#include <DFRobot_TouchKeyboard.h>
DFRobot_TouchKeyboard kb;
void setup() {
  /*默认引脚值为12,11,10,9,8,7,6,5(从1号到八号)
    Serial.begin(115200);
    /*设置intercal的值为1000，即两次按键最短可读时间为1秒*/
	  int interval=1000;
    /*初始化函数，设定引脚值*/
    kb.begin(interval);
}
void loop() {
  uint8_t v = kb.getKeyValue();
  if(v != TOUCH_KEY_NONE){
    if(v<10){
    Serial.print("value=");Serial.println(v);}
    if(v>=10){
      char ch;
      ch=char(v);
    Serial.print("value=");Serial.println(ch);}
  }
}