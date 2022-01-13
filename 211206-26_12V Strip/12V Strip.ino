/*
    Project     FastLED NeoPixel Library
    @author     David Madison
    @link       github.com/dmadison/FastLED_NeoPixel
    @license    MIT - Copyright (c) 2021 David Madison

   This file is part of the FastLED NeoPixel Library.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

*/

/**
  @file    StripVariant.ino
  @brief   Demonstrates how to use a different strip type.
  @example StripVariant.ino
  @brief   Demonstrates how to use a different strip type.
*/
#define SERIAL
#include <FastLED_NeoPixel.h>

// Which pin on the Arduino is connected to the LEDs?
#define DATA_PIN 10

// How many LEDs are attached to the Arduino?
#define NUM_LEDS 20

// LED brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];
FastLED_NeoPixel_Variant strip(leds, NUM_LEDS);

#define r1 A3
#define g1 A7
#define b1 A6

#define r2 A2
#define g2 A1
#define b2 A0

#define Nobe_Enable 12
int PIR = 2;
bool currentPIR = LOW, previousPIR = LOW, LED_off_flag = false;
int ledState[3] = {0};

int rgb[2][3] = {0};
void setup() {
  strip.begin(FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS));
  strip.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
#ifdef SERIAL
  Serial.begin(9600);
#endif
  pinMode(PIR, INPUT);   // PIR를 입력핀으로 설정합니다.
  pinMode(Nobe_Enable, OUTPUT);
  
  /*
    Instead of using the plain 'strip.begin()', we need to pass the
    CLEDController reference returned by the 'FastLED.addLeds()' call. This
    lets the strip use 'show()' and brightness independent of the rest of
    program and any other present LED strips.

    Although this is using the typical WS2812B strip setup, you can customize
    it for any strip configuration, including strips that use SPI (data + clock).
  */
digitalWrite(Nobe_Enable, HIGH);
delay(100);
  rgb[0][0] = map(analogRead(r1), 0, 1023, 0, 255);
  rgb[0][1] = map(analogRead(g1), 0, 1023, 0, 255);
  rgb[0][2] = map(analogRead(b1), 0, 1023, 0, 255);
  rgb[1][0] = map(analogRead(r2), 0, 1023, 0, 255);
  rgb[1][1] = map(analogRead(g2), 0, 1023, 0, 255);
  rgb[1][2] = map(analogRead(b2), 0, 1023, 0, 255);
  //digitalWrite(Nobe_Enable, LOW);
#ifdef SERIAL
  for (int x = 0; x < 2; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      Serial.print(rgb[x][y]);
      Serial.print(", ");
    }
  }
  Serial.println("");
  /*
  for (int y = 0; y < 100; y++)
    {
  Serial.println(analogRead(r1));
    }
  Serial.println("");
  */
#endif
digitalWrite(Nobe_Enable, LOW);
  for (int ledTest = 0; ledTest < 2; ledTest++)
  {
    for (int dot = 0; dot < NUM_LEDS; dot++)
    {
      leds[dot] = CRGB(rgb[ledTest][0], rgb[ledTest][1], rgb[ledTest][2]);
      FastLED.show();
      delay(30);
    }
    delay(500);
  }
  FastLED.clear();
  FastLED.show();
}


void loop() {
  if (digitalRead(PIR) == HIGH) {
    ColorChange(255, 255, 140);
#ifdef SERIAL
    Serial.println("end");
#endif
    previousPIR = HIGH;
    delay(5000);
  }
  if (digitalRead(PIR) == HIGH) {
    ColorChange(rgb[0][0], rgb[0][1], rgb[0][2]);
#ifdef SERIAL
    Serial.println("end");
#endif
    previousPIR = HIGH;
    delay(5000);
  }
  if (digitalRead(PIR) == HIGH) {
    ColorChange(rgb[1][0], rgb[1][1], rgb[1][2]);
#ifdef SERIAL
    Serial.println("end");
#endif
    previousPIR = HIGH;
    delay(5000);
  }
  /*
    while(digitalRead(PIR) == LOW)
    {
    if(digitalRead(PIR) == HIGH)break;
    }
  */
  currentPIR = digitalRead(PIR);

  if (previousPIR == HIGH && currentPIR == LOW)
  {
    LED_off_flag = true;
    ColorChange(50, 50, 50);
    if (LED_off_flag == true)
    {
      ColorChange(0, 0, 0);
      FastLED.clear();
      FastLED.show();
      previousPIR = currentPIR;
    }
    LED_off_flag = false;
  }
}





void ColorChange(int R, int G, int B)
{
  int flagAll = 0;
  bool flagR = 0, flagG = 0, flagB = 0;

  while (flagAll != 3)
  {
    if (LED_off_flag == true && digitalRead(PIR) == HIGH) {
      LED_off_flag = false;
      break;
    }

    if (ledState[0] > R)ledState[0]--;
    else if (ledState[0] < R)ledState[0]++;
    else flagR = 1;
#ifdef SERIAL
    Serial.print(ledState[0]); Serial.print(", ");
#endif
    if (ledState[1] > G)ledState[1]--;
    else if (ledState[1] < G)ledState[1]++;
    else flagG = 1;
#ifdef SERIAL
    Serial.print(ledState[1]); Serial.print(", ");
#endif
    if (ledState[2] > B)ledState[2]--;
    else if (ledState[2] < B)ledState[2]++;
    else flagB = 1;
#ifdef SERIAL
    Serial.println(ledState[2]);
#endif
    flagAll = flagR + flagG + flagB;

    for (int dot = 0; dot < NUM_LEDS; dot++)
    {
      leds[dot] = CRGB(ledState[0], ledState[1], ledState[2]);
    }

    FastLED.show();
    delay(50);
  }
}
