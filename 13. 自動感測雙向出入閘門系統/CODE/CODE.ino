#include <Servo.h>                   // 載入 Servo 函式庫控制伺服馬達
Servo myservo;                      // 建立伺服馬達物件

// === 腳位設定 ===
int Server_motor = 9;               // 伺服馬達接腳
int CdS_in = A0, CdS_out = A1;      // 兩個光敏電阻：進入、離開感測
int LED_R = 2, LED_G = 3, LED_B = 4;// RGB LED 三色燈控制腳

// === 狀態變數 ===
int count = 2;                      // 車位剩餘數（最大為 2）
int CdS_in_state = 0, CdS_out_state = 0; // 用來判斷是否剛通過感測器
int LED_R_state = 0, LED_G_state = 0, LED_B_state = 0; // 控制 LED 狀態
int car_in = 0, car_out = 0;        // 用來控制閘門開關狀態

void setup() {
  pinMode(CdS_in, INPUT);           // 設定 CdS 光敏輸入
  pinMode(CdS_out, INPUT);
  pinMode(LED_R, OUTPUT);           // 設定 RGB 為輸出
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(Server_motor, OUTPUT);    // 伺服馬達腳為輸出

  analogWrite(LED_R, 0);            // 初始化 RGB 為關閉狀態
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 0);

  myservo.attach(Server_motor);     // 初始化伺服馬達
  Serial.begin(9600);               // 啟動序列監控
  myservo.write(90);                // 馬達預設在 90 度（關門）
}

void loop() {
  // === 進入感測區（進車）===
  if (analogRead(CdS_in) < 500) {   // 感應到遮光（有車進入）
    if (CdS_in_state == 0) {
      delay(2);                     // 去抖動
      CdS_in_state = 1;
      if (count > 0) {              // 若還有車位
        if (car_in == 0) {          // 初始狀態：開門進車
          car_in = 1;
          count--;                  // 車位減少
          myservo.write(0);         // 馬達轉 0 度（開門）
          delay(15);
        } else {                    // 若 car_in 為 1，再次感應則關門
          car_in = 0;
          myservo.write(90);        // 馬達轉 90 度（關門）
          delay(15);
        }
      } else {
        count = 0;                  // 保險措施，不讓 count < 0
      }
    }
  } else {
    delay(2);
    if (CdS_in_state == 1) CdS_in_state = 0; // 感應器回復未遮光狀態
  }

  // === 離開感測區（出車）===
  if (analogRead(CdS_out) < 500) {
    if (CdS_out_state == 0) {
      delay(2);                     // 去抖動
      CdS_out_state = 1;
      if (count < 2) {              // 若車位未滿
        if (car_in == 0) {
          car_in = 1;
          count++;                  // 車位數增加
          myservo.write(0);         // 開門
          delay(15);
        } else {
          car_in = 0;
          myservo.write(90);        // 關門
          delay(15);
        }
      } else {
        count = 2;                  // 最多為 2 個車位
      }
    }
  } else {
    delay(2);
    if (CdS_out_state == 1) CdS_out_state = 0;
  }

  // === 根據車位數設定 RGB 顯示狀態 ===
  if (count == 0) {
    LED_R_state = 1; LED_G_state = 0; LED_B_state = 0;  // 紅燈：滿位
  } else if (count == 1) {
    LED_R_state = 0; LED_G_state = 0; LED_B_state = 1;  // 藍燈：剩 1 位
  } else {
    LED_R_state = 0; LED_G_state = 1; LED_B_state = 0;  // 綠燈：有位
  }

  digitalWrite(LED_R, LED_R_state);
  digitalWrite(LED_G, LED_G_state);
  digitalWrite(LED_B, LED_B_state);

  // 顯示目前狀態
  Serial.print("count = ");
  Serial.print(count);
  Serial.print("  car_in = ");
  Serial.println(car_in);
}
