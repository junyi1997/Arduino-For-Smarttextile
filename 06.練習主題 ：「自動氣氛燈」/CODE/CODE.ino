// === 腳位設定 ===
const int ldrPin = A0;          // 光敏電阻接腳 A0
const int redPin = 9;           // RGB LED 紅色腳位（PWM）
const int greenPin = 10;        // 綠色腳位
const int bluePin = 11;         // 藍色腳位

// === 呼吸燈變數 ===
float currR = 0, currG = 0, currB = 0;     // 當前 RGB 顏色（使用 float 便於漸變）
int targetR = 0, targetG = 0, targetB = 0; // 目標 RGB 顏色
float fadeSpeed = 0.01;                   // 顏色變化速度（越小越平滑）
unsigned long lastUpdate = 0;             // 上次顏色更新時間
int lightThreshold = 500;                 // 光線臨界值（越低越容易進入夜晚模式）
bool isNight = false;                     // 判斷是否為夜間（光線過暗）

void setup() {
  pinMode(redPin, OUTPUT);                // 設定紅腳為輸出
  pinMode(greenPin, OUTPUT);              // 綠腳輸出
  pinMode(bluePin, OUTPUT);               // 藍腳輸出
  Serial.begin(9600);                     // 啟用序列監看器，用於觀察光線數值
  randomSeed(analogRead(0));              // 使用模擬值初始化亂數
}

void loop() {
  int lightValue = analogRead(ldrPin);    // 讀取光敏電阻的亮度值
  Serial.println(lightValue);             // 印出值以供偵測與設定 threshold
  isNight = lightValue < lightThreshold;  // 若光線低於臨界值 → 進入夜間模式

  if (isNight) {
    // === 夜間：自動開始 RGB 呼吸燈 ===
    unsigned long now = millis();
    if (now - lastUpdate > 20) {
      lastUpdate = now;

      // 將當前顏色緩慢逼近目標顏色
      currR = smoothStep(currR, targetR);
      currG = smoothStep(currG, targetG);
      currB = smoothStep(currB, targetB);

      applyColor(currR, currG, currB);  // 實際輸出 PWM 值

      // 若 RGB 顏色已接近目標，換新色
      if (abs(currR - targetR) < 1 &&
          abs(currG - targetG) < 1 &&
          abs(currB - targetB) < 1) {
        generateNewTargetColor();       // 隨機產生下一組目標顏色
      }
    }
  } else {
    // === 白天：關閉 LED，節能模式 ===
    applyColor(0, 0, 0);
  }
}

// === 緩慢逼近目標顏色（平滑漸變）===
float smoothStep(float current, int target) {
  return current + (target - current) * fadeSpeed;
}

// === 實際輸出 RGB PWM 數值到 LED ===
void applyColor(float r, float g, float b) {
  analogWrite(redPin, (int)r);
  analogWrite(greenPin, (int)g);
  analogWrite(bluePin, (int)b);
}

// === 產生新的目標顏色（避免太暗）===
void generateNewTargetColor() {
  targetR = random(50, 255);
  targetG = random(50, 255);
  targetB = random(50, 255);
}
