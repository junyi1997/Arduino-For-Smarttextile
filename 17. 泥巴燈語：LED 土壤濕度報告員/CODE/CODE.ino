// C++ code

int moisture = 0;  // 儲存土壤濕度感測值的變數

void setup()
{
  pinMode(A0, OUTPUT);    // A0 接腳作為電源輸出，控制濕度感測器供電
  pinMode(A1, INPUT);     // A1 接腳用來讀取濕度感測器的類比數值
  Serial.begin(9600);     // 啟用序列埠監控，傳輸速率為 9600
  pinMode(8, OUTPUT);     // 將數位腳位 8 設為輸出（最濕）
  pinMode(9, OUTPUT);     // LED 輸出腳位（偏濕）
  pinMode(10, OUTPUT);    // LED 輸出腳位（中等）
  pinMode(11, OUTPUT);    // LED 輸出腳位（偏乾）
  pinMode(12, OUTPUT);    // LED 輸出腳位（最乾）
}

void loop()
{
  // 啟動濕度感測器電源
  digitalWrite(A0, HIGH);
  delay(10);  // 等待感測器穩定 10 毫秒

  // 讀取濕度值，數值範圍為 0~1023，數值越大表示越乾
  moisture = analogRead(A1);

  // 關閉濕度感測器電源以減少金屬腐蝕
  digitalWrite(A0, LOW);

  // 將濕度值輸出到序列監控視窗，方便除錯觀察
  Serial.println(moisture);

  // 先關閉所有 LED，準備重新根據濕度開啟對應亮度
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  // 根據濕度值點亮不同的 LED：
  // 數值越小代表越濕，越大代表越乾
  if (moisture < 200) {
    digitalWrite(12, HIGH);  // 非常濕，點亮最下層 LED（最乾）
  } else {
    if (moisture < 400) {
      digitalWrite(11, HIGH);  // 偏濕
    } else {
      if (moisture < 600) {
        digitalWrite(10, HIGH);  // 中等濕度
      } else {
        if (moisture < 800) {
          digitalWrite(9, HIGH);  // 偏乾
        } else {
          digitalWrite(8, HIGH);  // 非常乾，最上層 LED
        }
      }
    }
  }

  delay(100);  // 每次更新後延遲 100 毫秒
}
