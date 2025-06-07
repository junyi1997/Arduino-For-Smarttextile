const int ldrPin = A0;      // LDR 接腳
const int ledPin = 9;       // LED 接腳
int lightValue = 0;         // 儲存光線數值
int threshold = 500;        // 臨界亮度（越暗數值越高，依實際測試微調）
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  lightValue = analogRead(ldrPin);
  Serial.println(lightValue);
  if (lightValue < threshold) {
    digitalWrite(ledPin, HIGH);  // 太暗 → 開燈
  } else {
    digitalWrite(ledPin, LOW);   // 太亮 → 關燈
  }
  delay(200);
}
