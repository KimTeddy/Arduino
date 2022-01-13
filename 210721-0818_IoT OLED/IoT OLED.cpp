/*
 * ESP8266 강좌 시리즈
 * 미제먼지 데이터 받아오기 2편
 * 
 * 본 저작물은 '한국환경공단'에서 실시간 제공하는 '한국환경공단_대기오염정보'를 이용하였습니다.
 * https://www.data.go.kr/dataset/15000581/openapi.do
 */
#include <ESP8266WiFi.h> // ESP 8266 와이파이 라이브러리
#include <ESP8266HTTPClient.h> // HTTP 클라이언트

//oled
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
//time
#include <NTPClient.h>
#include <WiFiUdp.h>

#define CLOUDY "@"
#define LITTLE "A"
#define MOON "B"
#define RAINY "C"
#define SUNNY "E"

#define TIME 0
#define WEATH 1
#define BUS 2
#define CONNECT 3

//로터리 인코더
#define S1 5
#define S2 4
#define BUTTON 0
//릴레이
#define RELAY 16
//로터리 인코더
int count = 0; 
bool currentS1;
bool previousS1; 
//릴레이
bool currentButton= HIGH, lastButton=HIGH, lightOnOff = HIGH;
//setup시작할때 
bool Setup[2]={LOW};
//oled
U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=D8 */ 15, /* dc=D4 */ 2, /* reset=D0 */ 12);/* MOSI=D7 *//* CLK=D5 */
//time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600*9, 60000);
//html
String key = "QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D";
String url_dust = "http://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?serviceKey=" + key + "&returnType=xml&numOfRows=1&pageNo=1&stationName=%EC%97%B0%ED%96%A5%EB%8F%99&dataTerm=DAILY&ver=1.0";
//http://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?serviceKey=QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D&returnType=xml&numOfRows=1&pageNo=1&stationName=%EC%97%B0%ED%96%A5%EB%8F%99&dataTerm=DAILY&ver=1.0
String url_weth = "http://apis.data.go.kr/1360000/VilageFcstMsgService/getLandFcst?serviceKey=" + key + "&pageNo=1&numOfRows=4&dataType=XML&regId=11F20405";
//http://apis.data.go.kr/1360000/VilageFcstMsgService/getLandFcst?serviceKey=QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D&pageNo=1&numOfRows=2&dataType=XML&regId=11F20405
String url_bus = "http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoArvlPrearngeInfoList?serviceKey=" + key + "&cityCode=36030&nodeId=SCB326010374";
//bus http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoArvlPrearngeInfoList?serviceKey=QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D&cityCode=36030&nodeId=SCB326010374
//temp/humid  http://apis.data.go.kr/6460000/weeklyForecast/getWeeklyForecastList?serviceKey=QQJSOR%2FDsuJbCf%2Fg5g%2Bhy0k9Ky0XzE%2B%2B%2BZyUGwlhGMMHKn05ogwg8pmGFosr6WIReKoUOfFnifKePHhzM2jQjg%3D%3D&pageSize=1&startPage=1
//미세먼지 , 초미세먼지
int pm10Num, pm25Num = 0; // 미세먼지, 초미세먼지 정도
const char *Grade[5] = {"정보없음","좋음","보통","심함","매우심함"};

//날씨
int humidity, temperature, rain_percent, rain_form_num, weath = 0; 
String weather;
const char *weather_icon[5] = {SUNNY,LITTLE,CLOUDY,RAINY,MOON};
const char *Rain_form[5] = {"(비 소식X)","(비)","(비 또는 눈)","(눈)","(소나기)"};
//시간
int currentDay, currentHour, currentMinute, currentSecond = 0;
const char *Day[7] = {"일","월","화","수","목","금","토"};
String date;
//버스
int resultCode, totalCount, arrprevstationcnt, arrtime, nodenm, routeno = 0;
//updating
int busUpdateSecond = 20;
bool updateWeath, updateBus = LOW;
//절전 모드
unsigned long nowTime=0; // 현재 시간을 저장
unsigned long pastTime=0; // 과거 시간 저장 변수
bool powerSaveMode = LOW; // 과거 기준 시간 보다 500ms 이상 지날 경우를 판단하는 flag

//함수
void GetButton();
void GetLottery();
void Connecting();
void OLED_Time();
void OLED_Weather();
void OLED_Bus();

void Select(int select, bool updating);
int getNumber(String str, String tag, int from);
String getStr(String str, String tag, int from);

void setup()
{
  //로터리 인코더
  pinMode (S1,INPUT);
  pinMode (S2,INPUT);
  pinMode (BUTTON, INPUT_PULLUP);
  pinMode (RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  previousS1= digitalRead(S1);
  
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
    WiFiClient client; // 와이파이 클라이언트 객체
    HTTPClient http_dust; // HTTP 클라이언트 객체
    HTTPClient http_weth;
    HTTPClient http_bus;
/********************************TIME********************************/
    timeClient.update();
    currentDay = timeClient.getDay();
    currentHour = timeClient.getHours();
    currentMinute = timeClient.getMinutes();
    currentSecond = timeClient.getSeconds();
/*******************************POWER SAVE MODE*******************************/
    if(powerSaveMode == LOW)
    {
      nowTime = millis(); // 현재 시간을 저장
    
      // 현재 시간이 과거 시간보다 20분 지났을 때
      // 과거 시간에 현재 시간을 저장
      // 20분이 지났음을 알려 주는 powerSaveMode 를 1로 활성화
      Serial.println(nowTime - pastTime);
      if(nowTime - pastTime >= (60000)*20)
      { //20분 지나면
        powerSaveMode = HIGH;//절전모드 활성화
      }
    }
/*******************************INPUT*******************************/
    GetButton();
    GetLottery();
/*******************************RESULTS*******************************/
    if(powerSaveMode == LOW)
    {
    //oled
      switch(count)
      {
  case -2:
  
    OLED_Time();
    Setup[0]=0;
  break;
  case -1:
  case 0:
       /******************************FINE_DUST******************************/
        if(Setup[0]==0){currentMinute=0;currentSecond=0;Setup[0]=1;Serial.println("Setup[0] = 1");}
        
        if(currentMinute%30==0&&currentSecond==0)
        {
          updateWeath = 1;
          if (http_dust.begin(client, url_dust))
          {  // HTTP
            // 서버에 연결하고 HTTP 헤더 전송
            int httpCode_dust = http_dust.GET();
      
            // httpCode 가 음수라면 에러
            if (httpCode_dust > 0)
            { // 에러가 없는 경우
              if (httpCode_dust == HTTP_CODE_OK || httpCode_dust == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String payload = http_dust.getString(); // 받은 XML 데이터를 String에 저장
                int from = payload.indexOf("NORMAL_CODE");
                pm10Num = getNumber(payload, "<pm10Grade>", from); // 미세먼지 등급 값
                pm25Num = getNumber(payload, "<pm25Grade>", from); // 초미세먼지 등급 값
                date = getStr(payload, "<dataTime>", from);//날짜
                Serial.println("Dust update");
              }
              if(pm10Num==1||pm10Num==2||pm10Num==3||pm10Num==4); else pm10Num = 0;
              if(pm25Num==1||pm25Num==2||pm25Num==3||pm25Num==4); else pm25Num = 0;
            }
            else {Serial.printf("[HTTP] GET... 실패, 에러코드: %s\n", http_dust.errorToString(httpCode_dust).c_str());Connecting();}
            http_dust.end();
          }
          else {Serial.printf("[HTTP] 접속 불가\n");}
        }
        else {updateWeath = 0;}
        /*******************************WEATHER*******************************/
        if(currentMinute%20==0&&currentSecond==0)
        {
          updateWeath = 1;
          if (http_weth.begin(client, url_weth))
          {  // HTTP
            // 서버에 연결하고 HTTP 헤더 전송
            int httpCode_weth = http_weth.GET();
      
            // httpCode 가 음수라면 에러
            if (httpCode_weth > 0)
            { // 에러가 없는 경우
              if (httpCode_weth == HTTP_CODE_OK || httpCode_weth == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String payload = http_weth.getString(); // 받은 XML 데이터를 String에 저장
                int from = payload.indexOf("11F20405");
                temperature = getNumber(payload, "<ta>", from); // 예상기온(℃)
                rain_percent = getNumber(payload, "<rnSt>", from); // 강수확률
                weather = getStr(payload, "<wf>", from); // 날씨
                rain_form_num = getNumber(payload, "<rnYn>", from); // 강수형태
                Serial.println("Weather update");
              }
              if(rain_form_num != 0)
              weather = "비";
              
              if(weather=="맑음")
              {
                weath = 0; 
                if(currentHour>20||currentHour<4) weath = 4;
              }
              else if(weather=="구름많음") weath = 1;
              else if(weather=="흐림") weath = 2;
              else weath = 3; 
            }
            else {Serial.printf("[HTTP] GET... 실패, 에러코드: %s\n", http_weth.errorToString(httpCode_weth).c_str());Connecting();}
            http_weth.end();
          }
          else {Serial.printf("[HTTP] 접속 불가\n");}
        }
        else {updateWeath = 0;}
        //Serial.println(weath);
    OLED_Weather();
    Setup[1]=0;
  break;
  case 1:
  case 2:
  Setup[0]=0;
  /********************************bus station********************************/
        if(Setup[1]==0){currentSecond=0;Setup[1]=1;Serial.println("Setup[1] = 1");}
        if(totalCount==0) 
        {  busUpdateSecond = 30;}
        else 
        {  busUpdateSecond = 15;}
        if(currentHour>=6&&currentHour<22 && currentSecond%busUpdateSecond==0) //6시부터 22시 전까지 15초마다 최신화
        {
          updateBus=1;
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
        else {updateBus = 0;}//버스 정보 최신화
  OLED_Bus();
  break;
      }//end of switch
    }//end of power save mode == 0
    else
    {
      
      OLED_Time();
    }
  }//end of wifi connect
    else Connecting();
}//end of loop

/*************************************************************************/
/********************************FUNCTIONS********************************/
/*************************************************************************/
void GetButton()//전등 버튼 신호 감지
{
  currentButton = digitalRead(BUTTON);
  //Serial.println(lastButton);
   // Serial.println(currentButton);
  if(lastButton == HIGH &&currentButton == LOW)//버튼 신호가 1에서 0으로 떨어졌을 때
  {
    lightOnOff = !lightOnOff; //전등 상태 토글
    Serial.println(lightOnOff);
  }
  lastButton = currentButton;//현재 상태 기록
  digitalWrite(RELAY, lightOnOff);//현재 상태 출력
}

void GetLottery()//로터리 인코더 감지
{
  currentS1 = digitalRead(S1);   
  if (currentS1 != previousS1)
  { 
    if (digitalRead(S2) != currentS1)//s1과 s2신호가 다르면
    { count --;}//카운트 1 감소
    else  //s1과 s2신호가 같으면
    { count ++;}//카운트 1 증가
    if (count<-2)count=-2;//카운트가 -2 이하로 떨어지지 않게 함
    if (count>2)count=2;//카운트가 +2 이상으로 올라가지 않게 함
    Serial.print(" count = ");
    Serial.println(count);
    
    powerSaveMode = 0;// powerSaveMode 를 0으로 초기화
    pastTime = nowTime;
    powerSaveMode=LOW;
  }
  previousS1 = currentS1; //현재상태 기록
}

//oled
/********************************OLED_Connecting********************************/
void Connecting()//인터넷 끊겼을 때 연결중 상태 표시
{
  u8g2.clearBuffer();
  u8g2.firstPage();
  do { 
  Select(CONNECT, 0);
  } while ( u8g2.nextPage() );
}

/********************************OLED_Time********************************/
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
      Select(TIME, 1);//시간 선택 표시
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

/********************************OLED_Weather********************************/
void OLED_Weather(){//날씨, 대기질 표시
  char temper[10], rain[10];//온도, 비 정보
  
  u8g2.clearBuffer();
  u8g2.firstPage();
  do {
    Select(WEATH,updateWeath);//날씨 선택 표시
    u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
    u8g2.drawStr(0,33,weather_icon[weath]);//날씨 아이콘 표시
    if(temperature!=0)//온도
    {
      u8g2.setFont(u8g2_font_calibration_gothic_nbp_tf);
      sprintf(temper, "%dºc", temperature);//온도정보 받기
      u8g2.setCursor(35,15);u8g2.print(temper);//온도 출력
    }
    u8g2.setFont(u8g2_font_unifont_t_korean1);
    u8g2.setCursor(65,13);u8g2.print(Grade[pm10Num]);//미세먼지 출력
    u8g2.setCursor(65,30);u8g2.print(Grade[pm25Num]);//초미세먼지 출력
    sprintf(rain, "%d%% %s", rain_percent, Rain_form[rain_form_num]);//비 올 확률과 종류 등 비 정보 받기
    u8g2.setCursor(0, 47);u8g2.print(rain);//비 정보 출력
  } while ( u8g2.nextPage() );
}

/********************************OLED_Bus********************************/
void OLED_Bus()//버스 정보 표시
{
  char busNum[3], remainStation[3], remainTime[6];//버스번호, 남은 정류장 수, 남은 시간
  if(totalCount!=0)//버스 수가 0이 아닐 때
  {
    sprintf(busNum, "%d", routeno);//버스번호 받기
    sprintf(remainStation, "%d", arrprevstationcnt);//남은 정류장 수 받기
    sprintf(remainTime, "%d:%d", arrtime/60, arrtime%60);//남은 시간 받기
  }
  u8g2.clearBuffer();
  u8g2.firstPage();
  do
  {
    Select(BUS, updateBus);//버스 선택 표시
    if(totalCount!=0&&currentHour>=6&&currentHour<22)
    {
      u8g2.setFont(u8g2_font_VCR_OSD_tn);
      u8g2.setCursor(4, 32);u8g2.print(busNum);//버스번호 출력
      u8g2.setCursor(42,32);u8g2.print(remainStation);//남은 정류장 수 출력
      u8g2.setCursor(74,32);u8g2.print(remainTime);//남은 시간 출력
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

/********************************OLED_Select********************************/
void Select(int select, bool updating)//메뉴 선택 표시
{
  u8g2.drawLine(0,50,128,50);//선 그리기
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.setCursor(6, 62);u8g2.print("TIME");//시간메뉴
  u8g2.setCursor(40,62);u8g2.print("WEATH");//날씨 메뉴
  u8g2.setCursor(82,62);u8g2.print("BUS");//버스 메뉴
  
  u8g2.setFont(u8g2_font_t0_11b_tf);
  switch(select)//선택시 볼드체/네모 표시
  {
    case 0: u8g2.setCursor(6, 62);u8g2.print("TIME");  u8g2.drawRFrame(0,52,37,12,2); break;
    case 1: u8g2.setCursor(40, 62);u8g2.print("WEATH");u8g2.drawRFrame(36,52,37,12,2); break;
    case 2: u8g2.setCursor(82, 62);u8g2.print("BUS");  u8g2.drawRFrame(72,52,37,12,2); break;
    case 3: u8g2.setCursor(115, 62);u8g2.setFont(u8g2_font_open_iconic_www_1x_t);u8g2.print("H"); break;//CONNECTTING
  } 
  if(updating==1){u8g2.setCursor(115, 62);u8g2.setFont(u8g2_font_open_iconic_www_1x_t);u8g2.print("H");}//최신화중일 때 와이파이 표시
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
