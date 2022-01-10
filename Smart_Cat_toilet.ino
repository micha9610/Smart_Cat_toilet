#include <DFPlayer_Mini_Mp3.h>
#include <LiquidCrystal.h>
#define rxPin 3 
#define txPin 2 
SoftwareSerial esp01(txPin, rxPin); // SoftwareSerial NAME(TX, RX);
int ledPin1=9;
int ledPin2=8;
int inputPin=7;
int pirState=LOW;
int val = 0;
int count = 0;
const int GasPin = A0;
const int ledPin = 12;
int GasValue;
SoftwareSerial mySerial(10,11);
LiquidCrystal lcd(35, 34, 33, 32, 31, 30);

void setup() {
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(inputPin,INPUT);
  pinMode(GasPin ,INPUT);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("MY CAT TOILET");
  Serial.begin(9600);   //시리얼모니터
  esp01.begin(9600);  //와이파이 시리얼
  mySerial.begin(9600);
  mp3_set_serial(mySerial);
  mp3_set_volume(90);
  mp3_play(1);
  Serial.println("CAT DATA");
  Serial.println("LABEL,Gas,Gas LED,PIR LED");
}

void loop() {
  val=digitalRead(inputPin);
  Serial.print("DATA,");
  Serial.print(analogRead(GasPin));
  Serial.print(",");
  Serial.print(digitalRead(ledPin));
  Serial.print(",");
  Serial.println(digitalRead(ledPin1));
   if (val == HIGH){
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin2,LOW);
    if (pirState == LOW){
      mp3_play(1);
      delay(10000);
    }   
  }
  else{
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,HIGH);
    mp3_play(3);
    }
    
  GasValue = analogRead(GasPin); //gasvalue는 gaspin의 값을 읽어옵니다.
  if (GasValue >= 150) //500보다 크거나 같을시에
  {
    digitalWrite(ledPin, HIGH); //LED의 빛이 나옵니다.
    lcd.setCursor(0,1);
    lcd.print("CHANGE SAND!");
  }
  else
  {
    digitalWrite(ledPin, LOW); // 작을시에는 꺼집니다
    lcd.setCursor(0,1);
    lcd.print("CLEAN       ");
  }
  Serial.print(""); //시리얼 프린트에 값이 나옵니다.
  delay(300);
}
