// 設定腳位：TRIG（發射）接 D8，ECHO（接收）接 D7
const int trigger = 8; 
const int echo = 7; 

float dist;  // 儲存計算出來的距離（公分）

void setup() {
  Serial.begin(9600);        // 開啟序列埠，讓我們可以在監控視窗中看到結果
  pinMode(trigger, OUTPUT);  // TRIG 腳位是輸出（負責發出超音波）
  pinMode(echo, INPUT);      // ECHO 腳位是輸入（接收回音）
}

void loop() {
  digitalWrite(trigger, LOW);        // 先確保 TRIG 是 LOW（準備發射）
  delayMicroseconds(5);              // 稍等 5 微秒
  digitalWrite(trigger, HIGH);       // TRIG 短暫拉 HIGH → 發出一個超音波脈衝
  delayMicroseconds(10);             // 保持 HIGH 狀態 10 微秒
  digitalWrite(trigger, LOW);        // 再拉回 LOW，完成一次「嗶～」

  dist = pulseIn(echo, HIGH);        // 量測 ECHO 腳收到高電位的時間（微秒）

  dist = dist / 58.0;                // 把時間轉換為距離（公分）
                                     // 若要轉換為英吋，可除以 148

  Serial.print("Distancia = ");      // 顯示標籤
  Serial.print(dist);                // 顯示距離值
  Serial.println(" cm");             // 單位（公分）

  delay(200);                        // 每 0.2 秒測量一次
}
