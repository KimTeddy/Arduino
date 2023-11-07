#include <ESP8266WiFi.h> // ESP 8266 와이파이 라이브러리
#include <ESP8266HTTPClient.h> // HTTP 클라이언트

//#define BUTTON 0
//#define LED 16
//oled
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
//time
#include <NTPClient.h>
#include <WiFiUdp.h>
//버튼
//bool currentButton= HIGH, lastButton=HIGH;
//setup시작할때 
bool Setup = LOW;
//oled
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 0, /* data=*/ 2, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather M0 Basic Proto + FeatherWing OLED

//time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600*9, 60000);
//html
String key = "QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D";
String url_bus = "http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoArvlPrearngeInfoList?serviceKey=" + key + "&cityCode=36030&nodeId=SCB326010374";
//bus http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoArvlPrearngeInfoList?serviceKey=QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D&cityCode=36030&nodeId=SCB326010374

//시간
int currentDay, currentHour, currentMinute, currentSecond = 0;
//const char *Day[7] = {"일","월","화","수","목","금","토"};
//String date;
//버스
int resultCode, totalCount, arrprevstationcnt, arrtime, nodenm, routeno = 0;
//updating
int busUpdateSecond = 20;
boolean updateBus = false;
//절전 모드
/*
unsigned long nowTime=0; // 현재 시간을 저장
unsigned long pastTime=0; // 과거 시간 저장 변수
bool powerSaveMode = LOW; // 과거 기준 시간 보다 500ms 이상 지날 경우를 판단하는 flag
*/
//함수
//void GetButton();
void Connecting();
//void OLED_Time();
void OLED_Bus();

int getNumber(String str, String tag, int from);
String getStr(String str, String tag, int from);

void setup()
{
  //pinMode (BUTTON, INPUT_PULLUP);
  //pinMode (LED, OUTPUT);
  // 시리얼 세팅
  Serial.begin(115200);
  Serial.println();
  //oled
  u8g2.begin();
  u8g2.enableUTF8Print();   // enable UTF8 support for the Arduino print() function
  u8g2.setFontDirection(0);
  // 와이파이 접속
  WiFi.begin("Home", "yhsj2021"); // 공유기 이름과 비밀번호

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) // 와이파이 접속하는 동안 "." 출력
  {
    delay(500);
    Serial.print(".");
    Connecting();
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); // 접속된 와이파이 주소 출력

  //time
  timeClient.begin();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) // 와이파이가 접속되어 있는 경우
  {
/*******************************INPUT*******************************/
    //GetButton();

    WiFiClient client; // 와이파이 클라이언트 객체
    HTTPClient http_bus;


/********************************TIME********************************/
      timeClient.update();
      currentDay = timeClient.getDay();
      currentHour = timeClient.getHours();
      currentMinute = timeClient.getMinutes();
      currentSecond = timeClient.getSeconds();

/*******************************RESULTS*******************************/
/********************************bus station********************************/
        if(Setup==0){currentSecond=0;Setup=1;Serial.println("Setup = 1");}
        if(totalCount==0) 
        {  busUpdateSecond = 120;}
        else 
        {  busUpdateSecond = 15;}
        if(currentHour>=6&&currentHour<22 && currentSecond%busUpdateSecond==0) //6시부터 22시 전까지 15초마다 최신화
        {
          updateBus = true;
          int from_bus=0;
          if (http_bus.begin(client, url_bus))
          {  // HTTP
            // 서버에 연결하고 HTTP 헤더 전송
            int httpCode_bus = http_bus.GET();
      
            // httpCode 가 음수라면 에러
            if (httpCode_bus > 0)
            { // 에러가 없는 경우
              if (httpCode_bus == HTTP_CODE_OK || httpCode_bus == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String payload = http_bus.getString(); // 받은 XML 데이터를 String에 저장
                
                resultCode = getNumber(payload, "<resultCode>", payload.indexOf("<resultCode>")); // 결과 메세지 코드
                from_bus = payload.indexOf("<body>");
                totalCount = getNumber(payload, "<totalCount>", from_bus); // 운행버스 수
                Serial.print("totalCount=");Serial.println(totalCount);
                Serial.println("Bus update");
                if(totalCount!=0)
                {
                  arrprevstationcnt = getNumber(payload, "<arrprevstationcnt>", from_bus); // 번째 전
                  arrtime = getNumber(payload, "<arrtime>", from_bus); // 남은시간
                  nodenm = getNumber(payload, "<nodenm>", from_bus); // 정류장 이름
                  routeno = getNumber(payload, "<routeno>", from_bus); // 버스번호
                  //Serial.println(arrprevstationcnt);
                  //Serial.println(arrtime);
                  //Serial.println(nodenm);
                  //Serial.println(routeno);
                }
              }
            }
            else {Serial.printf("[HTTP] GET... bus station실패, 에러코드: %s\n", http_bus.errorToString(httpCode_bus).c_str());Connecting();}
            http_bus.end();
          }
          else {Serial.printf("[HTTP] 접속 불가\n");}
        }
        else {updateBus = false;}//버스 정보 최신화
  OLED_Bus();

  }//end of wifi connect
  else Connecting();
}//end of loop

/*************************************************************************/
/********************************FUNCTIONS********************************/
/*************************************************************************

void GetButton()//버튼 신호 감지
{
  currentButton = digitalRead(BUTTON);
  if(lastButton == HIGH &&currentButton == LOW)//버튼 신호가 1에서 0으로 떨어졌을 때
  {
    Setup = 0;
    pastTime = nowTime;
    powerSaveMode = !powerSaveMode;// powerSaveMode 를 토글
    digitalWrite(LED, HIGH);//현재 상태 출력
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
    digitalWrite(LED, LOW);//현재 상태 출력
  }
  else
  {
    
  }
  lastButton = currentButton;//현재 상태 기록
  
}

//oled
********************************OLED_Connecting********************************/
void Connecting()//인터넷 끊겼을 때 연결중 상태 표시
{
  u8g2.clearBuffer();
  u8g2.firstPage();
  do { 
  u8g2.setCursor(115, 10);u8g2.setFont(u8g2_font_open_iconic_www_1x_t);u8g2.print("H");
  } while ( u8g2.nextPage() );
}

/********************************OLED_Time********************************
void OLED_Time(){//시간 표시
  char currentH[3], currentM[3];//시간, 분, 날짜 표시용 변수
  if(currentHour<10)//10의자리 0 넣기
    sprintf(currentH, "0%d", currentHour);
  else
    sprintf(currentH, "%d", currentHour);
  if(currentMinute<10)//1의자리 0 넣기
    sprintf(currentM, "0%d", currentMinute);
  else
    sprintf(currentM, "%d", currentMinute);
  
  u8g2.clearBuffer();
  u8g2.firstPage();
  do { 
    if(powerSaveMode == 0)//날짜, 시간, 선택 모두 표시
    {
      
      char Date[22];
      u8g2.setFont(u8g2_font_unifont_t_korean1);
      sprintf(Date, "%s월 %s일 %s요일", date.substring(5, 7), date.substring(8, 10), Day[currentDay]);
      Serial.println(Date);
      u8g2.setCursor(0,15);u8g2.print(Date);//날짜 출력
    }
    u8g2.setFont(u8g2_font_cardimon_pixel_tn);
    u8g2.drawStr(20,45,currentH);//시간 출력
    
    u8g2.drawStr(80,45,currentM);//분 출력
    u8g2.setCursor(64,42);u8g2.print(":");// : 출력
    
  } while ( u8g2.nextPage() );
}
********************************OLED_Bus********************************/
void OLED_Bus()//버스 정보 표시
{
  char busNum[3], remainStation[3], remainTime[6];//버스번호, 남은 정류장 수, 남은 시간
  char arrMinute[3], arrSecond[3];//시간, 분 표시용 변수
  if(totalCount!=0)//버스 수가 0이 아닐 때
  {
        
    if((arrtime%60)<10)//1의자리 0 넣기
      sprintf(arrSecond, "0%d", arrtime%60);
    else
      sprintf(arrSecond, "%d", arrtime%60);
      
    sprintf(busNum, "%d", routeno);//버스번호 받기
    sprintf(remainStation, "%d", arrprevstationcnt);//남은 정류장 수 받기
    sprintf(remainTime, "%s:%s", arrtime/60, arrSecond);//남은 시간 받기
  }
  u8g2.clearBuffer();
  u8g2.firstPage();
  do
  {
    if(updateBus==true)u8g2.setCursor(115, 32);u8g2.setFont(u8g2_font_open_iconic_www_1x_t);u8g2.print("H");//업데이트 표시
    
    if(totalCount!=0&&currentHour>=6&&currentHour<22)
    {
      u8g2.setFont(u8g2_font_VCR_OSD_tn);
      u8g2.setCursor(4, 32);u8g2.print(busNum);//버스번호 출력
      u8g2.setCursor(42,32);u8g2.print(remainStation);//남은 정류장 수 출력
      u8g2.setCursor(64,32);u8g2.print(remainTime);//남은 시간 출력
    }
    
    u8g2.setFont(u8g2_font_unifont_t_korean1);
    if(totalCount>0)//버스 수가 0보다 클 때
    {u8g2.setCursor(0,13);u8g2.print("번호|전|예정분초");}//표시
    else
    {
      if(resultCode == 99)//오청 횟수 제한인 트레픽을 초과했을 때
      {  u8g2.setCursor(0,13);u8g2.print("요청 제한 초과!");}//요청 제한 초과! 표시
      else//아닐 때
      {  
        if(currentHour>=6&&currentHour<22)//6시부터 22시 전일 때
        {u8g2.setCursor(0,13);u8g2.print("운행중 버스 없음");}//운행중 버스 없음 표시
        else//버스 운행 끝났을 때
        {u8g2.setCursor(0,13);u8g2.print("버스 운행 종료");}//버스 운행 종료 표시
      }
    }
    
    
  } while ( u8g2.nextPage() );
}

/********************************FIND********************************/
int getNumber(String str, String tag, int from)//str xml데이터에서 from부터 tag를 찾아서 >이후 < 이전까지 int 형태로 반환
{
  float num = -1;
  int f = str.indexOf(tag, from) + tag.length();
  int t = str.indexOf("<", f);
  String s = str.substring(f, t);
  return s.toInt();
}

String getStr(String str, String tag, int from)//str xml데이터에서 from부터 tag를 찾아서 >이후 < 이전까지 string 형태로 반환
{
  float num = -1;
  int f = str.indexOf(tag, from) + tag.length();
  int t = str.indexOf("<", f);
  String s = str.substring(f, t);
  return s;
}
