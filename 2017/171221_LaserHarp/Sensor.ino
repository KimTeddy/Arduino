#define CL 131
#define DL 147
#define EL 165
#define FL 175
#define GL 196
#define AL 220
#define BL 247
#define CM 262
#define DM 294
#define EM 330
#define FM 349
#define GM 392
#define AM 440
#define BM 494
#define BbM 466
#define CH 523
#define DH 588
#define EH 660
#define FH 698
#define GH 784
#define AH 880
#define BH 988
//-----------------------------------------------
int Buz = 13; // 버저핀 지정

// 버튼핀 지정
int Sen_fl = A4;
int Sen_gl = A3;
int Sen_al = A2;
int Sen_bl = A1;
int Sen_cm = A0;
int Sen_dm = 2;
int Sen_em = 3;
int Sen_fm = 4;
int Sen_gm = 5;
int Sen_am = 6;
int Sen_bm = 7;
int Sen_ch = 8;
int Sen_dh = 9;
int Sen_eh = 10;
int Sen_fh = 11;
int Sen_gh = 12;
//------------------------------------------------
//함수추가
//------------------------------------------------
void setup() {
pinMode(Sen_fl, INPUT);pinMode(Sen_gl, INPUT); pinMode(Sen_al, INPUT); pinMode(Sen_bl, INPUT); pinMode(Sen_cm, INPUT); pinMode(Sen_dm, INPUT); pinMode(Sen_em, INPUT); pinMode(Sen_fm, INPUT); pinMode(Sen_gm, INPUT); pinMode(Sen_am, INPUT); pinMode(Sen_bm, INPUT); pinMode(Sen_ch, INPUT); pinMode(Sen_dh, INPUT); pinMode(Sen_eh, INPUT); pinMode(Sen_fh, INPUT); pinMode(Sen_gh, INPUT);

pinMode(Buz, OUTPUT);
noTone(Buz);

  Serial.begin(9600);
}
int sec = 15;
int pin = 0;

void loop() {
  pin = 0;
  if (digitalRead(Sen_fl)==LOW){Serial.println("낮은파");  // 센서값 출력
                    tone(Buz, FL);delay(sec);pin=1;}

  if (digitalRead(Sen_gl)==LOW){Serial.println("낮은솔");  // 센서값 출력
                    tone(Buz, GL);delay(sec);pin=1;}

  if (digitalRead(Sen_al)==LOW){Serial.println("낮은라");  // 센서값 출력
                    tone(Buz, AL);delay(sec);pin=1;}

  if (digitalRead(Sen_bl)==LOW){Serial.println("낮은시");  // 센서값 출력
                    tone(Buz, BL);delay(sec);pin=1;}

  if (digitalRead(Sen_cm)==LOW){Serial.println("가온도");  // 센서값 출력
                    tone(Buz, CM);delay(sec);pin=1;}

  if (digitalRead(Sen_dm)==LOW){Serial.println("가온레");  // 센서값 출력
                    tone(Buz, DM);delay(sec);pin=1;}

  if (digitalRead(Sen_em)==LOW){Serial.println("가온미");  // 센서값 출력
                    tone(Buz, EM);delay(sec);pin=1;}

  if (digitalRead(Sen_fm)==LOW){Serial.println("가온파");  // 센서값 출력
                    tone(Buz, FM);delay(sec);pin=1;}

  if (digitalRead(Sen_gm)==LOW){Serial.println("가온솔");  // 센서값 출력
                    tone(Buz, GM);delay(sec);pin=1;}

  if (digitalRead(Sen_am)==LOW){Serial.println("가온라");  // 센서값 출력
                    tone(Buz, AM);delay(sec);pin=1;}

  if (digitalRead(Sen_bm)==LOW){Serial.println("가온시");  // 센서값 출력
                    tone(Buz, BM);delay(sec);pin=1;}

  if (digitalRead(Sen_ch)==LOW){Serial.println("높은도");  // 센서값 출력
                    tone(Buz, CH);delay(sec);pin=1;}

  if (digitalRead(Sen_dh)==LOW){Serial.println("높은레");  // 센서값 출력
                    tone(Buz, DH);delay(sec);pin=1;}

  if (digitalRead(Sen_eh)==LOW){Serial.println("높은미");  // 센서값 출력
                    tone(Buz, EH);delay(sec);pin=1;}

  if (digitalRead(Sen_fh)==LOW){Serial.println("높은파");  // 센서값 출력
                    tone(Buz, FH);delay(sec);pin=1;}

  if (digitalRead(Sen_gh)==LOW){Serial.println("높은솔");  // 센서값 출력
                    tone(Buz, GH);delay(sec);pin=1;}
 
  if (pin == 0) {
   noTone(Buz);}
      
}



