/*!
 * @file readSound.ino
 * @brief 读取环境声音强度，单位DB
 * @n 实验现象：每秒读取一次环境光线强度，并打印到串口
 * @n 给传感器以不同的光照强度，可以得到不同的采集结果
 * @n 由于只有4 bits存放声音强度，最低分辨率8dB，所以测量范围是 0dB-120dB
 *
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#include <DFRobot_TouchKeyboard.h>
DFRobot_TouchKeyboard kb;
void setup() {
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