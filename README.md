# 韦根26协议解析

## 接口

* `void AnswerDataZeroExti(void)`：响应DATA0中断

* `void AnswerDataOneExti(void)`：响应DATA1中断

  以上连个函数需置于相应的两个中断中

* `unsigned char ReadWiegandResult(unsigned char *hidLow, unsigned short *pid)`：

  读取协议解析结果的函数，建议放在主循环

* `void CheckWiegandDataDelay(void)`：防止计数出错的函数，虽不是必须，但仍然建议使用，并且放在毫秒级的定时器中断中

  ​