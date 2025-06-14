const int buttonPin = 2;         // 定義按鈕接腳為 D2
const int ledPin = 9;            // 定義 LED 接腳為 D9（支援 PWM）
int ledBrightness = 0;           // 記錄目前 LED 亮度
int step = 25;                   // 每次短按亮度變化的幅度
bool increasing = true;          // 控制亮度增加或減少的方向
bool breathing = false;          // 是否進入「呼吸燈模式」
unsigned long lastPressTime = 0; // 紀錄上次按下的時間（未使用，可移除）
unsigned long pressStartTime = 0;// 紀錄按鈕被按下的時間
bool buttonPrev = HIGH;          // 紀錄前一次的按鈕狀態（HIGH = 未按）
bool buttonLongPress = false;    // 是否為長按觸發
unsigned long lastBreathTime = 0;// 呼吸模式中上次更新亮度的時間
int breathStep = 3;              // 呼吸燈模式每次亮度變化的幅度
void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 設定按鈕為上拉輸入（未按為 HIGH）
  pinMode(ledPin, OUTPUT);          // 設定 LED 腳位為輸出
}
void loop() {
  bool buttonState = digitalRead(buttonPin); // 讀取目前按鈕狀態
  unsigned long now = millis();              // 獲取目前時間（毫秒）
  // 偵測按鈕剛被按下（從 HIGH → LOW）
  if (buttonPrev == HIGH && buttonState == LOW) {
    pressStartTime = now;         // 記錄按下的起始時間
    buttonLongPress = false;      // 預設非長按
  }
  // 若持續按住 → 判斷是否超過 1 秒為長按
  if (buttonPrev == LOW && buttonState == LOW) {
    if (!buttonLongPress && now - pressStartTime > 1000) {
      breathing = true;           // 進入呼吸燈模式
      buttonLongPress = true;     // 標記為長按
    }
  }
  // 當按鈕從 LOW → HIGH，表示釋放
  if (buttonPrev == LOW && buttonState == HIGH) {
    if (!buttonLongPress) {
      breathing = false;          // 離開呼吸燈模式
      // 短按時進行亮度增加／減少循環
      if (increasing) {
        ledBrightness += step;
        if (ledBrightness >= 255) {
          ledBrightness = 255;
          increasing = false;     // 達最大值後改為減少
        }
      } else {
        ledBrightness -= step;
        if (ledBrightness <= 0) {
          ledBrightness = 0;
          increasing = true;      // 達最小值後改為增加
        }
      }
      analogWrite(ledPin, ledBrightness); // 寫入新亮度（PWM 控制 LED）
    }
  }
    // 呼吸燈模式：LED 亮度緩慢上升與下降
  if (breathing) {
    if (now - lastBreathTime >= 20) {      // 每 20ms 更新一次亮度
      lastBreathTime = now;
      edBrightness += increasing ? breathStep : -breathStep;
      if (ledBrightness >= 255) {
        ledBrightness = 255;
        increasing = false;                // 到達最亮 → 轉為漸暗
      } else if (ledBrightness <= 0) {
        ledBrightness = 0;
        increasing = true;                 // 到達最暗 → 轉為漸亮
      }
      analogWrite(ledPin, ledBrightness);  // 更新 LED 亮度
    }
  }
  buttonPrev = buttonState; // 更新按鈕狀態供下一輪使用
}


