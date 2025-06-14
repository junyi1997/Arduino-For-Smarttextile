// 腳位設定
#define BUZZER_PIN   9     // 蜂鳴器腳位
#define LDR_PIN      A0    // 光敏電阻腳位

// 音符頻率定義（C 大調）
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// 播放速度控制範圍（單位：ms）
#define TEMPO_FAST   100   // 最快節奏（光很亮）
#define TEMPO_SLOW   800   // 最慢節奏（光很暗）

int melody[] = {
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4,

  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_C4, NOTE_C4
};

int noteDurations[] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 2, 2,

  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 2, 2
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  Serial.begin(9600);  // 若需觀察光線數值
}

void loop() {
  int length = sizeof(melody) / sizeof(int);

  for (int i = 0; i < length; i++) {
    int lightValue = analogRead(LDR_PIN);  // 讀取 LDR 值（0~1023）

    // 根據光線值對應節奏（越亮越快）
    int tempo = map(lightValue, 0, 1023, TEMPO_FAST, TEMPO_SLOW);

    int duration = tempo * 4 / noteDurations[i];

    Serial.print("LDR: ");
    Serial.print(lightValue);
    Serial.print(" → Tempo: ");
    Serial.println(duration);

    tone(BUZZER_PIN, melody[i], duration);
    delay(duration * 1.3);  // 節奏間隔
    noTone(BUZZER_PIN);
  }

  delay(2000);  // 播完休息 2 秒再重播
}
