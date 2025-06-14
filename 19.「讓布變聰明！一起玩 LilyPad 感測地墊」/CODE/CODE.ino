// 音符頻率定義（單位：Hz）
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_F4  349
#define NOTE_F5  698
#define NOTE_AS4 466
#define NOTE_AS5 932

// RGB LED PWM 路線腳位定義
const int redLed = 3, greenLed = 5, blueLed = 6;

// 白光 LED 腳位（共五顆）
const int ledPins[5] = {7, 8, 10, 11, 12};

// 蜂鳴器腳位
const int buzzer = 9;

// 六顆按鈕對應的輸入腳位
const int switches[6] = {2, 4, A0, A1, A2, A3};

// 溫度與光線感測器腳位
const int tempSensor = A4;
const int lightSensor = A5;

// 模式控制變數：目前模式與前一個模式
int currentMode = 0;
int currentModebef = 0;

// 防彈跳陣列：記錄每個按鈕的前一個狀態
bool buttonPrevState[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

// LED/色彩動畫輔助變數
int fadeAmount = 0;
int i = 0;

// 星際大戰音樂資料：{音符, 音長, 延遲}
const int music[19][3] = {
  {NOTE_F4, 200, 200}, {NOTE_F4, 200, 200}, {NOTE_F4, 200, 200},
  {NOTE_AS4, 1200, 1200}, {NOTE_F5, 600, 600}, {NOTE_DS5, 200, 200},
  {NOTE_D5, 200, 200}, {NOTE_C5, 200, 200}, {NOTE_AS5, 1200, 1200},
  {NOTE_F5, 600, 600}, {NOTE_DS5, 200, 200}, {NOTE_D5, 200, 200},
  {NOTE_C5, 200, 200}, {NOTE_AS5, 1200, 1200}, {NOTE_F5, 600, 600},
  {NOTE_DS5, 200, 200}, {NOTE_D5, 200, 200}, {NOTE_DS5, 200, 200},
  {NOTE_C5, 900, 1200}
};

// RGB 彩虹顏色陣列
const int rainbowPattern[7][3] = {
  {255, 0, 0}, {255, 165, 0}, {255, 255, 0},
  {0, 128, 0}, {0, 0, 255}, {75, 0, 130}, {148, 0, 211}
};

// 設定腳位模式
void setup() {
  Serial.begin(9600); // 啟用序列監控
  for (int i = 0; i < 5; i++) pinMode(ledPins[i], OUTPUT);
  pinMode(redLed, OUTPUT); pinMode(greenLed, OUTPUT); pinMode(blueLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  for (int i = 0; i < 3; i++) pinMode(switches[i], INPUT_PULLUP);
  for (int i = 3; i < 6; i++) pinMode(switches[i], INPUT);
}

// 主迴圈根據當前模式執行對應功能
void loop() {
  checkButtons(); // 讀取按鈕並切換模式
  switch (currentMode) {
    case 1: playStarWars(); break;
    case 2: rainbowRGB(); break;
    case 3: colorFade(); break;
    case 4: ledAnimationAdvanced(); break;
    case 5: tempRGBDisplay(); break;
    case 6: lightToTone(); break;
    default:
      setAllWhite(LOW); setRGB(0, 0, 0); noTone(buzzer); // 模式為 0 時關閉全部
      break;
  }
}

// 檢查每顆按鈕是否觸發，並設定模式
void checkButtons() {
  for (int i = 0; i < 6; i++) {
    bool currentState = digitalRead(switches[i]);
    if (buttonPrevState[i] == LOW && currentState == HIGH) {
      delay(20); // 簡易防彈跳
      buttonPrevState[i] = currentState;
      currentMode = i + 1; // 將模式設為對應按鈕（1~6）
      if(currentModebef == currentMode){
        currentMode = 0;
        currentModebef = 0;
      } else {
        currentModebef = currentMode;
      }
      setAllWhite(LOW); setRGB(0, 0, 0); noTone(buzzer); // 切換時關閉輸出
    }
    buttonPrevState[i] = currentState;
  }
}

// 播放星際大戰主題音樂
void playStarWars() {
  static int index = 0;
  tone(buzzer, music[index][0], music[index][1]);
  delay(music[index][2]);
  index++;
  if (index >= 19) index = 0;
}

// 播放彩虹 RGB 色彩
void rainbowRGB() {
  static int index = 0;
  setRGB(rainbowPattern[index][0], rainbowPattern[index][1], rainbowPattern[index][2]);
  delay(300);
  index = (index + 1) % 7;
}

// RGB 綠/藍色漸變動畫
void colorFade() {
  static int val = 0, dir = 1, phase = 0;
  if (phase == 0) setRGB(0, val, 0); // 綠色階段
  else setRGB(0, 0, val);            // 藍色階段
  val += dir * 5;
  if (val >= 255 || val <= 0) {
    dir *= -1;
    if (val <= 0) phase = 1 - phase; // 切換顏色階段
  }
  delay(20);
}

// LED 動畫：左右跑馬燈 + 對稱擴散收縮
void ledAnimationAdvanced() {
  static int stage = 0, count = 0, index = 0;
  static unsigned long prevTime = 0;
  const int delayTime = 200;
  if (millis() - prevTime < delayTime) return;
  prevTime = millis();
  if (stage == 0) {
    if (count < 3) {
      if (index < 5) blinkOnce(ledPins[index++]);
      else if (index < 9) blinkOnce(ledPins[8 - index++]);
      else { index = 0; count++; }
    } else { count = 0; index = 0; stage = 1; }
  } else if (stage == 1) {
    if (count < 6) {
      bool expand = (count % 2 == 0);
      blinkSymmetricStep(index++, expand);
      if (index >= 3) { index = 0; count++; }
    } else { stage = 0; count = 0; index = 0; }
  }
}

// 顯示溫度對應 RGB 顏色（紅熱、藍冷）
void tempRGBDisplay() {
  int raw = analogRead(tempSensor);
  float voltage = raw * (5.0 / 1023.0);
  float celsius = (voltage - 0.5) * 100.0;
  float coldTemp = 15.0, hotTemp = 35.0;
  celsius = constrain(celsius, coldTemp, hotTemp);
  int blue = map(celsius, coldTemp, hotTemp, 0, 255);
  int red = map(celsius, coldTemp, hotTemp, 255, 0);
  setRGB(red, 0, blue);
  delay(300);
}

// 根據光線值產生不同音調音效
void lightToTone() {
  int val = analogRead(lightSensor);
  int pitch = map(val, 50, 400, 120, 1500);
  if (val > 50) tone(buzzer, pitch, 500);
  else noTone(buzzer);
  delay(100);
}

// 設定 RGB 顏色（共陰極需反轉輸出）
void setRGB(int r, int g, int b) {
  analogWrite(redLed, 255 - r);
  analogWrite(greenLed, 255 - g);
  analogWrite(blueLed, 255 - b);
}

// 設定全部白光 LED 為指定狀態
void setAllWhite(int state) {
  for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], state);
}

// 短暫閃爍單一 LED
void blinkOnce(int pin) {
  digitalWrite(pin, HIGH); delay(50); digitalWrite(pin, LOW);
}

// 同步閃爍對稱 LED，根據擴散或收縮順序決定亮滅腳位
void blinkSymmetricStep(int step, bool expand) {
  int forward[3][2] = { {2, 2}, {1, 3}, {0, 4} };
  int reverse[3][2] = { {0, 4}, {1, 3}, {2, 2} };
  int a = expand ? forward[step][0] : reverse[step][0];
  int b = expand ? forward[step][1] : reverse[step][1];
  digitalWrite(ledPins[a], HIGH);
  digitalWrite(ledPins[b], HIGH);
  delay(50);
  digitalWrite(ledPins[a], LOW);
  digitalWrite(ledPins[b], LOW);
}
