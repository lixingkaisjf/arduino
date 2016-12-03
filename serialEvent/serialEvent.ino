unsigned char Re_buf[11];
unsigned char counter = 0;
unsigned char sign = 0; //校验位

void setup() {
  Serial.begin(9600);

}

void loop() {
  if (sign) {
    sign = 0;   //标识符
    
    if (Re_buf[0]==49) //检测帧头
    {
      //发送数据
      Serial.println(Re_buf[0]);
      Serial.println(Re_buf[1]);
      Serial.println(Re_buf[2]);
      Serial.println(Re_buf[3]);
	  Serial.println("---------------------------------");
    }
  }

}

//所有串口相关的操作都会调用此函数 （这是系统库函数，起到中断作用）
void serialEvent() {
  while (Serial.available()) {    // 看串口缓冲区中是否有数据
    //Serial.println("test");  //测试
    //Serial.println(Re_buf[0]);  //测试

    Re_buf[counter] = (unsigned char)Serial.read();   //每次读取一个字节，并赋值给Re_buf数组
    if (counter == 0 && Re_buf[0] != 49) return;  //第0号数据不是指定的帧头，就重现读取（对应的ascii值）
    counter++;    //索引数组下标
    if (counter == 4) {    //接受到11个数据
      counter = 0;    //重新赋值
      sign = 1;   //标识符
    }

  }
}
