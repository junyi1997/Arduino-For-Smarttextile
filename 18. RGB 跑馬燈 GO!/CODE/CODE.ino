#include <Adafruit_NeoPixel.h>  // 匯入 NeoPixel 控制函式庫

#define PIN 2  // 設定 NeoPixel 接在 Arduino 的第 2 號腳位

#define NUMPIXELS 12  // 定義 LED 燈條上有 12 顆 NeoPixel 燈珠

// 建立一個 NeoPixel 物件，傳入燈珠數量、腳位，以及燈珠通訊頻率與顏色順序設定
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100;  // 每顆燈變色之間的延遲時間（單位：毫秒）

// 儲存 RGB 顏色的三個變數
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  // 初始化 NeoPixel 模組，這行一定要加才會啟用硬體控制
  pixels.begin();
}

void loop() {
  setColor();  // 隨機設定一組 RGB 顏色值

  // 用迴圈控制每一顆燈依序點亮
  for (int i = 0; i < NUMPIXELS; i++) {
    // 設定第 i 顆 NeoPixel 的顏色為隨機的 RGB
    pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));

    // 傳送資料到 NeoPixel 燈條（一定要呼叫 show() 才會更新）
    pixels.show();

    // 每顆燈之間暫停 delayval 毫秒，營造「逐顆亮起」效果
    delay(delayval);
  }
}

// setColor()
// 這個函式隨機產生一組 RGB 顏色值（每個值為 0~254 之間）
void setColor() {
  redColor = random(0, 255);    // 隨機紅色值
  greenColor = random(0, 255);  // 隨機綠色值
  blueColor = random(0, 255);   // 隨機藍色值
}
