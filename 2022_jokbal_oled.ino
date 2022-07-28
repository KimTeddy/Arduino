#include <U8g2lib.h>
//OLED
#define start_cursor 0
#define line_width 15


int pos[8]={1,2,3,4,5,6,7,180};

//화면 전환
unsigned long nowTime=0; // 현재 시간을 저장
unsigned long pastTime=0; // 과거 시간 저장 변수
//bool powerSaveMode = LOW;
enum displays {NAME=0, MOTOR, SENSOR, VOID};
enum displays state = NAME;

//절전 모드
int lastMotor[8]={0};
int currentMotor[8]={0};

//OLED
//U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 3, /* data=*/ 2, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather M0 Basic Proto + FeatherWing OLED
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 3, 2); //[full framebuffer, size = 1024 bytes]

void oled_display(enum displays st);

void setup()
{
  Serial.begin(9600);
  //OLED setup
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFontDirection(0);

  oled_display(NAME);
}

void loop()
{
/*******************************OLED Change*******************************/

  nowTime = millis(); // 현재 시간을 저장

  if((nowTime - pastTime) >= ((1000)*3))
  { //지정 시간 지나면
    pastTime = nowTime;
    state = state+1;
    if(state == VOID) state= NAME;
    Serial.println(state);
    u8g2.clearBuffer();// u8g2.firstPage(); do{} while( u8g2.nextPage() );
    oled_display(state);
  } 

}/*******************************END of LOOP*******************************/


void oled_display(enum displays st)
{
  int line=0;
  switch(st)
  {
    case NAME:
              do
              {
                u8g2.setFont(u8g2_font_unifont_t_korean1);
                  u8g2.setCursor((127/2)-10, (63/2)+5);  u8g2.print("밤이");
              } while( u8g2.nextPage() );
              break;
      
    case MOTOR:
    
              /*******************************MOTOR DEGREE DISPLAY*******************************/
              char leftmotor[4][8]={0};//모터 각도 int->string
              char rightmotor[4][8]={0};
              
              char buf[8][4]={"M1","M2","M3","M4","M5","M6","M7","M8"};
              
              for(int num=0; num<4; num++)//모터 각도 값을 문자열로 변환하고
              {
                sprintf(leftmotor[num],"%3d",pos[num]);
                sprintf(rightmotor[num],"%3d",pos[num+4]);
              }
              
              u8g2.setFont(u8g2_font_t0_13b_tf);
              for(line=0; line<4; line++)
              {
                u8g2.setCursor(0,   start_cursor + (line+1)*line_width);  u8g2.print(buf[line]);
                u8g2.setCursor(20,  start_cursor + (line+1)*line_width);  u8g2.print(strcat(leftmotor[line],"°"));
                u8g2.setCursor(80,  start_cursor + (line+1)*line_width);  u8g2.print(buf[line+4]);
                u8g2.setCursor(100, start_cursor + (line+1)*line_width);  u8g2.print(strcat(rightmotor[line],"°"));
              }
              
              do{} while( u8g2.nextPage() );
              break;

    case SENSOR:
    //delay(2000);
    u8g2.clearBuffer();
              char sensor[8][8]={0};
              char sensorName[8][4]={"A1","A2","A3","A4","A5","A6","A7","A8"};
              
              sprintf(sensor[0],"%3d", 42);   sprintf(sensor[4],"%3d", 82);
              sprintf(sensor[1],"%3d",230);   sprintf(sensor[5],"%3d", 57);
              sprintf(sensor[2],"%3d",147);   sprintf(sensor[6],"%3d",255);
              sprintf(sensor[3],"%3d", 62);   sprintf(sensor[7],"%3d",  0);
              
              for(line=0; line<4; line++)
              {
                //u8g2.setFont(u8g2_font_t0_13b_tf);
                u8g2.setCursor(0,   start_cursor + (line+1)*line_width);  u8g2.print(sensorName[line]);
                u8g2.setCursor(20,  start_cursor + (line+1)*line_width);  u8g2.print(sensor[line]);
                u8g2.setCursor(80,  start_cursor + (line+1)*line_width);  u8g2.print(sensorName[line+4]);
                u8g2.setCursor(100, start_cursor + (line+1)*line_width);  u8g2.print(sensor[line+4]);
              }
              
              do{} while( u8g2.nextPage() );
              break;
              
     default:
              break;
  }
}

/*******************************MOTOR DEGREE Changed*******************************/
/*
void degreeChanged()//모터 각도 변화 확인
{
  for(int i=0; i<8; i++)
  {
    currentMotor[i] = pos[i];
    if(currentMotor[i]==lastMotor[i])
    {
      pastTime = nowTime;
      
      powerSaveMode = !powerSaveMode;// powerSaveMode 를 토글
      Serial.println(powerSaveMode);
  
      if(powerSaveMode == HIGH)//절전모드 활성화
      {
        u8g2.clearBuffer();
        u8g2.firstPage();
        do
        {
          u8g2.setCursor(115, 10);u8g2.setFont(u8g2_font_open_iconic_www_1x_t);u8g2.print("H");
        } while( u8g2.nextPage() );
        
      }
      delay(50);
      break;
  }
  
  for(int i=0; i<8; i++)
    lastMotor[i] = currentMotor[i];//현재 상태 기록
  
}//degreeChanged()
*/
