#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
int servo = 6;//4번핀 서보모터
/*********************서보모터 각도설정*/
int angle_on = 120;
int angle_mid = 90;
int angle_off = 45;
/***********************************/
//int state = 0;
int sound = 0;
//--------------------------------------------------------
/*
#define CL 131
#define DL 147
#define EL 165
#define FL 175
#define GL 196
#define AL 220
#define BL 247
*/
#define CM 262
#define DM 294
#define EM 330
#define FM 349
#define GM 392
#define AM 440
#define BM 494
#define CH 523

#define DH 588
#define EH 660
#define FH 698
#define GH 784
#define AH 880
#define BH 988

int Melody = 5;

void Melody_ON(){
  tone(Melody, CM); delay(240); noTone(Melody); delay(10);
  tone(Melody, GM); delay(240); noTone(Melody); delay(10);
  tone(Melody, CH); delay(240); noTone(Melody); delay(10);
  tone(Melody, BM); delay(490); noTone(Melody); delay(10);
  tone(Melody, GM); delay(250); noTone(Melody);
}
void Melody_OFF(){
  tone(Melody, CH); delay(240); noTone(Melody); delay(10);
  tone(Melody, GM); delay(240); noTone(Melody); delay(10);
  tone(Melody, CM); delay(240); noTone(Melody); delay(10);
  tone(Melody, DM); delay(250); noTone(Melody);
}
//--------------------------------------------------------
SoftwareSerial hc06(2,3); //Tx, Rx
//--------------------------------------------------------
void MENU(){
  hc06.write("********************\n");
  hc06.write("*\t\tM  E  N  U   = M\t\t*\n");
  hc06.write("*\t\tSwitch ON  = O\t\t*\n");
  hc06.write("*\t\tSwitch OFF = X\t\t*\n");
  hc06.write("*\t\tSound ON   = 1\t\t*\n");
  hc06.write("*\t\tSound OFF  = 0\t\t*\n");
  hc06.write("*\t\tSound TEST= T\t*\n");
  hc06.write("********************\n");
}
//--------------------------------------------------------
byte buffer[1024];
int bufferPosition;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  hc06.begin(9600);
  bufferPosition = 0;

  MENU();

  myservo.attach(servo);
  myservo.write(angle_mid);
  delay(2000);
  myservo.detach();
  pinMode(Melody, OUTPUT);
//  pinMode(6, OUTPUT);
//  digitalWrite(6, HIGH);//3.3V
}
//--------------------------------------------------------
//--------------------------------------------------------
void loop() {
  if(hc06.available())
  {
    byte dataFromBt = hc06.read();
    Serial.write(dataFromBt);
    buffer[bufferPosition++] = dataFromBt;
  
    if(dataFromBt == '\n'){
      buffer[bufferPosition] = '\0';
      //안드로이드로 받은 문자열 전송함
      hc06.write(buffer, bufferPosition);
      bufferPosition = 0;
    }    
//--------------------------------------------------------
myservo.detach();
    //각 상황별 설정
    if(dataFromBt == '.'){
      Serial.println("\n");
      hc06.write("\n");
      dataFromBt = 0;
    } 
    
    if (dataFromBt == 'O'){
      digitalWrite(LED_BUILTIN, HIGH);
      if (sound == 1){
        delay(100);
        Melody_ON();
        }
      dataFromBt = 0;

      myservo.attach(servo);
      myservo.write(angle_on);
      delay(2000);
      myservo.write(angle_mid);
      
      Serial.println("\n");
      hc06.write("Switch ON\n");
    }

    if(dataFromBt == 'X'){
      digitalWrite(LED_BUILTIN, LOW);
      if (sound == 1){
        delay(100);
        Melody_OFF();
        }
      dataFromBt = 0;
      
      myservo.attach(servo);
      myservo.write(angle_off);
      delay(2000);
      myservo.write(angle_mid);
      
      Serial.println("\n");
      hc06.write("Switch OFF\n");
    }


    if(dataFromBt == 'T'){
      digitalWrite(LED_BUILTIN, LOW);
      Melody_ON();
      delay(750);
      Melody_OFF();
      dataFromBt = 0;
      Serial.println("\n");
      hc06.write("Sound Test end\n");
    }

    if(dataFromBt == '0'){
      sound = 0;
      hc06.write("\t\tSound OFF\n");
    }

    if(dataFromBt == '1'){
      sound = 1;
      hc06.write("\t\tSound ON\n");
    }

    if(dataFromBt == 'M'){
      MENU();
    }
  }
//--------------------------------------------------------
  if(Serial.available()){
    hc06.write(Serial.read()); //시리얼 모니터 내용을 블루투스에 쓰기
  }       
  delay(100);
}
