const int buttonPin = 2;
const int ledPin = 13;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // 按鈕接腳位 2
  pinMode(ledPin, OUTPUT);           // LED 接腳位 13
}
void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {          // 注意：按下時為 LOW（因為使用 pull-up）
    digitalWrite(ledPin, HIGH);      // LED 亮
  } else {
    digitalWrite(ledPin, LOW);       // LED 滅
  }
}
