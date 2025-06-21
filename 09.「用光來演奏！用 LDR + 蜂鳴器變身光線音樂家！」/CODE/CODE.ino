const int ldrPin = A0;
const int buzzerPin = 9;
void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int lightValue = analogRead(ldrPin);
  Seril.println(lightValue);
  int toneFreq = map(lightValue, 0, 1023, 1000, 200);  // 光越強 → 音越低
  tone(buzzerPin, toneFreq);
  delay(100);
}
