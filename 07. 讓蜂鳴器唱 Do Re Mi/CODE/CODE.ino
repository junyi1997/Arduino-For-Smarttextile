const int buzzer = 9;
void setup() {
  // Do Re Mi 音階
  tone(buzzer, 262); // Do
  delay(500);
  tone(buzzer, 294); // Re
  delay(500);
  tone(buzzer, 330); // Mi
  delay(500);
  noTone(buzzer);    // 停止聲音
}
void loop() {
}
