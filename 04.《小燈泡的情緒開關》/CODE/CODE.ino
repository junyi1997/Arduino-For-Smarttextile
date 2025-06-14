// === 腳位與變數定義 ===
const int buttonPin = 2;// 按鈕腳位（接 D2）
const int redPin = 9;// 紅色 LED 腳位（PWM）
const int greenPin = 10;// 綠色 LED 腳位（PWM）
const int bluePin = 11;// 藍色 LED 腳位（PWM）
bool buttonPrev = HIGH;// 上一次的按鈕狀態（預設未按）
bool breathing = false;// 是否進入呼吸模式
bool longPressed = false;// 是否是長按（>1 秒）
unsigned long pressStartTime = 0;// 記錄按下時間
int targetR = 0, targetG = 0, targetB = 0; // 目標 RGB 顏色
float currR = 0, currG = 0, currB = 0;// 目前 RGB 顏色（浮點數便於漸變）
float fadeSpeed = 0.01;// 顏色變化速度（數值越小越平滑）
unsigned long lastUpdate = 0;// 上一次顏色更新時間
void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 設定按鈕為上拉輸入（未按為 HIGH）
  pinMode(redPin, OUTPUT);// 設定紅色腳為輸出
  pinMode(greenPin, OUTPUT);// 設定綠色腳為輸出
  pinMode(bluePin, OUTPUT);// 設定藍色腳為輸出
  randomSeed(analogRead(0));// 使用類比輸入初始化亂數種子
}
void loop() {
  bool buttonState = digitalRead(buttonPin); // 讀取目前按鈕狀態
  unsigned long now = millis();// 獲取目前時間
  // 如果按鈕剛剛被按下（HIGH -> LOW）
  if (buttonPrev == HIGH && buttonState == LOW) {
    pressStartTime = now;
    longPressed = false;
  }
  // 如果按鈕持續被按，且時間超過 1 秒，進入呼吸模式
  if (buttonPrev == LOW && buttonState == LOW && !longPressed) {
    if (now - pressStartTime > 1000) {
      breathing = true;
      longPressed = true;
      generateNewTargetColor(); // 隨機產生第一個目標顏色
    }
  }
  // 放開按鈕（LOW -> HIGH）
  if (buttonPrev == LOW && buttonState == HIGH) {
    if (!longPressed) {// 如果不是長按，則為短按，立即換色
      breathing = false;
      generateNewTargetColor(); // 產生新顏色
      currR = targetR;
      currG = targetG;
      currB = targetB;
      applyColor(currR, currG, currB); // 立即寫入顏色
    }
  }
  // 呼吸模式中，每 20 毫秒平滑更新顏色
  if (breathing && (now - lastUpdate > 20)) {
    lastUpdate = now;
    currR = smoothStep(currR, targetR); // 將目前 R 漸漸接近目標 R
    currG = smoothStep(currG, targetG); // G
    currB = smoothStep(currB, targetB); // B
    applyColor(currR, currG, currB);// 實際輸出顏色
    // 如果三個顏色都已接近目標值，換新色
    if (abs(currR - targetR) < 1 && abs(currG - targetG) < 1 && abs(currB - targetB) < 1) {
      generateNewTargetColor(); // 換一個新目標顏色
    }
  }
  buttonPrev = buttonState; // 更新按鈕狀態
}
// === 計算顏色平滑變化（漸進逼近目標） ===
float smoothStep(float current, float target) {
  return current + (target - current) * fadeSpeed;
}
  // === 將目前 RGB 顏色寫入 LED ===
void applyColor(float r, float g, float b) {
  analogWrite(redPin, (int)r);
  analogWrite(greenPin, (int)g);
  analogWrite(bluePin, (int)b);
}
// === 隨機產生一個新顏色（避免太暗） ===
void generateNewTargetColor() {
  targetR = random(50, 256);
  targetG = random(50, 256);
  targetB = random(50, 256);
}

