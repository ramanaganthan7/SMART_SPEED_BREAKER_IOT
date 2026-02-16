#include ESP32Servo.h
#include LiquidCrystal.h    LCD library

#define SERVO_PIN 18
#define SENSOR_A 32
#define SENSOR_B 33

 Traffic Light Pins
#define GREEN_LED 25
#define YELLOW_LED 26
#define RED_LED 27

Servo myservo;

 LCD pins RS, E, D4, D5, D6, D7
LiquidCrystal lcd(19, 21, 22, 23, 5, 17);
 
 For time measurement
volatile unsigned long timeA = 0;
volatile unsigned long timeB = 0;

bool waitingForB = false;
bool objectProcessed = false;

const float distance = 0.30;  30 cm between sensors (meters)

enum LightState {GREEN, YELLOW, RED};
LightState currentState = GREEN;

unsigned long lightStartTime = 0;
unsigned long lightDuration = 0;

void IRAM_ATTR sensorA_ISR() {
  timeA = micros();
  waitingForB = true;
  objectProcessed = false;
}

void IRAM_ATTR sensorB_ISR() {
  if (waitingForB) {
    timeB = micros();
  }
}

void setLight(LightState state, unsigned long durationMs) {
  currentState = state;
  lightStartTime = millis();
  lightDuration = durationMs;

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (state == GREEN) digitalWrite(GREEN_LED, HIGH);
  else if (state == YELLOW) digitalWrite(YELLOW_LED, HIGH);
  else if (state == RED) digitalWrite(RED_LED, HIGH);
}

void setup() {
  Serial.begin(9600);

  pinMode(SENSOR_A, INPUT_PULLUP);
  pinMode(SENSOR_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(SENSOR_A), sensorA_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_B), sensorB_ISR, FALLING);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  setLight(GREEN, 0);

  myservo.attach(SERVO_PIN);
  myservo.write(0);

   LCD setup
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Speed Monitor);
  lcd.setCursor(0, 1);
  lcd.print(System Ready);
  delay(2000);
  lcd.clear();
}

void loop() {
  if (waitingForB && timeB  timeA && !objectProcessed) {
    unsigned long dt = timeB - timeA;
    float dt_sec = dt  1000000.0;
    float speed_mps = distance  dt_sec;
    float speed_kmh = speed_mps  3.6;

    Serial.print(Object detected → Speed );
    Serial.print(speed_kmh);
    Serial.println( kmh);

     Display speed on LCD (top row)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(Speed);
    lcd.setCursor(7, 0);
    lcd.print(speed_kmh, 1);  show 1 decimal place
    lcd.print(kmh);

     Overspeed → RED
    if (speed_kmh  10.0) {
      setLight(RED, 5000);

       Show Overspeed immediately
      lcd.setCursor(0, 1);
      lcd.print(Overspeed     );  spaces clear leftover text

      myservo.write(90);
      delay(5000);    block for 5s
      myservo.write(0);
    } 
     Normal speed → YELLOW
    else {
      setLight(YELLOW, 5000);

      lcd.setCursor(0, 1);
      lcd.print(Normal Speed  );  keep bottom line filled
    }

    objectProcessed = true;
    waitingForB = false;
    timeA = 0;
    timeB = 0;
  }

   Handle light timing
  if (currentState != GREEN && millis() - lightStartTime = lightDuration) {
    setLight(GREEN, 0);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(Speed Monitor);
    lcd.setCursor(0, 1);
    lcd.print(System Ready);
  }
}
