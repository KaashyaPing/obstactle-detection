#define ECHO_PIN 3
#define TRIGGER_PIN 4
#include <LiquidCrystal_I2C.h>
#define RED_PIN 12 
#define YELLOW_PIN 11
#define GREEN_PIN 10
#define BUZZER_PIN 9
#define BUTTON_PIN 2
#define Threshold_RED 10.0
#define Threshold_Yellow 20.0

LiquidCrystal_I2C lcd(0x27,16,2);

// Ultra sonic sensor
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 100;

//Red LED
unsigned long lastTimeRED = millis();
unsigned long REDdelay = 500;
byte Redstate = LOW;

//Yellow LED
unsigned long lastTimeYELLOW = millis();
unsigned long YELLOWdelay = 500;
byte Yellowstate = LOW;


void triggerUltrasonicSensor()
{
  digitalWrite(TRIGGER_PIN,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN,LOW);
}

void blinkRED() {
  Redstate = !Redstate;                     // Toggle state
  digitalWrite(RED_PIN, Redstate);          // Actually turn LED on/off
  if (Redstate == HIGH) {
    tone(BUZZER_PIN, 1000); // 1kHz beep
  } else {
    noTone(BUZZER_PIN);
  }
  
  lastTimeRED = millis();
}



void blinkYELLOW() {
  Yellowstate = !Yellowstate;
  digitalWrite(YELLOW_PIN, Yellowstate);
  lastTimeYELLOW = millis();
}

double getUltraSonicDistance()
{
  double durationMicros = pulseIn(ECHO_PIN, HIGH);
  double distance = durationMicros / 58.0;
  return distance;
}



void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
 
}


void loop() {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  double distance = getUltraSonicDistance();

  if (distance < Threshold_RED && (timeNow - lastTimeRED > REDdelay)) {
    blinkRED();
    digitalWrite(YELLOW_PIN, LOW); // Turn off Yellow
    digitalWrite(GREEN_PIN, LOW);  // Turn off Green
  }
  else if (distance >= Threshold_RED && distance < Threshold_Yellow && (timeNow - lastTimeYELLOW > YELLOWdelay)) {
    blinkYELLOW();
    digitalWrite(RED_PIN, LOW);    // Turn off Red
    digitalWrite(GREEN_PIN, LOW);  // Turn off Green
    noTone(BUZZER_PIN);
  }
  else if (distance >= Threshold_Yellow) {
    digitalWrite(GREEN_PIN, HIGH); // Turn on Green
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  lcd.setCursor(0, 0);
  lcd.print(distance);
  lcd.print(" cm   ");
}



