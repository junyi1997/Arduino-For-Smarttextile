// === 腳位設定 ===
const int ldrPin = A0;          // 光敏電阻接腳 A0
const int redPin = 9;           // RGB LED 紅色腳位（PWM）
const int greenPin = 10;        // 綠色腳位
const int bluePin = 11;         // 藍色腳位

// === 呼吸燈變數 ===
float currR = 0, currG = 0, currB = 0;    // 目前 RGB 顏色（浮點數可漸變）
int targetR = 0, targetG = 0, targetB = 0;// 目標 RGB 顏色
float fadeSpeed = 0.01;                  // 顏色變化速度（越小越慢）

unsigned long lastUpdate = 0;            // 上次更新時間
int lightThreshold = 500;                // 光敏電阻臨界值（可調整）

bool isNight = false;                    // 是否進入「夜晚模式」（光線偏暗）

void setup() {
  pinMode(redPin, OUTPUT);               // 設定 RGB 為輸出
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);                    // 開啟序列埠監看光線數值
  randomSeed(analogRead(0));             // 用類比值初始化亂數種子
}
