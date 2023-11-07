// 버튼핀 지정
int Las_fl = 10;
int Las_gl = 11;
int Las_al = 9;
int Las_bl = 8;
int Las_cm = 7;
int Las_dm = 6;
int Las_em = 5;
int Las_fm = 4;
int Las_gm = 3;
int Las_am = 2;
int Las_bm = A0;
int Las_ch = A1;
int Las_dh = A2;
int Las_eh = A3;
int Las_fh = A4;
int Las_gh = A5;

int But = 12;
//------------------------------------------------
void Play_chop();//함수추가
//------------------------------------------------
void setup() {
pinMode(Las_fl, OUTPUT);
pinMode(Las_gl, OUTPUT);
pinMode(Las_al, OUTPUT);
pinMode(Las_bl, OUTPUT);
pinMode(Las_cm, OUTPUT); 
pinMode(Las_dm, OUTPUT);
pinMode(Las_em, OUTPUT); 
pinMode(Las_fm, OUTPUT); 
pinMode(Las_gm, OUTPUT); 
pinMode(Las_am, OUTPUT); 
pinMode(Las_bm, OUTPUT); 
pinMode(Las_ch, OUTPUT);
pinMode(Las_dh, OUTPUT);
pinMode(Las_eh, OUTPUT);
pinMode(Las_fh, OUTPUT);
pinMode(Las_gh, OUTPUT);

pinMode(But, INPUT);

  Serial.begin(9600);

//---------초기세팅--------------------------------
int a = 50;
digitalWrite(Las_fl, HIGH);delay(a);
digitalWrite(Las_gl, HIGH);delay(a);
digitalWrite(Las_al, HIGH);delay(a);
digitalWrite(Las_bl, HIGH);delay(a);
digitalWrite(Las_cm, HIGH);delay(a);
digitalWrite(Las_dm, HIGH);delay(a);
digitalWrite(Las_em, HIGH);delay(a);
digitalWrite(Las_fm, HIGH);delay(a);
digitalWrite(Las_gm, HIGH);delay(a);
digitalWrite(Las_am, HIGH);delay(a);
digitalWrite(Las_bm, HIGH);delay(a);
digitalWrite(Las_ch, HIGH);delay(a);
digitalWrite(Las_dh, HIGH);delay(a);
digitalWrite(Las_eh, HIGH);delay(a);
digitalWrite(Las_fh, HIGH);delay(a);
digitalWrite(Las_gh, HIGH);
}
//-------------------------------------------------------
void loop() {
   if (digitalRead(But) == LOW) {
    Play_chop();}
  
else{
digitalWrite(Las_fl, HIGH);
digitalWrite(Las_gl, HIGH);
digitalWrite(Las_al, HIGH);
digitalWrite(Las_bl, HIGH);
digitalWrite(Las_cm, HIGH);
digitalWrite(Las_dm, HIGH);
digitalWrite(Las_em, HIGH);
digitalWrite(Las_fm, HIGH);
digitalWrite(Las_gm, HIGH);
digitalWrite(Las_am, HIGH);
digitalWrite(Las_bm, HIGH);
digitalWrite(Las_ch, HIGH);
digitalWrite(Las_dh, HIGH);
digitalWrite(Las_eh, HIGH);
digitalWrite(Las_fh, HIGH);
digitalWrite(Las_gh, HIGH);
}

}
int chop = 200;
int choff = 50;
int chopp = 450;
void Play_chop() {
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);

  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);

  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);

  digitalWrite(Las_cm,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);
  digitalWrite(Las_cm,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);
  digitalWrite(Las_cm,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);
  digitalWrite(Las_cm,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);//시
  digitalWrite(Las_em,LOW);digitalWrite(Las_am,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_am,HIGH);delay(choff);//라


    digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_fm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);

  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);

  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);
  digitalWrite(Las_dm,LOW);digitalWrite(Las_bm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);

  digitalWrite(Las_cm,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);//도
  digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_gm,HIGH);delay(choff);                                                   //솔
  digitalWrite(Las_em,LOW);delay(chop);  digitalWrite(Las_em,HIGH);delay(choff);                                                   //미
  digitalWrite(Las_cm,LOW);delay(chopp);                                                                                           //도
                                             digitalWrite(Las_cm,HIGH);delay(choff);
    digitalWrite(Las_ch,LOW);digitalWrite(Las_eh,LOW);delay(chop);  digitalWrite(Las_ch,HIGH);digitalWrite(Las_eh,HIGH);delay(choff);//미


  digitalWrite(Las_bm,LOW);digitalWrite(Las_dh,LOW);delay(chopp);  digitalWrite(Las_bm,HIGH);digitalWrite(Las_dh,HIGH);delay(choff);//레
  digitalWrite(Las_am,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_am,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);//도
  digitalWrite(Las_gm,LOW);digitalWrite(Las_bm,LOW);delay(chopp);  digitalWrite(Las_gm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);//시
  digitalWrite(Las_fm,LOW);digitalWrite(Las_am,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_am,HIGH);delay(choff);//라

  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chopp);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_fm,LOW);digitalWrite(Las_am,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_am,HIGH);delay(choff);//라
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔

  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chopp);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  
  digitalWrite(Las_cm,LOW);digitalWrite(Las_em,LOW);delay(chopp);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_em,HIGH);delay(choff);//미
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chopp);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
    digitalWrite(Las_ch,LOW);digitalWrite(Las_eh,LOW);delay(chop);  digitalWrite(Las_ch,HIGH);digitalWrite(Las_eh,HIGH);delay(choff);//미
  
  digitalWrite(Las_bm,LOW);digitalWrite(Las_dh,LOW);delay(chopp);  digitalWrite(Las_bm,HIGH);digitalWrite(Las_dh,HIGH);delay(choff);//레
  digitalWrite(Las_am,LOW);digitalWrite(Las_ch,LOW);delay(chop);  digitalWrite(Las_am,HIGH);digitalWrite(Las_ch,HIGH);delay(choff);//도
  digitalWrite(Las_gm,LOW);digitalWrite(Las_bm,LOW);delay(chopp);  digitalWrite(Las_gm,HIGH);digitalWrite(Las_bm,HIGH);delay(choff);//시
    digitalWrite(Las_fm,LOW);digitalWrite(Las_am,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_am,HIGH);delay(choff);//라

  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chopp);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_fm,LOW);digitalWrite(Las_am,LOW);delay(chop);  digitalWrite(Las_fm,HIGH);digitalWrite(Las_am,HIGH);delay(choff);//라
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔

  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chopp);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  digitalWrite(Las_em,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_dm,LOW);digitalWrite(Las_fm,LOW);delay(chop);  digitalWrite(Las_dm,HIGH);digitalWrite(Las_fm,HIGH);delay(choff);//파
  
  digitalWrite(Las_cm,LOW);digitalWrite(Las_em,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_em,HIGH);delay(choff);//미
  digitalWrite(Las_cm,LOW);digitalWrite(Las_gm,LOW);delay(chop);  digitalWrite(Las_cm,HIGH);digitalWrite(Las_gm,HIGH);delay(choff);//솔
  digitalWrite(Las_gm,LOW);digitalWrite(Las_eh,LOW);delay(chop);  digitalWrite(Las_gm,HIGH);digitalWrite(Las_eh,HIGH);delay(choff);//미
    digitalWrite(Las_gl,LOW);delay(choff);//솔
    digitalWrite(Las_cm,LOW);delay(choff);//도
    digitalWrite(Las_em,LOW);delay(choff);//미
    digitalWrite(Las_gm,LOW);delay(choff);//솔
    digitalWrite(Las_ch,LOW);delay(chopp);//도
    digitalWrite(Las_gl,HIGH);digitalWrite(Las_cm,HIGH);digitalWrite(Las_em,HIGH);digitalWrite(Las_gm,HIGH);digitalWrite(Las_ch,HIGH);
  
 setup();
}
