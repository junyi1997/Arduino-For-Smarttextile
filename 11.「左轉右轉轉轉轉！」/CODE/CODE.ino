#include <Servo.h>         // 載入 Servo 函式庫（內建，不需額外安裝）

Servo myservo;             // 建立一個伺服馬達物件，名稱為 myservo

void setup() {
  myservo.attach(9);       // 將伺服馬達連接到 Arduino 的 D9 腳位
}

void loop() {
  myservo.write(0);        // 將馬達轉到 0 度位置（起始點）
  delay(1000);             // 停 1 秒

  myservo.write(90);       // 將馬達轉到 90 度位置（中間）
  delay(1000);             // 停 1 秒

  myservo.write(180);      // 將馬達轉到 180 度位置（最遠端）
  delay(1000);             // 停 1 秒

  myservo.write(90);       // 再次轉回 90 度
  delay(1000);             // 停 1 秒
}
