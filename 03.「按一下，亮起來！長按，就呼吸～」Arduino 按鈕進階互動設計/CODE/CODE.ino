// === 引腳與變數定義 ===
const int buttonPin = 2;          // 按鈕腳位
const int redPin = 9;             // RGB 紅腳（PWM）
const int greenPin = 10;          // RGB 綠腳
const int bluePin = 11;           // RGB 藍腳

bool buttonPrev = HIGH;           // 前一次按鈕狀態
bool breathing = false;           // 是否為呼吸模式
bool longPressed = false;         // 是否為長按
unsigned long pressStartTime = 0; // 按鈕按下時間

// 顏色變數：目標值與目前值（使用 float 做漸變）
int targetR = 0, targetG = 0, targetB = 0;
float currR = 0, currG = 0, currB = 0;

float fadeSpeed = 0.01;           // 顏色漸變速度
unsigned long lastUpdate = 0;     // 上次更新時間

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 上拉輸入（未按為 HIGH）
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  randomSeed(analogRead(0));        // 初始化亂數種子
}

void loop() {
  bool buttonState = digitalRead(buttonPin); // 讀取目前按鈕狀態
  unsigned long now = millis();              // 獲取目前時間

  // === 偵測剛按下 ===
  if (buttonPrev == HIGH && buttonState == LOW) {
    pressStartTime = now;
    longPressed = false;
  }

  // === 判斷長按 → 啟動呼吸模式 ===
  if (buttonPrev == LOW && buttonState == LOW && !longPressed) {
    if (now - pressStartTime > 1000) {
      breathing = true;
      longPressed = true;
      generateNewTargetColor(); // 初始化第一個目標色
    }
  }

  // === 放開按鈕 → 若非長按則為短按切色 ===
  if (buttonPrev == LOW && buttonState == HIGH) {
    if (!longPressed) {
      breathing = false;              // 關閉呼吸模式
      generateNewTargetColor();      // 立即換色
      currR = targetR;
      currG = targetG;
      currB = targetB;
      applyColor(currR, currG, currB);
    }
  }

  // === 呼吸模式：漸變顏色（每 20ms 更新一次） ===
  if (breathing && (now - lastUpdate > 20)) {
    lastUpdate = now;

    // 平滑靠近目標顏色
    currR = smoothStep(currR, targetR);
    currG = smoothStep(currG, targetG);
    currB = smoothStep(currB, targetB);
    applyColor(currR, currG, currB);

    // 若已接近目標色 → 換下一組顏色
    if (abs(currR - targetR) < 1 && abs(currG - targetG) < 1 && abs(currB - targetB) < 1) {
      generateNewTargetColor();
    }
  }

  buttonPrev = buttonState; // 更新按鈕狀態
}

// === 顏色漸變輔助函式 ===
float smoothStep(float current, float target) {
  return current + (target - current) * fadeSpeed;
}

// === 將目前顏色寫入 LED ===
void applyColor(float r, float g, float b) {
  analogWrite(redPin, (int)r);
  analogWrite(greenPin, (int)g);
  analogWrite(bluePin, (int)b);
}

// === 產生新的隨機目標顏色 ===
void generateNewTargetColor() {
  targetR = random(50, 256); // 避免過暗
  targetG = random(50, 256);
  targetB = random(50, 256);
}
