// Arduino LED 流水燈效果示範程式

// LED 接腳陣列（由左到右）
int ledPins[] = {9, 10, 11, 12, 13};

// 延遲時間（單位：毫秒）
int delayTime = 200;

void setup() {
  // 將每個 LED 接腳設為輸出模式
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // 第一段：LED從左到右再從右到左流動，重複3次
  for (int j = 0; j < 3; j++) {
    // 左到右亮滅
    for (int i = 0; i < 5; i++) {
      blinkLED(ledPins[i], delayTime);
    }
    // 右到左亮滅（注意 i > 0，故不包含 ledPins[0]）
    for (int i = 4; i > 0; i--) {
      blinkLED(ledPins[i], delayTime);
    }
  }

  // 第二段：對稱點亮 LED 的圖案，重複3次
  for (int j = 0; j < 3; j++) {
    // 由中間向外擴散亮
    symmetricPattern(true);
    // 由外向中間收回亮
    symmetricPattern(false);
  }
}

// ✅ 封裝通用的 LED 閃爍函式
void blinkLED(int pin, int duration) {
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
}

// ✅ 封裝對稱圖案（擴散 / 收縮）函式
void symmetricPattern(bool expand) {
  if (expand) {
    // 擴散：中 → 兩側
    blinkLED(ledPins[2], delayTime);                        // 中間
    blinkDualLEDs(ledPins[1], ledPins[3], delayTime);       // 中間兩側
    blinkDualLEDs(ledPins[0], ledPins[4], delayTime);       // 最兩側
  } else {
    // 收縮：兩側 → 中
    blinkDualLEDs(ledPins[0], ledPins[4], delayTime);
    blinkDualLEDs(ledPins[1], ledPins[3], delayTime);
    blinkLED(ledPins[2], delayTime);
  }
}

// ✅ 同步點亮兩個 LED 的函式
void blinkDualLEDs(int pin1, int pin2, int duration) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  delay(duration);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}
