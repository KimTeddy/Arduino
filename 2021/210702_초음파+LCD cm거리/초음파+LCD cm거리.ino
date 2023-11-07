#include <HCSR04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

byte triggerPin = 12;//트리거 핀
byte echoCount = 1;
byte* echoPins = new byte[echoCount] {13};//에코 핀

long* times = new long[echoCount];
double* distances = new double[echoCount];

//https://maxpromer.github.io/LCD-Character-Creator/

uint8_t g[8] = 
{
  B00000,
  B01111,
  B00001,
  B00001,
  B00010,
  B00100,
  B01000,
  B00000
};
uint8_t eo[8] = 
{
  B00100,
  B00100,
  B11100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
uint8_t l[8] = 
{
  B00000,
  B11110,
  B00010,
  B11110,
  B10000,
  B10001,
  B11110,
  B00000
};
uint8_t ee[8] = 
{
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000
};

void setup ()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  lcd.createChar(0, g);//ㄱ
  lcd.createChar(1, eo);//ㅓ
  lcd.createChar(2, l);//ㄹ
  lcd.createChar(3, ee);//ㅣ
  lcd.home();
  HCSR04.begin(triggerPin, echoPins, echoCount);
  pinMode(8,OUTPUT);//초음파센서 전원용
  digitalWrite(8,HIGH);
}

void loop()
{
  lcd.setCursor(0,0);

  HCSR04.measureDistanceCm(distances);

  for(int letter=0;letter<4;letter++)
    lcd.write(letter);
  lcd.print(" = ");
  
  if(distances[0] == -1)
    lcd.print("  -  ");//초음파가 돌아오지 않아 인식이 안 될 때
  else
    lcd.print(distances[0]);
    
  lcd.print("cm    ");

  delay(200);
}
