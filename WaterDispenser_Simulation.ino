#include <LiquidCrystal_I2C.h>

int Relay = 3;
int Button_1 = 7;
int Button_2 = 6;
int Button_3 = 8;
int Button_4 = 9;

int IR_Sensor = 2;

enum State {
  IDLE,
  OPTION_1,
  HOT_WATER,
  WARM_WATER,
  PAY_10,
  PAY_20,
  CONFIRM_PAYMENT_10,
  CONFIRM_PAYMENT_20,
  PLACE_TUMBLER
};

State CurrentState = IDLE;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(Relay, OUTPUT);
  pinMode(IR_Sensor, INPUT);
  pinMode(Button_1, INPUT_PULLUP);
  pinMode(Button_2, INPUT_PULLUP);
  pinMode(Button_3, INPUT_PULLUP);
  pinMode(Button_4, INPUT_PULLUP);

  digitalWrite(Relay, LOW);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("SYSTEM");
  lcd.setCursor(1, 1);
  lcd.print("INITIALIZATION");
  delay(1000);
}

void loop() {
  switch (CurrentState) {
    case IDLE:
      idle();
      break;
    case OPTION_1:
      option_1();
      break;
    case HOT_WATER:
      hot_water();
      break;
    case WARM_WATER:
      warm_water();
      break;
    case PAY_10:
      pay_10();
      break;
    case PAY_20:
      pay_20();
      break;
    case CONFIRM_PAYMENT_10:
      confirm_payment_10();
      break;
    case CONFIRM_PAYMENT_20:
      confirm_payment_20();
      break;
    case PLACE_TUMBLER:
      place_tumbler();
      break;
  }
}
void idle() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WATER DISPENSER");
  lcd.setCursor(0, 1);
  lcd.print("PRESS 1 TO PROCEED");
  if (digitalRead(Button_1) == LOW) {
    CurrentState = OPTION_1;
  }
  delay(1000);
}
void option_1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. HOT WATER");
  lcd.setCursor(0, 1);
  lcd.print("2. COLD WATER");
  if (digitalRead(Button_1) == LOW) {
    CurrentState = HOT_WATER;
  }
  if (digitalRead(Button_2) == LOW) {
    CurrentState = WARM_WATER;
  }
  delay(1000);
}
void hot_water() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. 500ML");
  lcd.setCursor(0, 1);
  lcd.print("2. 1000ML");
  if (digitalRead(Button_1) == LOW) {
    CurrentState = PAY_10;
  }
  if (digitalRead(Button_2) == LOW) {
    CurrentState = PAY_20;
  }
  delay(1000);
}
void warm_water() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. 500ML");
  lcd.setCursor(0, 1);
  lcd.print("2. 1000ML");
  if (digitalRead(Button_1) == LOW) {
    CurrentState = PAY_10;
  }
  if (digitalRead(Button_2) == LOW) {
    CurrentState = PAY_20;
  }
  delay(1000);
}
void pay_10() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("KINDLY PAY 10");
  lcd.setCursor(0, 1);
  lcd.print("WAITING PAYMENT");
  if (digitalRead(Button_3) == LOW) {
    CurrentState = CONFIRM_PAYMENT_10;
  }
  delay(1000);
}
void pay_20() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("KINDLY PAY 20");
  lcd.setCursor(0, 1);
  lcd.print("WAITING PAYMENT");
  if (digitalRead(Button_4) == LOW) {
    CurrentState = CONFIRM_PAYMENT_20;
  }
  delay(1000);
}
void confirm_payment_10() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PAYMENT RECEIVED");
  lcd.setCursor(0, 1);
  lcd.print("AMOUNT KSH 10");
  delay(1000);
  CurrentState = PLACE_TUMBLER;
}
void confirm_payment_20() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PAYMENT RECEIVED");
  lcd.setCursor(0, 1);
  lcd.print("AMOUNT KSH 20");
  delay(1000);
  CurrentState = PLACE_TUMBLER;
}
void place_tumbler() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLACE TUMBLER");
  lcd.setCursor(0, 1);
  lcd.print("BELOW THE TAP");
  if (digitalRead(IR_Sensor) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TUMBLER DETECTED");
    lcd.setCursor(0, 1);
    lcd.print("WATER DISPENSING");
    digitalWrite(Relay, HIGH);
    delay(200);
    digitalWrite(Relay, LOW);
    CurrentState = IDLE;
  }
  delay(1000);
}
