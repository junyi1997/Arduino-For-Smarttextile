// === 腳位設定 ===
#define PIR_PIN     2     // PIR 感測器腳位
#define BUZZER_PIN  9     // 蜂鳴器腳位

// === 音符頻率定義（簡化 C 大調）===
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440

// === 音樂旋律：小星星 ===
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2
};

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    Serial.println("感應到人！播放音樂中...");

    for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
      int duration = 1000 / noteDurations[i];
      tone(BUZZER_PIN, melody[i], duration);
      delay(duration * 1.3);     // 停頓稍長一點比較自然
      noTone(BUZZER_PIN);
    }

    delay(5000);  // 播放完後等待一段時間避免重複觸發
  }
}
