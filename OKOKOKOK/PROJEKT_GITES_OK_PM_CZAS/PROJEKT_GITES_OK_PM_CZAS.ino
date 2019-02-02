//#include <WidgetRTC.h>
#include <Timers.h>


Timer glowny;
Timer sekunda;
Timer sekunddwie;
Timer blynkMiganie;
Timer czujniki;
Timer blynkConnect;
Timer alarm_led;

//BlynkTimer timer;
unsigned long cMillisGlowny;
unsigned long pMillisGlowny=0;



#include <Adafruit_NeoPixel.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include "RTClib.h"
#include "i2c.h"
#include "i2c_BMP280.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include "DHT.h"
LiquidCrystal_I2C lcd(0x27,20,4);  // Ustawienie adresu ukladu na 0x27
RTC_DS1307 czas;
Adafruit_NeoPixel LED = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800);

BMP280 bmp280;
Adafruit_BMP280 bme;
int temperatura_bmp_piwnica;
int temperatura_bmp_piwnica_max, temperatura_bmp_piwnica_min;
int dzien_temperatura_bmp_piwnica_min, miesiac_temperatura_bmp_piwnica_min, rok_temperatura_bmp_piwnica_min;
int dzien_temperatura_bmp_piwnica_max, miesiac_temperatura_bmp_piwnica_max, rok_temperatura_bmp_piwnica_max;
int cisnienie_bmp_strych;
int cisnienie_bmp_strych_max, cisnienie_bmp_strych_min;
int dzien_cisnienie_bmp_strych_min, miesiac_cisnienie_bmp_strych_min, rok_cisnienie_bmp_strych_min;
int dzien_cisnienie_bmp_strych_max, miesiac_cisnienie_bmp_strych_max, rok_cisnienie_bmp_strych_max;

OneWire oneWire(A5);
DallasTemperature sensors(&oneWire); 
DeviceAddress termometr_strych = {0x28, 0xB, 0xA6, 0x40, 0x5, 0x0, 0x0, 0x9C};
DeviceAddress termometr_slonce = {0x28, 0x56, 0x4F, 0xEE, 0x9, 0x0, 0x0, 0xD6};
DeviceAddress termometr_grunt = {0x28, 0xC4, 0x85, 0x40, 0x5, 0x0, 0x0, 0x91};
DeviceAddress termometr_CO = {0x28, 0xAC, 0x74, 0x40, 0x5, 0x0, 0x0, 0x98};
//#define termometr_one_wire A5

int temp_strych, temp_strych_max, temp_strych_min;
int dzien_temp_strych_max, miesiac_temp_strych_max, rok_temp_strych_max;
int dzien_temp_strych_min, miesiac_temp_strych_min, rok_temp_strych_min;


int temp_slonce, temp_slonce_max, temp_slonce_min;
int dzien_temp_slonce_max, miesiac_temp_slonce_max, rok_temp_slonce_max;
int dzien_temp_slonce_min, miesiac_temp_slonce_min, rok_temp_slonce_min;

int temp_grunt, temp_grunt_max, temp_grunt_min;
int dzien_temp_grunt_max, miesiac_temp_grunt_max, rok_temp_grunt_max;
int dzien_temp_grunt_min, miesiac_temp_grunt_min, rok_temp_grunt_min;

int temp_CO, temp_CO_max, temp_CO_min;
int dzien_temp_CO_max, miesiac_temp_CO_max, rok_temp_CO_max;
int dzien_temp_CO_min, miesiac_temp_CO_min, rok_temp_CO_min;

#define DHTPIN1 8    
#define DHTPIN2 7 
#define DHTTYPE1 DHT11   // DHT 11
#define DHTTYPE2 DHT22 
DHT dht_wew(DHTPIN1, DHTTYPE1);
DHT dht_zew(DHTPIN2, DHTTYPE2);

int temperatura_dht_kuchnia, wilgotnosc_dht_kuchnia;
int temperatura_dht_kuchnia_max, temperatura_dht_kuchnia_min, wilgotnosc_dht_kuchnia_max, wilgotnosc_dht_kuchnia_min;
int dzien_temperatura_dht_kuchnia_min, miesiac_temperatura_dht_kuchnia_min, rok_temperatura_dht_kuchnia_min;
int dzien_temperatura_dht_kuchnia_max, miesiac_temperatura_dht_kuchnia_max, rok_temperatura_dht_kuchnia_max;
int dzien_wilgotnosc_dht_kuchnia_min, miesiac_wilgotnosc_dht_kuchnia_min, rok_wilgotnosc_dht_kuchnia_min;
int dzien_wilgotnosc_dht_kuchnia_max, miesiac_wilgotnosc_dht_kuchnia_max, rok_wilgotnosc_dht_kuchnia_max;

int temperatura_dht_zew, wilgotnosc_dht_zew;
int temperatura_dht_zew_max, temperatura_dht_zew_min, wilgotnosc_dht_zew_max, wilgotnosc_dht_zew_min;
int dzien_temperatura_dht_zew_min, miesiac_temperatura_dht_zew_min, rok_temperatura_dht_zew_min;
int dzien_temperatura_dht_zew_max, miesiac_temperatura_dht_zew_max, rok_temperatura_dht_zew_max;
int dzien_wilgotnosc_dht_zew_min, miesiac_wilgotnosc_dht_zew_min, rok_wilgotnosc_dht_zew_min;
int dzien_wilgotnosc_dht_zew_max, miesiac_wilgotnosc_dht_zew_max, rok_wilgotnosc_dht_zew_max;

#define PinA 2  
#define PinB 3  
#define PinP 53

#define treconnect 30
int liczreconnect = 10;

unsigned long time = 0; 
unsigned long time1 = 0;
unsigned long time_przekaznika = 0;
unsigned long cMillisGaraz;
unsigned long pMillisGaraz=0;
unsigned long cMillisFurtka;
unsigned long pMillisFurtka=0;
long licznik = 1;  
int pozycja_markera=1;
int pozycja_markera_poprzednia=1;
int liczba_pozycji_menu=11;
int poprzedni_button_brama_garaz = 0;
int poprzedni_button_furtka = 0;
int poprzedni_brama_garaz;
int poprzedni_lampa_plac;
int poprzedni_lampa_ogrod;
int poprzedni_furtka;
int poprzedni_dodatkowy1;
int poprzedni_dodatkowy2;
int poprzedni_dodatkowy3;
int poprzedni_dodatkowy4;

boolean lampa_plac_enkoder = false;
boolean lampa_ogrod_enkoder = false;
boolean furtka_enkoder = false;
boolean dodatkowy1_enkoder = false;
boolean dodatkowy2_enkoder = false;
boolean dodatkowy3_enkoder = false;
boolean dodatkowy4_enkoder = false;

boolean lampa_plac = false;
boolean lampa_ogrod = false;
boolean brama_garaz;
boolean praca_brama_garaz = false;
boolean furtka = false;
boolean furtka_przycisk = false;
boolean dodatkowy1 = false;
boolean dodatkowy2 = false;
boolean dodatkowy3 = false;
boolean dodatkowy4 = false;
boolean wylaczono_alarm_deszcz=false;
boolean wylaczono_alarm_pralka=false;
boolean alarm_wlaczony=false;
unsigned long napiecie_pralka = 80;
boolean alarm_on = false;

#define lampa_plac_przekaznik 27
#define lampa_plac_wlacznik 22
#define lampa_ogrod_przekaznik 29
#define lampa_ogrod_wlacznik 24
#define brama_garaz_krancowka 28
#define brama_garaz_przekaznik 23
#define furtka_przekaznik 25
#define furtka_wlacznik 26
#define dodatkowy1_przekaznik 31
#define dodatkowy1_wlacznik 30
#define dodatkowy2_przekaznik 33
#define dodatkowy2_wlacznik 32
#define dodatkowy3_przekaznik 35
#define dodatkowy3_wlacznik 34
#define dodatkowy4_przekaznik 37
#define dodatkowy4_wlacznik 36
#define pin_alarm_pralka 45
#define pin_alarm_deszcz 46
#define buzzer A15

enum PIERWSZE {JEDEN=1,DWA,TRZY,CZTERY,PIEC,SZESC,SIEDEM,OSIEM,DZIEWIEC,DZIESIEC,JEDENASCIE,DWANASCIE};
int menu_1=JEDEN;
const long scroll_speed = 300;
unsigned long cMillis;
unsigned long cMillis1;
unsigned long pMillis = 0; 
unsigned long pMillis1 = 0; 
unsigned long cMillisOpcje;
unsigned long pMillisOpcje = 0;
unsigned long czekanie = 60000;
char auth[] = "4fc87431c0ec4c1e90778d8c5765b1c8";

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"
#define _RED            "#FF0000"
#define _GREEN          "#00FF00"

int button_lampa_plac = 0;
int button_lampa_ogrod = 0;
int button_brama_garaz = 0;
int button_furtka = 0;
int button_dodatkowy1 = 0;
int button_dodatkowy2 = 0;
int button_dodatkowy3 = 0;
int button_dodatkowy4 = 0;
WidgetLED led1(V0);
WidgetLED led2(V25);
int blueLED = 0; 
int blynk_menu;
int button_reset;
int blynk_alarm_deszcz;
int blynk_alarm_pralka;
boolean smsPralka = false;
boolean smsDeszcz = false;
boolean smsBramaOtwarta = false;
boolean smsBramaZamknieta = false;
//WidgetRTC rtc;
//String currentTime = String(hour()) + ":" + minute() + ":" + second();
//String currentDate = String(day()) + "." + month() + "." + year(); 
int PM1;
int PM25;
int PM10;
int minPM1,maxPM1,minPM25,maxPM25,minPM10,maxPM10;
int dzien_PM1_min,dzien_PM1_max,miesiac_PM1_min,miesiac_PM1_max,rok_PM1_min,rok_PM1_max;
int dzien_PM25_min,dzien_PM25_max,miesiac_PM25_min,miesiac_PM25_max,rok_PM25_min,rok_PM25_max;
int dzien_PM10_min,dzien_PM10_max,miesiac_PM10_min,miesiac_PM10_max,rok_PM10_min,rok_PM10_max;

BLYNK_WRITE(V4){
  button_reset = param.asInt();
  if(button_reset = 1){
    switch(blynk_menu){
  case 1:{
    DateTime now = czas.now();
    temperatura_dht_kuchnia=dht_wew.readTemperature();
    temperatura_dht_kuchnia_min=temperatura_dht_kuchnia;
    dzien_temperatura_dht_kuchnia_min = now.day();
    miesiac_temperatura_dht_kuchnia_min = now.month();
    rok_temperatura_dht_kuchnia_min = now.year();
    temperatura_dht_kuchnia_max=temperatura_dht_kuchnia;
    dzien_temperatura_dht_kuchnia_max = now.day();
    miesiac_temperatura_dht_kuchnia_max = now.month();
    rok_temperatura_dht_kuchnia_max = now.year();
   break;
  }
  case 2:{
    DateTime now = czas.now();
    wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
    wilgotnosc_dht_kuchnia_min=wilgotnosc_dht_kuchnia;
    dzien_wilgotnosc_dht_kuchnia_min = now.day();
    miesiac_wilgotnosc_dht_kuchnia_min = now.month();
    rok_wilgotnosc_dht_kuchnia_min = now.year();
    wilgotnosc_dht_kuchnia_max=wilgotnosc_dht_kuchnia;
    dzien_wilgotnosc_dht_kuchnia_max = now.day();
    miesiac_wilgotnosc_dht_kuchnia_max = now.month();
    rok_wilgotnosc_dht_kuchnia_max = now.year();
   break;
  }
  case 3:{
    DateTime now = czas.now();
    cisnienie_bmp_strych=bme.readPressure()/100;
    cisnienie_bmp_strych_min=cisnienie_bmp_strych;
    dzien_cisnienie_bmp_strych_min = now.day();
    miesiac_cisnienie_bmp_strych_min = now.month();
    rok_cisnienie_bmp_strych_min = now.year();
    cisnienie_bmp_strych_max=cisnienie_bmp_strych;
    dzien_cisnienie_bmp_strych_max = now.day();
    miesiac_cisnienie_bmp_strych_max = now.month();
    rok_cisnienie_bmp_strych_max = now.year();
   break;
  }
  case 4:{
    DateTime now = czas.now();
    temperatura_dht_zew = dht_zew.readTemperature();
    temperatura_dht_zew_min=temperatura_dht_zew;
    dzien_temperatura_dht_zew_min = now.day();
    miesiac_temperatura_dht_zew_min = now.month();
    rok_temperatura_dht_zew_min = now.year();
    temperatura_dht_zew_max=temperatura_dht_zew;
    dzien_temperatura_dht_zew_max = now.day();
    miesiac_temperatura_dht_zew_max = now.month();
    rok_temperatura_dht_zew_max = now.year();
   break;
  }
  case 5:{
    DateTime now = czas.now();
    wilgotnosc_dht_zew = dht_zew.readHumidity();
    wilgotnosc_dht_zew_min = wilgotnosc_dht_zew;
    dzien_wilgotnosc_dht_zew_min = now.day();
    miesiac_wilgotnosc_dht_zew_min = now.month();
    rok_wilgotnosc_dht_zew_min = now.year();
    wilgotnosc_dht_zew_max = wilgotnosc_dht_zew;
    dzien_wilgotnosc_dht_zew_max = now.day();
    miesiac_wilgotnosc_dht_zew_max = now.month();
    rok_wilgotnosc_dht_zew_max = now.year();
   break;
  }
  case 6:{
    DateTime now = czas.now();
    temp_grunt = sensors.getTempC(termometr_grunt);
    temp_grunt_min=temp_grunt;
    dzien_temp_grunt_min = now.day();
    miesiac_temp_grunt_min = now.month();
    rok_temp_grunt_min = now.year();
    temp_grunt_max=temp_grunt;
    dzien_temp_grunt_max = now.day();
    miesiac_temp_grunt_max = now.month();
    rok_temp_grunt_max = now.year();
   break;
  }
  case 7:{
    DateTime now = czas.now();
    temp_slonce = sensors.getTempC(termometr_slonce);
    temp_slonce_min=temp_slonce;
    dzien_temp_slonce_min = now.day();
    miesiac_temp_slonce_min = now.month();
    rok_temp_slonce_min = now.year(); 
    temp_slonce_max=temp_slonce;
    dzien_temp_slonce_max = now.day();
    miesiac_temp_slonce_max = now.month();
    rok_temp_slonce_max = now.year();
   break;
  }
  case 8:{
    DateTime now = czas.now();
    temp_CO = sensors.getTempC(termometr_CO);
    temp_CO_min=temp_CO;
    dzien_temp_CO_min = now.day();
    miesiac_temp_CO_min = now.month();
    rok_temp_CO_min = now.year();
    temp_CO_max=temp_CO;
    dzien_temp_CO_max = now.day();
    miesiac_temp_CO_max = now.month();
    rok_temp_CO_max = now.year();
   break;
  }
  case 9:{
    DateTime now = czas.now();
    sensors.requestTemperatures(); 
    temp_strych = sensors.getTempC(termometr_strych);
    temp_strych_min=temp_strych;
    dzien_temp_strych_min = now.day();
    miesiac_temp_strych_min = now.month();
    rok_temp_strych_min = now.year();
    temp_strych_max=temp_strych;
    dzien_temp_strych_max = now.day();
    miesiac_temp_strych_max = now.month();
    rok_temp_strych_max = now.year();
   break; 
  }
  case 10:{
    DateTime now = czas.now(); 
    temperatura_bmp_piwnica = bme.readTemperature();
    temperatura_bmp_piwnica_min=temperatura_bmp_piwnica;
    dzien_temperatura_bmp_piwnica_min = now.day();
    miesiac_temperatura_bmp_piwnica_min = now.month();
    rok_temperatura_bmp_piwnica_min = now.year();
    temperatura_bmp_piwnica_max=temperatura_bmp_piwnica;
    dzien_temperatura_bmp_piwnica_max = now.day();
    miesiac_temperatura_bmp_piwnica_max = now.month();
    rok_temperatura_bmp_piwnica_max = now.year();
   break;
  }
  case 11:{
    DateTime now = czas.now(); 
    maxPM1 = PM1;
    dzien_PM1_max = now.day();
    miesiac_PM1_max = now.month();
    rok_PM1_max = now.year();
    minPM1 = PM1;
    dzien_PM1_min = now.day();
    miesiac_PM1_min = now.month();
    rok_PM1_min = now.year();
   break;
  }
  case 12:{
    DateTime now = czas.now(); 
    maxPM25 = PM25;
    dzien_PM25_max = now.day();
    miesiac_PM25_max = now.month();
    rok_PM25_max = now.year();
    minPM25 = PM25;
    dzien_PM25_min = now.day();
    miesiac_PM25_min = now.month();
    rok_PM25_min = now.year();
   break;
  }
  case 13:{
    DateTime now = czas.now(); 
    maxPM10 = PM10;
    dzien_PM10_max = now.day();
    miesiac_PM10_max = now.month();
    rok_PM10_max = now.year();
    minPM10 = PM10;
    dzien_PM10_min = now.day();
    miesiac_PM10_min = now.month();
    rok_PM10_min = now.year();
   break;
  }
  }
  }
}

BLYNK_WRITE(V1){
  blynk_menu = param.asInt();
  switch(blynk_menu){
  case 1:{
    Blynk.setProperty(V2, "offLabel", temperatura_dht_kuchnia_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temperatura_dht_kuchnia_min,":", miesiac_temperatura_dht_kuchnia_min,":", rok_temperatura_dht_kuchnia_min);
    Blynk.setProperty(V3, "offLabel", temperatura_dht_kuchnia_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temperatura_dht_kuchnia_max,":", miesiac_temperatura_dht_kuchnia_max,":", rok_temperatura_dht_kuchnia_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break;
  }
  case 2:{
    Blynk.setProperty(V2, "offLabel", wilgotnosc_dht_kuchnia_min, "% RH");
    Blynk.setProperty(V2, "onLabel", dzien_wilgotnosc_dht_kuchnia_min,":", miesiac_wilgotnosc_dht_kuchnia_min,":", rok_wilgotnosc_dht_kuchnia_min);
    Blynk.setProperty(V3, "offLabel", wilgotnosc_dht_kuchnia_max, "% RH");
    Blynk.setProperty(V3, "onLabel", dzien_wilgotnosc_dht_kuchnia_max,":", miesiac_wilgotnosc_dht_kuchnia_max,":", rok_wilgotnosc_dht_kuchnia_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE WILGOTNOSC I DATE");
   break;
  }
  case 3:{
    Blynk.setProperty(V2, "offLabel", cisnienie_bmp_strych_min, "hPa");
    Blynk.setProperty(V2, "onLabel", dzien_cisnienie_bmp_strych_min,":", miesiac_cisnienie_bmp_strych_min,":", rok_cisnienie_bmp_strych_min);
    Blynk.setProperty(V3, "offLabel", cisnienie_bmp_strych_max, "hPa");
    Blynk.setProperty(V3, "onLabel", dzien_cisnienie_bmp_strych_max,":", miesiac_cisnienie_bmp_strych_max,":", rok_cisnienie_bmp_strych_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE CISNIENIE I DATE");
   break;
  }
  case 4:{
    Blynk.setProperty(V2, "offLabel", temperatura_dht_zew_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temperatura_dht_zew_min,":", miesiac_temperatura_dht_zew_min,":", rok_temperatura_dht_zew_min);
    Blynk.setProperty(V3, "offLabel", temperatura_dht_zew_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temperatura_dht_zew_max,":", miesiac_temperatura_dht_zew_max,":", rok_temperatura_dht_zew_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break;
  }
  case 5:{
    Blynk.setProperty(V2, "offLabel", wilgotnosc_dht_zew_min, "% RH");
    Blynk.setProperty(V2, "onLabel", dzien_wilgotnosc_dht_zew_min,":", miesiac_wilgotnosc_dht_zew_min,":", rok_wilgotnosc_dht_zew_min);
    Blynk.setProperty(V3, "offLabel", wilgotnosc_dht_zew_max, "% RH");
    Blynk.setProperty(V3, "onLabel", dzien_wilgotnosc_dht_zew_max,":", miesiac_wilgotnosc_dht_zew_max,":", rok_wilgotnosc_dht_zew_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE WILGOTNOSC I DATE");
   break;
  }
  case 6:{
    Blynk.setProperty(V2, "offLabel", temp_grunt_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temp_grunt_min,":", miesiac_temp_grunt_min,":", rok_temp_grunt_min);
    Blynk.setProperty(V3, "offLabel", temp_grunt_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temp_grunt_max,":", miesiac_temp_grunt_max,":", rok_temp_grunt_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break;
  }
  case 7:{
    Blynk.setProperty(V2, "offLabel", temp_slonce_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temp_slonce_min,":", miesiac_temp_slonce_min,":", rok_temp_slonce_min);
    Blynk.setProperty(V3, "offLabel",temp_slonce_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temp_slonce_max,":", miesiac_temp_slonce_max,":", rok_temp_slonce_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break;
  }
  case 8:{
    Blynk.setProperty(V2, "offLabel", temp_CO_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temp_CO_min,":", miesiac_temp_CO_min,":", rok_temp_CO_min);
    Blynk.setProperty(V3, "offLabel", temp_CO_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temp_CO_max,":", miesiac_temp_CO_max,":", rok_temp_CO_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break;
  }
  case 9:{
    Blynk.setProperty(V2, "offLabel", temp_strych_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temp_strych_min,":", miesiac_temp_strych_min,":", rok_temp_strych_min);
    Blynk.setProperty(V3, "offLabel", temp_strych_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temp_strych_max,":", miesiac_temp_strych_max,":", rok_temp_strych_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break; 
  }
  case 10:{
    Blynk.setProperty(V2, "offLabel", temperatura_bmp_piwnica_min, "*C");
    Blynk.setProperty(V2, "onLabel", dzien_temperatura_bmp_piwnica_min,":", miesiac_temperatura_bmp_piwnica_min,":", rok_temperatura_bmp_piwnica_min);
    Blynk.setProperty(V3, "offLabel", temperatura_bmp_piwnica_max, "*C");
    Blynk.setProperty(V3, "onLabel", dzien_temperatura_bmp_piwnica_max,":", miesiac_temperatura_bmp_piwnica_max,":", rok_temperatura_bmp_piwnica_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE TEMPERATURE I DATE");
   break;
  }
  case 11:{
    Blynk.setProperty(V2, "offLabel", minPM1, "ug/m3");
    Blynk.setProperty(V2, "onLabel", dzien_PM1_min,":", miesiac_PM1_min,":", rok_PM1_min);
    Blynk.setProperty(V3, "offLabel", maxPM1, "ug/m3");
    Blynk.setProperty(V3, "onLabel", dzien_PM1_max,":", miesiac_PM1_max,":", rok_PM1_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE WARTOSC I DATE");
   break;
  }
  case 12:{
    Blynk.setProperty(V2, "offLabel", minPM25, "ug/m3");
    Blynk.setProperty(V2, "onLabel", dzien_PM25_min,":", miesiac_PM25_min,":", rok_PM25_min);
    Blynk.setProperty(V3, "offLabel", maxPM25, "ug/m3");
    Blynk.setProperty(V3, "onLabel", dzien_PM25_max,":", miesiac_PM25_max,":", rok_PM25_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE WARTOSC I DATE");
   break;
  }
  case 13:{
    Blynk.setProperty(V2, "offLabel", minPM10, "ug/m3");
    Blynk.setProperty(V2, "onLabel", dzien_PM10_min,":", miesiac_PM10_min,":", rok_PM10_min);
    Blynk.setProperty(V3, "offLabel", maxPM10, "ug/m3");
    Blynk.setProperty(V3, "onLabel", dzien_PM10_max,":", miesiac_PM10_max,":", rok_PM10_max);
    Blynk.setProperty(V4, "offLabel", "RESET");
    Blynk.setProperty(V4, "onLabel", "RESETUJE WARTOSC I DATE");
   break;
  }
  }
}
BLYNK_WRITE(V14) {
   button_lampa_plac = param.asInt(); //zapisujemy do zmiennej stan buttona
}
BLYNK_WRITE(V15) {
   button_lampa_ogrod = param.asInt(); //zapisujemy do zmiennej stan buttona
}
 BLYNK_WRITE(V16) {
    button_brama_garaz = param.asInt(); //zapisujemy do zmiennej stan buttona

 }
 BLYNK_WRITE(V17) {
   button_furtka = param.asInt(); //zapisujemy do zmiennej stan buttona
}
 BLYNK_WRITE(V18) {
   button_dodatkowy1 = param.asInt(); //zapisujemy do zmiennej stan buttona
}
 BLYNK_WRITE(V19) {
   button_dodatkowy2 = param.asInt(); //zapisujemy do zmiennej stan buttona
}
 BLYNK_WRITE(V20) {
   button_dodatkowy3 = param.asInt(); //zapisujemy do zmiennej stan buttona
}
 BLYNK_WRITE(V21) {
  button_dodatkowy4 = param.asInt(); //zapisujemy do zmiennej stan buttona
}
BLYNK_WRITE(V22){
  blynk_alarm_deszcz = param.asInt();
    if(blynk_alarm_deszcz == 1){
    wylaczono_alarm_deszcz=true;
    Blynk.setProperty(V22, "color", _RED);
    Blynk.setProperty(V22, "onLabel", "!WYLACZONY!");
  }
  if(blynk_alarm_deszcz == 0){
    Blynk.setProperty(V22, "color", _GREEN);
    Blynk.setProperty(V22, "offLabel", "WYLACZ ALARM DESZCZU");
  }
}
BLYNK_WRITE(V24){
  blynk_alarm_pralka = param.asInt();
  if(blynk_alarm_pralka == 1){
    wylaczono_alarm_pralka=true;
    Blynk.setProperty(V24, "color", _RED);
    Blynk.setProperty(V24, "onLabel", "!WYLACZONY!");
  }
  if(blynk_alarm_pralka == 0){
    Blynk.setProperty(V24, "color", _GREEN);
    Blynk.setProperty(V24, "offLabel", "WYLACZ ALARM PRALKI");
  }
}
BLYNK_WRITE(V38){
    PM1=param.asInt();
  }
BLYNK_WRITE(V39){
    PM25=param.asInt();
  } 
BLYNK_WRITE(V40){
    PM10=param.asInt();
  }

void blinkA() { 
  if ((millis() - time) > 200) 
        licznik ++; 
  time = millis(); 
} 
void blinkB() { 
  if ((millis() - time) > 200)  
        licznik --; 
  time = millis(); 
} 
void pozycja_enkodera(){
  if(licznik>liczba_pozycji_menu){
    licznik=1;
  }
  else if(licznik<1){
    licznik=liczba_pozycji_menu;
  }
  else{
     while (pozycja_markera != licznik) 
    { 
    pozycja_markera = licznik;  
    } 
  }
}

/*void testconnect()
{
if (Blynk.connected()) {
digitalWrite(led_blue, HIGH); //wskaźnik łączności z serwerem stan wysoki- wyłączenie LEDa
} else {
digitalWrite(led_blue, LOW);
}
}*/
void term_strych_maxmin_reset(){
  sensors.requestTemperatures(); 
  temp_strych = sensors.getTempC(termometr_strych);
  DateTime now = czas.now();
  if (temp_strych > temp_strych_max) {
    temp_strych_max = temp_strych;
    dzien_temp_strych_max = now.day();
    miesiac_temp_strych_max = now.month();
    rok_temp_strych_max = now.year();
   }
   if (temp_strych < temp_strych_min) { 
    temp_strych_min = temp_strych;
    dzien_temp_strych_min = now.day();
    miesiac_temp_strych_min = now.month();
    rok_temp_strych_min = now.year();
   }
}
void term_slonce_maxmin_reset(){ //termometr garaz z pamięcią temperatury max. i min.
  sensors.requestTemperatures(); 
  temp_slonce = sensors.getTempC(termometr_slonce);
   DateTime now = czas.now();
   if (temp_slonce > temp_slonce_max) {
    temp_slonce_max = temp_slonce;
    dzien_temp_slonce_max = now.day();
    miesiac_temp_slonce_max = now.month();
    rok_temp_slonce_max = now.year();
   }
   if (temp_slonce < temp_slonce_min) { 
    temp_slonce_min = temp_slonce;
    dzien_temp_slonce_min = now.day();
    miesiac_temp_slonce_min = now.month();
    rok_temp_slonce_min = now.year();
   }
}
void term_grunt_maxmin_reset(){ //termometr garaz z pamięcią temperatury max. i min.
  sensors.requestTemperatures(); 
  temp_grunt = sensors.getTempC(termometr_grunt);
   DateTime now = czas.now();
   if (temp_grunt > temp_grunt_max) {
    temp_grunt_max = temp_grunt;
    dzien_temp_grunt_max = now.day();
    miesiac_temp_grunt_max = now.month();
    rok_temp_grunt_max = now.year();
   }
   if (temp_grunt < temp_grunt_min) { 
    temp_grunt_min = temp_grunt;
    dzien_temp_grunt_min = now.day();
    miesiac_temp_grunt_min = now.month();
    rok_temp_grunt_min = now.year();
   }
}
void term_CO_maxmin_reset(){ //termometr garaz z pamięcią temperatury max. i min.
  sensors.requestTemperatures(); 
   DateTime now = czas.now();
  temp_CO = sensors.getTempC(termometr_CO);
   if (temp_CO > temp_CO_max) {
    temp_CO_max = temp_CO;
    dzien_temp_CO_max = now.day();
    miesiac_temp_CO_max = now.month();
    rok_temp_CO_max = now.year();
   }
   if (temp_CO < temp_CO_min) { 
    temp_CO_min = temp_CO;
    dzien_temp_CO_min = now.day();
    miesiac_temp_CO_min = now.month();
    rok_temp_CO_min = now.year();
   }
}
void dht_wew_maxmin_reset(){ 
 DHT dht_wew(DHTPIN1, DHTTYPE1);
 temperatura_dht_kuchnia=dht_wew.readTemperature();
 wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
   DateTime now = czas.now();
  if (temperatura_dht_kuchnia > temperatura_dht_kuchnia_max) {
    temperatura_dht_kuchnia_max = temperatura_dht_kuchnia;
    dzien_temperatura_dht_kuchnia_max = now.day();
    miesiac_temperatura_dht_kuchnia_max = now.month();
    rok_temperatura_dht_kuchnia_max = now.year();
   }
   if (temperatura_dht_kuchnia< temperatura_dht_kuchnia_min) { 
    temperatura_dht_kuchnia_min = temperatura_dht_kuchnia;
    dzien_temperatura_dht_kuchnia_min = now.day();
    miesiac_temperatura_dht_kuchnia_min = now.month();
    rok_temperatura_dht_kuchnia_min = now.year();
   }
   if (wilgotnosc_dht_kuchnia > wilgotnosc_dht_kuchnia_max) {
    wilgotnosc_dht_kuchnia_max = wilgotnosc_dht_kuchnia;
    dzien_wilgotnosc_dht_kuchnia_max = now.day();
    miesiac_wilgotnosc_dht_kuchnia_max = now.month();
    rok_wilgotnosc_dht_kuchnia_max = now.year();
   }
   if (wilgotnosc_dht_kuchnia < wilgotnosc_dht_kuchnia_min) { 
    wilgotnosc_dht_kuchnia_min = wilgotnosc_dht_kuchnia;
    dzien_wilgotnosc_dht_kuchnia_min = now.day();
    miesiac_wilgotnosc_dht_kuchnia_min = now.month();
    rok_wilgotnosc_dht_kuchnia_min = now.year();
   }
 } 
void bmp_maxmin_reset(){
   DateTime now = czas.now();
    temperatura_bmp_piwnica= bme.readTemperature();
    cisnienie_bmp_strych=bme.readPressure()/100;
   if (cisnienie_bmp_strych > cisnienie_bmp_strych_max) {
    cisnienie_bmp_strych_max = cisnienie_bmp_strych;
    dzien_cisnienie_bmp_strych_max = now.day();
    miesiac_cisnienie_bmp_strych_max = now.month();
    rok_cisnienie_bmp_strych_max = now.year();
   }
   if (cisnienie_bmp_strych < cisnienie_bmp_strych_min) { 
    cisnienie_bmp_strych_min = cisnienie_bmp_strych;
    dzien_cisnienie_bmp_strych_min = now.day();
    miesiac_cisnienie_bmp_strych_min = now.month();
    rok_cisnienie_bmp_strych_min = now.year();
   }
    if (temperatura_bmp_piwnica > temperatura_bmp_piwnica_max) {
    temperatura_bmp_piwnica_max = temperatura_bmp_piwnica;
    dzien_temperatura_bmp_piwnica_max = now.day();
    miesiac_temperatura_bmp_piwnica_max = now.month();
    rok_temperatura_bmp_piwnica_max = now.year();
   }
   if (temperatura_bmp_piwnica < temperatura_bmp_piwnica_min) { 
    temperatura_bmp_piwnica_min = temperatura_bmp_piwnica;
    dzien_temperatura_bmp_piwnica_min = now.day();
    miesiac_temperatura_bmp_piwnica_min = now.month();
    rok_temperatura_bmp_piwnica_min = now.year();
   }
}

void dht_zew_maxmin_reset(){
   DHT dht_zew(DHTPIN2, DHTTYPE2);
  wilgotnosc_dht_zew = dht_zew.readHumidity();
  temperatura_dht_zew = dht_zew.readTemperature();
   DateTime now = czas.now();
   if (wilgotnosc_dht_zew > wilgotnosc_dht_zew_max) {
    wilgotnosc_dht_zew_max = wilgotnosc_dht_zew;
    dzien_wilgotnosc_dht_zew_max = now.day();
    miesiac_wilgotnosc_dht_zew_max = now.month();
    rok_wilgotnosc_dht_zew_max = now.year();
   }
   if (wilgotnosc_dht_zew < wilgotnosc_dht_zew_min) { 
    wilgotnosc_dht_zew_min = wilgotnosc_dht_zew;
    dzien_wilgotnosc_dht_zew_min = now.day();
    miesiac_wilgotnosc_dht_zew_min = now.month();
    rok_wilgotnosc_dht_zew_min = now.year();
   }
   if (temperatura_dht_zew > temperatura_dht_zew_max) {
    temperatura_dht_zew_max = temperatura_dht_zew;
    dzien_temperatura_dht_zew_max = now.day();
    miesiac_temperatura_dht_zew_max = now.month();
    rok_temperatura_dht_zew_max = now.year();
   }
   if (temperatura_dht_zew < temperatura_dht_zew_min) { 
    temperatura_dht_zew_min = temperatura_dht_zew;
    dzien_temperatura_dht_zew_min = now.day();
    miesiac_temperatura_dht_zew_min = now.month();
    rok_temperatura_dht_zew_min = now.year();
   }
}
void PM_maxmin_reset(){
   Blynk.syncVirtual(V38,V39,V40);
   DateTime now = czas.now();
   if (PM1 > maxPM1) {
    maxPM1 = PM1;
    dzien_PM1_max = now.day();
    miesiac_PM1_max = now.month();
    rok_PM1_max = now.year();
   }
   if (PM1 < minPM1) { 
    minPM1 = PM1;
    dzien_PM1_min = now.day();
    miesiac_PM1_min = now.month();
    rok_PM1_min = now.year();
   }
   if (PM25 > maxPM25) {
    maxPM25 = PM25;
    dzien_PM25_max = now.day();
    miesiac_PM25_max = now.month();
    rok_PM25_max = now.year();
   }
   if (PM25 < minPM25) { 
    minPM25 = PM25;
    dzien_PM25_min = now.day();
    miesiac_PM25_min = now.month();
    rok_PM25_min = now.year();
   }
    if (PM10 > maxPM10) {
    maxPM10 = PM10;
    dzien_PM10_max = now.day();
    miesiac_PM10_max = now.month();
    rok_PM10_max = now.year();
   }
   if (PM10 < minPM10) { 
    minPM10 = PM10;
    dzien_PM10_min = now.day();
    miesiac_PM10_min = now.month();
    rok_PM10_min = now.year();
   }
}

 void kontrola_garaz(){
   if(button_brama_garaz == 1){
    led2.on();
   }
   else{
    led2.off();
   }
   if(button_brama_garaz != poprzedni_button_brama_garaz){
    poprzedni_button_brama_garaz = button_brama_garaz;
    brama_garaz = true;
   }
 }
  void brama(){
  if((brama_garaz == true) && (praca_brama_garaz == false)){
    praca_brama_garaz = true;
    sekunda.restart();
      digitalWrite(brama_garaz_przekaznik, LOW); //włączmy przekaźnik stanem niskim(pin fizyczny 20)
    //Blynk.setProperty(V16, "color", BLYNK_BLUE);
   // Blynk.setProperty(V16, "Label", "WYKONUJE");
  }
     if(sekunda.available()){
     digitalWrite(brama_garaz_przekaznik, HIGH);
     brama_garaz = false;
     praca_brama_garaz = false;
     }
}
void kontrola_lampa_plac(){
  
   if((button_lampa_plac == 1) || (digitalRead(lampa_plac_wlacznik) == HIGH) || (lampa_plac_enkoder == true)){
    lampa_plac = true;
   }
   else if(button_lampa_plac == 0){
    lampa_plac = false;
   }
}
void kontrola_lampa_ogrod(){
   if((button_lampa_ogrod == 1) || (digitalRead(lampa_ogrod_wlacznik) == HIGH) || (lampa_ogrod_enkoder == true)){
    lampa_ogrod = true;
   }
   else if(button_lampa_ogrod == 0){
    lampa_ogrod = false;
   }
}
void kontrola_furtka(){
  if((button_furtka != poprzedni_button_furtka) || (digitalRead(furtka_wlacznik) == HIGH) || (furtka_enkoder == true)){
    poprzedni_button_furtka = button_furtka;
    furtka = true;
    sekunda.restart();
    digitalWrite(furtka_przekaznik, LOW); //włączmy przekaźnik stanem niskim(pin fizyczny 20)
    Blynk.setProperty(V17, "color", BLYNK_BLUE);
    Blynk.setProperty(V17, "label", "                           WYKONUJE");
    LED.setPixelColor(3, LED.Color(25,0, 0)); 
    LED.show();
  }
  if(sekunda.available()){
     digitalWrite(furtka_przekaznik, HIGH);
     LED.setPixelColor(3, LED.Color(0, 25, 0)); 
     LED.show(); 
     Blynk.setProperty(V17, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
     Blynk.setProperty(V17, "color", _GREEN);
     furtka = false;
     }
}
void kontrola_dodatkowy1(){
   if((button_dodatkowy1 == 1) || (dodatkowy1_enkoder == true)){
    dodatkowy1 = true;
   }
   else if(button_dodatkowy1 == 0){
    dodatkowy1 = false;
   }
}
void kontrola_dodatkowy2(){
   if((button_dodatkowy2 == 1) || (dodatkowy2_enkoder == true)){
    dodatkowy2 = true;
   }
   else if(button_dodatkowy2 == 0){
    dodatkowy2 = false;
   }
}
void kontrola_dodatkowy3(){
   if((button_dodatkowy3 == 1) || (dodatkowy3_enkoder == true)){
    dodatkowy3 = true;
   }
   else if(button_dodatkowy3 == 0){
    dodatkowy3 = false;
   }
}
void kontrola_dodatkowy4(){
   if((button_dodatkowy4 == 1) || (dodatkowy4_enkoder == true)){
    dodatkowy4 = true;
   }
   else if(button_dodatkowy4 == 0){
    dodatkowy4 = false;
   }
}
void praca_przekazniki(){
   if (digitalRead(brama_garaz_krancowka) == HIGH){
    LED.setPixelColor(0, LED.Color(25, 0, 0)); 
    LED.show(); 
    Blynk.setProperty(V16, "color", _RED);
    Blynk.setProperty(V16, "label", "                              OTWARTA");
    if(smsBramaOtwarta == false){
      Blynk.notify("BRAMA OTWARTA");
      smsBramaOtwarta = true;
      smsBramaZamknieta = false;
    }
  }
  else if(digitalRead(brama_garaz_krancowka) == LOW){
    Blynk.setProperty(V16, "color", _GREEN);
    Blynk.setProperty(V16, "label", "                            ZAMKNIETA");
    LED.setPixelColor(0, LED.Color(0, 25, 0)); 
    LED.show(); 
    if(smsBramaZamknieta == false){
      Blynk.notify("BRAMA ZAMKNIETA");
      smsBramaZamknieta = true;
      smsBramaOtwarta = false;
    }
  }
  if(lampa_plac == true){
    digitalWrite(lampa_plac_przekaznik, LOW);
    LED.setPixelColor(1, LED.Color(25, 0, 0)); 
    LED.show(); 
    Blynk.setProperty(V14, "label", "                           WLACZONY"); //wypisujemy na BUTTONie "ON"
    Blynk.setProperty(V14, "color", _RED);
  }
  else if(lampa_plac == false){
    digitalWrite(lampa_plac_przekaznik, HIGH);
    LED.setPixelColor(1, LED.Color(0, 25, 0)); 
    LED.show(); 
    Blynk.setProperty(V14, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
    Blynk.setProperty(V14, "color", _GREEN);
  }
  if(lampa_ogrod == true){
    digitalWrite(lampa_ogrod_przekaznik, LOW);
    LED.setPixelColor(2, LED.Color(25, 0, 0)); 
    LED.show(); 
    Blynk.setProperty(V15, "label", "                           WLACZONY"); //wypisujemy na BUTTONie "ON"
    Blynk.setProperty(V15, "color", _RED);
  }
  else if(lampa_ogrod == false){
    digitalWrite(lampa_ogrod_przekaznik, HIGH);
    LED.setPixelColor(2, LED.Color(0, 25, 0)); 
    LED.show(); 
    Blynk.setProperty(V15, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
    Blynk.setProperty(V15, "color", _GREEN);
  }
  if(dodatkowy1 == true){
    digitalWrite(dodatkowy1_przekaznik, LOW);
    LED.setPixelColor(4, LED.Color(25, 0, 0)); 
    LED.show(); 
    Blynk.setProperty(V18, "label", "                           WLACZONY"); //wypisujemy na BUTTONie "ON"
    Blynk.setProperty(V18, "color", _RED);
  }
  else if(dodatkowy1 == false){
    digitalWrite(dodatkowy1_przekaznik, HIGH);
    LED.setPixelColor(4, LED.Color(0, 25, 0)); 
    LED.show(); 
    Blynk.setProperty(V18, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
    Blynk.setProperty(V18, "color", _GREEN);
  }
  if(dodatkowy2 == true){
    digitalWrite(dodatkowy2_przekaznik, LOW);
    LED.setPixelColor(5, LED.Color(25, 0, 0)); 
    LED.show(); 
    Blynk.setProperty(V19, "label", "                           WLACZONY"); //wypisujemy na BUTTONie "ON"
    Blynk.setProperty(V19, "color", _RED);
  }
  else if(dodatkowy2 == false){
    digitalWrite(dodatkowy2_przekaznik, HIGH);
    LED.setPixelColor(5, LED.Color(0, 25, 0)); 
    LED.show(); 
    Blynk.setProperty(V19, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
    Blynk.setProperty(V19, "color", _GREEN);
  }
  if(dodatkowy3 == true){
    digitalWrite(dodatkowy3_przekaznik, LOW);
    LED.setPixelColor(6, LED.Color(25, 0, 0)); 
    LED.show(); 
    Blynk.setProperty(V20, "label", "                           WLACZONY"); //wypisujemy na BUTTONie "ON"
    Blynk.setProperty(V20, "color", _RED);
  }
  else if(dodatkowy3 == false){
    digitalWrite(dodatkowy3_przekaznik, HIGH);
    LED.setPixelColor(6, LED.Color(0, 25, 0)); 
    LED.show(); 
    Blynk.setProperty(V20, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
    Blynk.setProperty(V20, "color", _GREEN);  
  }
  if(dodatkowy4 == true){
    digitalWrite(dodatkowy4_przekaznik, LOW);
    LED.setPixelColor(7, LED.Color(25, 0, 0));
    LED.show(); 
    Blynk.setProperty(V21, "label", "                           WLACZONY"); //wypisujemy na BUTTONie "ON"
    Blynk.setProperty(V21, "color", _RED);
  }
  else if(dodatkowy4 == false){
    digitalWrite(dodatkowy4_przekaznik, HIGH);
    LED.setPixelColor(7, LED.Color(0, 25, 0));
    LED.show();
    Blynk.setProperty(V21, "label", "                           WYLACZONY"); // wypisujemy na BUTTONie "OFF"
    Blynk.setProperty(V21, "color", _GREEN);
  }
}

void kontrola_przekazniki(){
  kontrola_garaz();
  kontrola_lampa_plac();
  kontrola_lampa_ogrod();
  kontrola_furtka();
  kontrola_dodatkowy1();
  kontrola_dodatkowy2();
  kontrola_dodatkowy3();
  kontrola_dodatkowy4();
  praca_przekazniki();

}
void ping() {
  tone(buzzer, 1000); 
  delay(300);  
  noTone(buzzer);
}
void krotki_ping() {
  tone(buzzer, 1000); 
  delay(50);  
  noTone(buzzer); 
}
void led_alarm(){
 int i = 0;
  uint32_t kolor = 0;
  for (i = 0; i < 8; i++) {
    if (i < 4) {
      LED.setPixelColor(i, LED.Color(125, 0, 0)); //Dioda nr i świeci na wybrany kolor
    } else {
      LED.setPixelColor(i, LED.Color(0, 0, 125)); //Dioda nr i świeci na wybrany kolor     
    }
    
    LED.show(); 
    delay(100);
  }
  LED.clear();
  //krotki_ping();
}

 void alarm_pralka(){
   if((napiecie_pralka < 30) && (wylaczono_alarm_pralka==false)){ 
     if(smsPralka==false){
     Blynk.notify("!!!PRALKA WYLACZONA!!!   !!!PRALKA WYLACZONA!!!");
     smsPralka=true;
     }
    LED.setPixelColor(0, LED.Color(0, 0, 100));
    LED.setPixelColor(1, LED.Color(0, 0, 100));
    LED.setPixelColor(2, LED.Color(0, 0, 100));
    LED.setPixelColor(3, LED.Color(0, 0, 100));
    LED.setPixelColor(4, LED.Color(0, 0, 100));
    LED.setPixelColor(5, LED.Color(0, 0, 100));
    LED.setPixelColor(6, LED.Color(0, 0, 100));
    LED.setPixelColor(7, LED.Color(0, 0, 100));
    LED.show();
   }
   if(napiecie_pralka > 30){
    smsPralka=false;
    wylaczono_alarm_pralka=false;
   }
}

void alarm_deszcz(){
  if((digitalRead(pin_alarm_deszcz) == LOW) && (wylaczono_alarm_deszcz==false)){ 
     if(smsDeszcz==false){
     Blynk.notify("!!!DESZCZ!!!   !!!DESZCZ!!!   !!!DESZCZ!!!");
     smsDeszcz=true;
     }
    led_alarm();
   }
 if(digitalRead(pin_alarm_deszcz) == HIGH){
    smsDeszcz=false;
    wylaczono_alarm_deszcz=false;
  }
}
void alarm(){
  alarm_pralka();
  alarm_deszcz();
}
void menu_glowne(){
  Serial.println(brama_garaz);
 if(sekunddwie.available()){
   kontrola_przekazniki();
   sekunddwie.restart();
 }
 if(czujniki.available()){
  napiecie_pralka = analogRead(A7);
  term_strych_maxmin_reset();
  term_slonce_maxmin_reset();
  term_grunt_maxmin_reset();
  term_CO_maxmin_reset();
  dht_wew_maxmin_reset();
  bmp_maxmin_reset();
  dht_zew_maxmin_reset();
  PM_maxmin_reset();
  Blynk.virtualWrite(5,"    ",temperatura_dht_kuchnia," *C");
  Blynk.virtualWrite(6," ",wilgotnosc_dht_kuchnia," %RH");
  Blynk.virtualWrite(7,"    ",temperatura_dht_zew," *C");
  Blynk.virtualWrite(8," ",wilgotnosc_dht_zew," %RH");
  Blynk.virtualWrite(9,"   ",cisnienie_bmp_strych," hPa");
  Blynk.virtualWrite(10,"    ",temp_grunt," *C");
  Blynk.virtualWrite(11,"    ",temp_slonce," *C");
  Blynk.virtualWrite(12,"    ",temp_strych," *C");
  Blynk.virtualWrite(13,"    ",temp_CO," *C");
  Blynk.virtualWrite(23,"    ",temperatura_bmp_piwnica," *C");
  Blynk.virtualWrite(30,temp_CO);
  Blynk.virtualWrite(31,temperatura_dht_zew);
  Blynk.virtualWrite(32,cisnienie_bmp_strych);
  Blynk.virtualWrite(33,wilgotnosc_dht_zew);
  Blynk.virtualWrite(34,wilgotnosc_dht_kuchnia);
  czujniki.restart();
 }
 switch(menu_1){
 case JEDEN:
    jeden();
    if(alarm_on==false){
    alarm();
    alarm_on=true;
    }
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
  if(glowny.available()){
      lcd.clear(); 
     glowny.restart();
     alarm_on=false;
     menu_1=DWA;
    }
  
 break;
 case DWA:
    dwa();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=TRZY;
    }
 break;
 case TRZY:
    trzy();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=CZTERY;
    }
 break;
 case CZTERY:
    cztery();
    if(alarm_on==false){
     alarm();
     alarm_on=true;
    }
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
   alarm_on=false;
    menu_1=PIEC;
    }
 break;
 case PIEC:
    piec();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=SZESC;
    }
 break;
 case SZESC:
    szesc();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=SIEDEM;
    }
 break;
 case SIEDEM:
    siedem();
   if(alarm_on==false){
     alarm();
     alarm_on=true;
    }
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    alarm_on=false;
    menu_1=OSIEM;
    }
 break;
 case OSIEM:
    osiem();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=DZIEWIEC;
    }
 break;
 case DZIEWIEC:
    dziewiec();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();;
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=DZIESIEC;
    }
 break;
 case DZIESIEC:
    dziesiec();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();;
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=JEDENASCIE;
    }
 break;
 case JEDENASCIE:
    jedenascie();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();;
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=DWANASCIE;
    }
 break;
 case DWANASCIE:
    dwanascie();
    if(digitalRead(PinP)==LOW){
      delay(30);
        lcd.clear(); 
        pozycja_markera=1;
        licznik=1;
        ping();
        time1=millis();;
        menu_opcje();
  }
    if(glowny.available()){
   lcd.clear(); 
   glowny.restart();
    menu_1=JEDEN;
    }
 break;
}
}
void jeden(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Temp.kuchnia:  ");
  lcd.print(temperatura_dht_kuchnia);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print("Wilg.kuchnia: ");
  lcd.print(wilgotnosc_dht_kuchnia);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print("Cisnienie:  ");
  lcd.print(cisnienie_bmp_strych);
  lcd.print(" hPa");
 }
 void dwa(){
   DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Wilg.kuchnia: ");
  lcd.print(wilgotnosc_dht_kuchnia);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print("Cisnienie:  ");
  lcd.print(cisnienie_bmp_strych);
  lcd.print(" hPa");
  lcd.setCursor(0,3);
  lcd.print("Temp.zew.:    ");
  lcd.print(temperatura_dht_zew);
  lcd.print(" *C");
 }
 void trzy(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Cisnienie:  ");
  lcd.print(cisnienie_bmp_strych);
  lcd.print(" hPa");
  lcd.setCursor(0,2);
  lcd.print("Temp.zew.:    ");
  lcd.print(temperatura_dht_zew);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print("Wilg.zew.:    ");
  lcd.print(wilgotnosc_dht_zew);
  lcd.print(" %RH");
 }
 void cztery(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Temp.zew.:    ");
  lcd.print(temperatura_dht_zew);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print("Wilg.zew.:    ");
  lcd.print(wilgotnosc_dht_zew);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print("Temp.grunt:    ");
  lcd.print(temp_grunt);
  lcd.print(" *C");
 }
 void piec(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Wilg.zew.:    ");
  lcd.print(wilgotnosc_dht_zew);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print("Temp.grunt:    ");
  lcd.print(temp_grunt);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print("Temp.slonce:   ");
  lcd.print(temp_slonce);
  lcd.print(" *C");
 }
 void szesc(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Temp.grunt:    ");
  lcd.print(temp_grunt);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print("Temp.slonce:   ");
  lcd.print(temp_slonce);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print("Temp.CO:       ");
  lcd.print(temp_CO);
  lcd.print(" *C");
 }
 void siedem(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Temp.slonce:   ");
  lcd.print(temp_slonce);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print("Temp.CO:       ");
  lcd.print(temp_CO);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print("Temp.strych:   ");
  lcd.print(temp_strych);
  lcd.print(" *C");
 }
 void osiem(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Temp.CO:       ");
  lcd.print(temp_CO);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print("Temp.strych:   ");
  lcd.print(temp_strych);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print("PM 1:     ");
  lcd.print(PM1);
  lcd.print(" ug/m3");
 }
 void dziewiec(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Temp.strych:   ");
  lcd.print(temp_strych);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print("PM 1:     ");
  lcd.print(PM1);
  lcd.print(" ug/m3");
  lcd.setCursor(0,3);
  lcd.print("PM 2.5:   ");
  lcd.print(PM25);
  lcd.print(" ug/m3");
 }
 void dziesiec(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("PM 1:     ");
  lcd.print(PM1);
  lcd.print(" ug/m3");
  lcd.setCursor(0,2);
  lcd.print("PM 2.5:   ");
  lcd.print(PM25);
  lcd.print(" ug/m3");
  lcd.setCursor(0,3);
  lcd.print("PM 10:    ");
  lcd.print(PM10);
  lcd.print(" ug/m3");
 }
 void jedenascie(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("PM 2.5:   ");
  lcd.print(PM25);
  lcd.print(" ug/m3");
  lcd.setCursor(0,2);
  lcd.print("PM 10:    ");
  lcd.print(PM10);
  lcd.print(" ug/m3");
  lcd.setCursor(0,3);
  lcd.print("Temp.kuchnia:  ");
  lcd.print(temperatura_dht_kuchnia);
  lcd.print(" *C");
 }
 void dwanascie(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("  ");
  if(now.hour()<10){
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute()<10){
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(" - ");
  if(now.day()<10){
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('.');
  if(now.month()<10){
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0,1);
  lcd.print("PM 10:    ");
  lcd.print(PM10);
  lcd.print(" ug/m3");
  lcd.setCursor(0,2);
  lcd.print("Temp.kuchnia:  ");
  lcd.print(temperatura_dht_kuchnia);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print("Wilg.kuchnia: ");
  lcd.print(wilgotnosc_dht_kuchnia);
  lcd.print(" %RH");
 }
 void menu_opcje(){
  liczba_pozycji_menu=11;
  czekanie=10000;
  switch(pozycja_markera){
    case 1:
     while(millis()-time1<czekanie){
     opcje_1();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
     }  
    if(digitalRead(PinP) == LOW){
      delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      przekazniki();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 2:
    while(millis()-time1<czekanie){
     opcje_2();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
     }  
     if(digitalRead(PinP) == LOW){
      delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      tempKuchnia();
     }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 3:
     while(millis()-time1<czekanie){
     opcje_3();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
     }  
     if(digitalRead(PinP) == LOW){
      delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      wilgKuchnia();
    }
     }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 4:
    while(millis()-time1<czekanie){
     opcje_4();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
        pozycja_markera_poprzednia = pozycja_markera;
        krotki_ping();
        lcd.clear();
        time1=millis();
        menu_opcje();
     }  
    if(digitalRead(PinP) == LOW){
      delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      cisnienie();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 5:
     while(millis()-time1<czekanie){
     opcje_5();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
   if(digitalRead(PinP) == LOW){
    delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      tempZew();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear();
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 6:
     while(millis()-time1<czekanie){
     opcje_6();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
   if(digitalRead(PinP) == LOW){
    delay(30);
      ping(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      wilgZew();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear();
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 7:
    while(millis()-time1<czekanie){
     opcje_7();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
   if(digitalRead(PinP) == LOW){
    delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      tempGrunt();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 8:
    while(millis()-time1<czekanie){
     opcje_8();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
    if(digitalRead(PinP) == LOW){
      delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      tempSlonce();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 9:
     while(millis()-time1<czekanie){
     opcje_9();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
       if(digitalRead(PinP) == LOW){
        delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      tempCO();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 10:
    while(millis()-time1<czekanie){
     opcje_10();
     kontrola_przekazniki();
     pozycja_enkodera();
      if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
   if(digitalRead(PinP) == LOW){
    delay(30);
      ping();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      time1=millis();
      tempStrych();
    }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_glowne();
   }
    break;
    
    case 11:
     while(millis()-time1<czekanie){
      opcje_11();
      kontrola_przekazniki();
      pozycja_enkodera();
     if(pozycja_markera != pozycja_markera_poprzednia){
       pozycja_markera_poprzednia = pozycja_markera;
       krotki_ping();
       lcd.clear();
       time1=millis();
       menu_opcje();
      }  
  if(digitalRead(PinP) == LOW){
    delay(30);
      ping();
      lcd.clear();
      glowny.restart();
      menu_glowne();
      }
    }
   if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();  
    menu_glowne();
   }
    break;
  }
 }
 void opcje_1(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">WLACZNIKI");
  lcd.setCursor(0,3);
  lcd.print(" Temp.kuchn. min-max");
 }
 void opcje_2(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" WLACZNIKI");
  lcd.setCursor(0,2);
  lcd.print(">Temp.kuchn. min-max");
  lcd.setCursor(0,3);
  lcd.print(" Wilg.kuch. min-max");
 }
  void opcje_3(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Temp.kuchn. min-max");
  lcd.setCursor(0,2);
  lcd.print(">Wilg.kuch. min-max");
  lcd.setCursor(0,3);
  lcd.print(" Cisnienie min-max");
 }
 void opcje_4(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Wilg.kuch. min-max");
  lcd.setCursor(0,2);
  lcd.print(">Cisnienie min-max");
  lcd.setCursor(0,3);
  lcd.print(" Temp.zew. min-max");
 }
 void opcje_5(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Cisnienie min-max");
  lcd.setCursor(0,2);
  lcd.print(">Temp.zew. min-max");
  lcd.setCursor(0,3);
  lcd.print(" Wil.zew. min-max");
 }
  void opcje_6(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Temp.zew. min-max");
  lcd.setCursor(0,2);
  lcd.print(">Wil.zew. min-max");
  lcd.setCursor(0,3);
  lcd.print(" Temp.grunt min-max");
 }
 void opcje_7(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Wil.zew. min-max");
  lcd.setCursor(0,2);
  lcd.print(">Temp.grunt min-max");
  lcd.setCursor(0,3);
  lcd.print(" Temp.slonce min-max");
 }
 void opcje_8(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Temp.grunt min-max");
  lcd.setCursor(0,2);
  lcd.print(">Temp.slonce min-max");
  lcd.setCursor(0,3);
  lcd.print(" Temp.CO min-max");
 }
 void opcje_9(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Temp.slonce min-max");
  lcd.setCursor(0,2);
  lcd.print(">Temp.CO min-max");
  lcd.setCursor(0,3);
  lcd.print(" Temp.strych min-max");
 }
 void opcje_10(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Temp.CO min-max");
  lcd.setCursor(0,2);
  lcd.print(">Temp.strych min-max");
  lcd.setCursor(0,3);
  lcd.print("   <--POWROT");
 }
 void opcje_11(){
  lcd.setCursor(0,0);
  lcd.print(" <<<<  OPCJE  >>>>");
  lcd.setCursor(0,1);
  lcd.print(" Temp.strych min-max");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
 
 void tempKuchnia(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    tempKuchnia_1();
    wait_and_checkButton_tempKuchnia();
    break;
    case 2:
    tempKuchnia_2();
    wait_and_checkButton_tempKuchnia();
    break;
    case 3:
    tempKuchnia_3();
    wait_and_checkButton_tempKuchnia();
    break;
    case 4:
    tempKuchnia_4();
    wait_and_checkButton_tempKuchnia();
    break;
    case 5:
    tempKuchnia_5();
    wait_and_checkButton_tempKuchnia();
    break;
    case 6:
    tempKuchnia_6();
    wait_and_checkButton_tempKuchnia();
    break;
  }
 }
 void tempKuchnia_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print("        ");
  lcd.print(temperatura_dht_kuchnia);
  lcd.print("*C");
  lcd.setCursor(0,2);
  lcd.print(">Temp. min:  ");
  lcd.print(temperatura_dht_kuchnia_min);
  lcd.print("*C");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_temperatura_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(miesiac_temperatura_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(rok_temperatura_dht_kuchnia_min);
 }
 void tempKuchnia_2(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("<< Temp. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. min: ");
  lcd.print(temperatura_dht_kuchnia_min);
  lcd.print("*C");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_temperatura_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(miesiac_temperatura_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(rok_temperatura_dht_kuchnia_min);
  lcd.setCursor(0,3);
  lcd.print(" Temp. max.: ");
  lcd.print(wilgotnosc_dht_kuchnia_max);
  lcd.print("*C");
 }
 void tempKuchnia_3(){
  DateTime now = czas.now();
  lcd.setCursor(0,0);
  lcd.print("<< Temp. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_temperatura_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(miesiac_temperatura_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(rok_temperatura_dht_kuchnia_min);
  lcd.setCursor(0,2);
  lcd.print(">Temp. max.: ");
  lcd.print(wilgotnosc_dht_kuchnia_max);
  lcd.print("*C");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_temperatura_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(miesiac_temperatura_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(rok_temperatura_dht_kuchnia_max);
 }
 void tempKuchnia_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. max.: ");
  lcd.print(wilgotnosc_dht_kuchnia_max);
  lcd.print("*C");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_temperatura_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(miesiac_temperatura_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(rok_temperatura_dht_kuchnia_max);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void tempKuchnia_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_temperatura_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(miesiac_temperatura_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(rok_temperatura_dht_kuchnia_max);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void tempKuchnia_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
  void wilgKuchnia(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    wilgKuchnia_1();
    wait_and_checkButton_wilgKuchnia();
    break;
    case 2:
    wilgKuchnia_2();
    wait_and_checkButton_wilgKuchnia();
    break;
    case 3:
    wilgKuchnia_3();
    wait_and_checkButton_wilgKuchnia();
    break;
    case 4:
    wilgKuchnia_4();
    wait_and_checkButton_wilgKuchnia();
    break;
    case 5:
    wilgKuchnia_5();
    wait_and_checkButton_wilgKuchnia();
    break;
    case 6:
    wilgKuchnia_6();
    wait_and_checkButton_wilgKuchnia();
    break;
  }
 }
 void wilgKuchnia_1(){
  lcd.setCursor(0,0);
  lcd.print("<<  Wilg. kuchnia  >>");
  lcd.setCursor(0,1);
  lcd.print("        ");
  lcd.print(wilgotnosc_dht_kuchnia);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Min:  ");
  lcd.print(wilgotnosc_dht_kuchnia_min);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_wilgotnosc_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(miesiac_wilgotnosc_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(rok_wilgotnosc_dht_kuchnia_min);
 }
 void wilgKuchnia_2(){
  lcd.setCursor(0,0);
  lcd.print("<<  Wilg. kuchnia  >>");
  lcd.setCursor(0,1);
  lcd.print(" Min:  ");
  lcd.print(wilgotnosc_dht_kuchnia_min);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_wilgotnosc_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(miesiac_wilgotnosc_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(rok_wilgotnosc_dht_kuchnia_min);
  lcd.setCursor(0,3);
  lcd.print(" Max.: ");
  lcd.print(wilgotnosc_dht_kuchnia_max);
  lcd.print(" %RH");
 }
 void wilgKuchnia_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_wilgotnosc_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(miesiac_wilgotnosc_dht_kuchnia_min);
  lcd.print('.');
  lcd.print(rok_wilgotnosc_dht_kuchnia_min);
  lcd.setCursor(0,2);
  lcd.print(">Wilg. max.: ");
  lcd.print(wilgotnosc_dht_kuchnia_max);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_wilgotnosc_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(miesiac_wilgotnosc_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(rok_wilgotnosc_dht_kuchnia_max);
 }
 void wilgKuchnia_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Wilg. max.: ");
  lcd.print(wilgotnosc_dht_kuchnia_max);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_wilgotnosc_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(miesiac_wilgotnosc_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(rok_wilgotnosc_dht_kuchnia_max);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void wilgKuchnia_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_wilgotnosc_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(miesiac_wilgotnosc_dht_kuchnia_max);
  lcd.print('.');
  lcd.print(rok_wilgotnosc_dht_kuchnia_max);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void wilgKuchnia_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. kuchnia >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
  void cisnienie(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    cisnienie_1();
    wait_and_checkButton_cisnienie();
    break;
    case 2:
    cisnienie_2();
    wait_and_checkButton_cisnienie();
    break;
    case 3:
    cisnienie_3();
    wait_and_checkButton_cisnienie();
    break;
    case 4:
    cisnienie_4();
    wait_and_checkButton_cisnienie();
    break;
    case 5:
    cisnienie_5();
    wait_and_checkButton_cisnienie();
    break;
    case 6:
    cisnienie_6();
    wait_and_checkButton_cisnienie();
    break;
  }
 }
 void cisnienie_1(){
  lcd.setCursor(0,0);
  lcd.print("  << Cisnienie >>");
  lcd.setCursor(0,1);
  lcd.print("      ");
  lcd.print(cisnienie_bmp_strych);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Min:  ");
  lcd.print(cisnienie_bmp_strych_min);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_cisnienie_bmp_strych_min);
  lcd.print('.');
  lcd.print(miesiac_cisnienie_bmp_strych_min);
  lcd.print('.');
  lcd.print(rok_cisnienie_bmp_strych_min);
 }
 void cisnienie_2(){
  lcd.setCursor(0,0);
  lcd.print("  << Cisnienie >>");
  lcd.setCursor(0,1);
  lcd.print(" Min:  ");
  lcd.print(cisnienie_bmp_strych_min);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_cisnienie_bmp_strych_min);
  lcd.print('.');
  lcd.print(miesiac_cisnienie_bmp_strych_min);
  lcd.print('.');
  lcd.print(rok_cisnienie_bmp_strych_min);
  lcd.setCursor(0,3);
  lcd.print(" Max.: ");
  lcd.print(cisnienie_bmp_strych_max);
  lcd.print(" %RH");
 }
 void cisnienie_3(){
  lcd.setCursor(0,0);
  lcd.print("  << Cisnienie >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_cisnienie_bmp_strych_min);
  lcd.print('.');
  lcd.print(miesiac_cisnienie_bmp_strych_min);
  lcd.print('.');
  lcd.print(rok_cisnienie_bmp_strych_min);
  lcd.setCursor(0,2);
  lcd.print(">Max.: ");
  lcd.print(cisnienie_bmp_strych_max);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_cisnienie_bmp_strych_max);
  lcd.print('.');
  lcd.print(miesiac_cisnienie_bmp_strych_max);
  lcd.print('.');
  lcd.print(rok_cisnienie_bmp_strych_max);
 }
 void cisnienie_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Cisnienie >>");
  lcd.setCursor(0,1);
  lcd.print(" Max.: ");
  lcd.print(cisnienie_bmp_strych_max);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_cisnienie_bmp_strych_max);
  lcd.print('.');
  lcd.print(miesiac_cisnienie_bmp_strych_max);
  lcd.print('.');
  lcd.print(rok_cisnienie_bmp_strych_max);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void cisnienie_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Cisnienie >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_cisnienie_bmp_strych_max);
  lcd.print('.');
  lcd.print(miesiac_cisnienie_bmp_strych_max);
  lcd.print('.');
  lcd.print(rok_cisnienie_bmp_strych_max);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void cisnienie_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Cisnienie >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
  void tempZew(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    tempZew_1();
    wait_and_checkButton_tempZew();
    break;
    case 2:
    tempZew_2();
    wait_and_checkButton_tempZew();
    break;
    case 3:
    tempZew_3();
    wait_and_checkButton_tempZew();
    break;
    case 4:
    tempZew_4();
    wait_and_checkButton_tempZew();
    break;
    case 5:
    tempZew_5();
    wait_and_checkButton_tempZew();
    break;
    case 6:
    tempZew_6();
    wait_and_checkButton_tempZew();
    break;
  }
 }
 void tempZew_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. zew. >>");
  lcd.setCursor(0,1);
  lcd.print("        ");
  lcd.print(temperatura_dht_zew);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Temp. min:  ");
  lcd.print(temperatura_dht_zew_min);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_temperatura_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temperatura_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(rok_temperatura_dht_zew_min,DEC);
 }
 void tempZew_2(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. min: ");
  lcd.print(temperatura_dht_zew_min);
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_temperatura_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temperatura_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(rok_temperatura_dht_zew_min,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Temp. max.: ");
  lcd.print(temperatura_dht_zew_max);
 }
 void tempZew_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.: ");
  lcd.print(dzien_temperatura_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temperatura_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(rok_temperatura_dht_zew_min,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Temp. max.: ");
  lcd.print(temperatura_dht_zew_max);
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_temperatura_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temperatura_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(rok_temperatura_dht_zew_max,DEC);
 }
 void tempZew_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. max.: ");
  lcd.print(temperatura_dht_zew_max);
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_temperatura_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temperatura_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(rok_temperatura_dht_zew_max,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void tempZew_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_temperatura_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temperatura_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(rok_temperatura_dht_zew_max,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void tempZew_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp.zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
void wilgZew(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    wilgZew_1();
    wait_and_checkButton_wilgZew();
    break;
    case 2:
    wilgZew_2();
    wait_and_checkButton_wilgZew();
    break;
    case 3:
    wilgZew_3();
    wait_and_checkButton_wilgZew();
    break;
    case 4:
    wilgZew_4();
    wait_and_checkButton_wilgZew();
    break;
    case 5:
    wilgZew_5();
    wait_and_checkButton_wilgZew();
    break;
    case 6:
    wilgZew_6();
    wait_and_checkButton_wilgZew();
    break;
  }
 }
 void wilgZew_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. zew. >>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">Wilg. min:  ");
  lcd.print(wilgotnosc_dht_zew_min);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_wilgotnosc_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_wilgotnosc_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(rok_wilgotnosc_dht_zew_min,DEC);
 }
 void wilgZew_2(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Wilg. min: ");
  lcd.print(wilgotnosc_dht_zew_min);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_wilgotnosc_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_wilgotnosc_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(rok_wilgotnosc_dht_zew_min,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Wilg. max.: ");
  lcd.print(wilgotnosc_dht_zew_max);
  lcd.print(" %RH");
 }
 void wilgZew_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_wilgotnosc_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_wilgotnosc_dht_zew_min, DEC);
  lcd.print(":");
  lcd.print(rok_wilgotnosc_dht_zew_min,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Wilg. max.: ");
  lcd.print(wilgotnosc_dht_zew_max);
  lcd.print(" %RH");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_wilgotnosc_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_wilgotnosc_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(rok_wilgotnosc_dht_zew_max,DEC);
 }
 void wilgZew_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Wilg. max.: ");
  lcd.print(wilgotnosc_dht_zew_max);
  lcd.print(" %RH");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_wilgotnosc_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_wilgotnosc_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(rok_wilgotnosc_dht_zew_max,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void wilgZew_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg. zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_wilgotnosc_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_wilgotnosc_dht_zew_max, DEC);
  lcd.print(":");
  lcd.print(rok_wilgotnosc_dht_zew_max,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void wilgZew_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Wilg.zew. >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
 void tempGrunt(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    tempGrunt_1();
    wait_and_checkButton_tempGrunt();
    break;
    case 2:
    tempGrunt_2();
    wait_and_checkButton_tempGrunt();
    break;
    case 3:
    tempGrunt_3();
    wait_and_checkButton_tempGrunt();
    break;
    case 4:
    tempGrunt_4();
    wait_and_checkButton_tempGrunt();
    break;
    case 5:
    tempGrunt_5();
    wait_and_checkButton_tempGrunt();
    break;
    case 6:
    tempGrunt_6();
    wait_and_checkButton_tempGrunt();
    break;
  }
 }
 void tempGrunt_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. grunt >>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">Temp. min:  ");
  lcd.print(temp_grunt_min);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_grunt_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_min,DEC);
 }
 void tempGrunt_2(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. grunt >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. min: ");
  lcd.print(temp_grunt_min);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_temp_grunt_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_min,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_grunt_max);
  lcd.print(" *C");
 }
 void tempGrunt_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. grunt >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_grunt_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_min,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Temp. max.: ");
  lcd.print(temp_grunt_max);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_max,DEC);
 }
 void tempGrunt_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. grunt >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_grunt_max);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_max,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void tempGrunt_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. grunt >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_max,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void tempGrunt_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. grunt >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
 void tempSlonce(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    tempSlonce_1();
    wait_and_checkButton_tempSlonce();
    break;
    case 2:
    tempSlonce_2();
    wait_and_checkButton_tempSlonce();
    break;
    case 3:
    tempSlonce_3();
    wait_and_checkButton_tempSlonce();
    break;
    case 4:
    tempSlonce_4();
    wait_and_checkButton_tempSlonce();
    break;
    case 5:
    tempSlonce_5();
    wait_and_checkButton_tempSlonce();
    break;
    case 6:
    tempSlonce_6();
    wait_and_checkButton_tempSlonce();
    break;
  }
 }
 void tempSlonce_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Slonce >>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">Temp. min:  ");
  lcd.print(temp_slonce_min);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_grunt_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_grunt_max,DEC);
 }
 void tempSlonce_2(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Slonce >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. min: ");
  lcd.print(temp_slonce_min);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_temp_slonce_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_slonce_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_slonce_min,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_slonce_max);
  lcd.print(" *C");
 }
 void tempSlonce_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Slonce >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_slonce_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_slonce_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_slonce_min,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Temp. max.: ");
  lcd.print(temp_slonce_max);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_slonce_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_slonce_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_slonce_max,DEC);
 }
 void tempSlonce_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Slonce >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_slonce_max);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_temp_slonce_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_slonce_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_slonce_max,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void tempSlonce_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Slonce >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_slonce_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_slonce_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_slonce_max,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void tempSlonce_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Slonce >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
 void tempCO(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    tempCO_1();
    wait_and_checkButton_tempCO();
    break;
    case 2:
    tempCO_2();
    wait_and_checkButton_tempCO();
    break;
    case 3:
    tempCO_3();
    wait_and_checkButton_tempCO();
    break;
    case 4:
    tempCO_4();
    wait_and_checkButton_tempCO();
    break;
    case 5:
    tempCO_5();
    wait_and_checkButton_tempCO();
    break;
    case 6:
    tempCO_6();
    wait_and_checkButton_tempCO();
    break;
  }
 }
 void tempCO_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. CO >>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">Temp. min:  ");
  lcd.print(temp_CO_min);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_CO_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_CO_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_CO_min,DEC);
 }
 void tempCO_2(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. CO >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. min: ");
  lcd.print(temp_CO_min);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_temp_CO_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_CO_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_CO_min,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_CO_max);
  lcd.print(" *C");
 }
 void tempCO_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. CO >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.");
  lcd.print(dzien_temp_CO_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_CO_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_CO_min,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Temp. max.: ");
  lcd.print(temp_CO_max);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_CO_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_CO_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_CO_max,DEC);
 }
 void tempCO_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. CO >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_CO_max);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_temp_CO_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_CO_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_CO_max,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void tempCO_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. CO >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_CO_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_CO_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_CO_max,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void tempCO_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. CO >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }
 void tempStrych(){
  kontrola_przekazniki();
  liczba_pozycji_menu=6;
  czekanie = 10000;
  switch(pozycja_markera){
    case 1:
    tempStrych_1();
    wait_and_checkButton_tempStrych();
    break;
    case 2:
    tempStrych_2();
    wait_and_checkButton_tempStrych();
    break;
    case 3:
    tempStrych_3();
    wait_and_checkButton_tempStrych();
    break;
    case 4:
    tempStrych_4();
    wait_and_checkButton_tempStrych();
    break;
    case 5:
    tempStrych_5();
    wait_and_checkButton_tempStrych();
    break;
    case 6:
    tempStrych_6();
    wait_and_checkButton_tempStrych();
    break;
  }
 }
 void tempStrych_1(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Strych >>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">Temp. min:  ");
  lcd.print(temp_strych_min);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_strych_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_strych_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_strych_min,DEC);
 }
 void tempStrych_2(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Strych >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. min: ");
  lcd.print(temp_strych_min);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data min.:");
  lcd.print(dzien_temp_strych_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_strych_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_strych_min,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_strych_max);
  lcd.print(" *C");
 }
 void tempStrych_3(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Strych >>");
  lcd.setCursor(0,1);
  lcd.print(" Data min.:");
  lcd.print(dzien_temp_strych_min, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_strych_min, DEC);
  lcd.print(":");
  lcd.print(rok_temp_strych_min,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Temp. max.: ");
  lcd.print(temp_strych_max);
  lcd.print(" *C");
  lcd.setCursor(0,3);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_strych_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_strych_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_strych_max,DEC);
 }
 void tempStrych_4(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Strych >>");
  lcd.setCursor(0,1);
  lcd.print(" Temp. max.: ");
  lcd.print(temp_strych_max);
  lcd.print(" *C");
  lcd.setCursor(0,2);
  lcd.print(">Data max.:");
  lcd.print(dzien_temp_strych_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_strych_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_strych_max,DEC);
  lcd.setCursor(0,3);
  lcd.print(" Kasuj (NACISNIJ)");
 }
 void tempStrych_5(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Strych >>");
  lcd.setCursor(0,1);
  lcd.print(" Data max.:");
  lcd.print(dzien_temp_strych_max, DEC);
  lcd.print(":");
  lcd.print(miesiac_temp_strych_max, DEC);
  lcd.print(":");
  lcd.print(rok_temp_strych_max,DEC);
  lcd.setCursor(0,2);
  lcd.print(">Kasuj (NACISNIJ)");
  lcd.setCursor(0,3);
  lcd.print("    <--POWROT");
 }
 void tempStrych_6(){
  lcd.setCursor(0,0);
  lcd.print("<< Temp. Strych >>");
  lcd.setCursor(0,1);
  lcd.print(" Kasuj (NACISNIJ)");
  lcd.setCursor(0,2);
  lcd.print(">   <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                    ");
 }

 void przekazniki(){
  liczba_pozycji_menu=9;
  czekanie = 10000;
  kontrola_przekazniki();
  switch(pozycja_markera){
    case 1:
    przekazniki_1();
    wait_and_checkButton_przekazniki();
    break;
    case 2:
    przekazniki_2();
    wait_and_checkButton_przekazniki();
    break;
    case 3:
    przekazniki_3();
    wait_and_checkButton_przekazniki();
    break;
    case 4:
    przekazniki_4();
    wait_and_checkButton_przekazniki();
    break;
    case 5:
    przekazniki_5();
    wait_and_checkButton_przekazniki();
    break;
    case 6:
    przekazniki_6();
    wait_and_checkButton_przekazniki();
    break;
    case 7:
    przekazniki_7();
    wait_and_checkButton_przekazniki();
    break;
    case 8:
    przekazniki_8();
    wait_and_checkButton_przekazniki();
    break;
    case 9:
    przekazniki_9();
    wait_and_checkButton_przekazniki();
    break;
  }
 }
  void przekazniki_1(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(">Lampa plac   ");
  if(lampa_plac==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print(" Lampy ogrod");
  
  }
  void przekazniki_2(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Lampa plac");
  lcd.setCursor(0,2);
  lcd.print(">Lampy ogrod  ");
  if(lampa_ogrod==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print(" Brama garaz");
  }
  void przekazniki_3(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Lampy ogrod");
  lcd.setCursor(0,2);
  lcd.print(">Br. garaz ");
  if(digitalRead(brama_garaz_krancowka) == LOW){
    lcd.print("ZAMKNIETA");
  }
  else if(digitalRead(brama_garaz_krancowka) == HIGH){
    lcd.print("OTWARTA");
  }
  lcd.setCursor(0,3);
  lcd.print(" Furtka");
  }
   void przekazniki_4(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Brama garaz");
  lcd.setCursor(0,2);
  lcd.print(">Furtka       ");
  if(furtka==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print(" Dodatkowy_1");
  }
  void przekazniki_5(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Furtka");
  lcd.setCursor(0,2);
  lcd.print(">Dodatkowy_1   ");
  if(dodatkowy1==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print(" Dodatkowy_2");
  }
  void przekazniki_6(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Dodatkowy_1   ");
  lcd.setCursor(0,2);
  lcd.print(">Dodatkowy_2   ");
  if(dodatkowy2==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print(" Dodatkowy_3");
  }
  void przekazniki_7(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Dodatkowy_2   ");
  lcd.setCursor(0,2);
  lcd.print(">Dodatkowy_3   ");
  if(dodatkowy3==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print(" Dodatkowy_4");
  }
  void przekazniki_8(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Dodatkowy_3   ");
  lcd.setCursor(0,2);
  lcd.print(">Dodatkowy_4   ");
  if(dodatkowy4==false){
    lcd.print("OFF");
  }
  else{
    lcd.print("ON");
  }
  lcd.setCursor(0,3);
  lcd.print("   <--POWROT");
  }
  void przekazniki_9(){
  lcd.setCursor(0,0);
  lcd.print("<<  Przekazniki  >>");
  lcd.setCursor(0,1);
  lcd.print(" Dodatkowy_4    ");
  lcd.setCursor(0,2);
  lcd.print(">  <--POWROT");
  lcd.setCursor(0,3);
  lcd.print("                     ");
  }

void wait_and_checkButton_przekazniki(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    pozycja_enkodera();
    kontrola_przekazniki();
    if((pozycja_markera == 1) && (lampa_plac != poprzedni_lampa_plac)){
      poprzedni_lampa_plac=lampa_plac;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 2) && (lampa_ogrod != poprzedni_lampa_ogrod)){
      poprzedni_lampa_ogrod=lampa_ogrod;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 3) && (brama_garaz != poprzedni_brama_garaz)){
      poprzedni_brama_garaz=brama_garaz;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 4) && (furtka != poprzedni_furtka)){
      poprzedni_furtka =furtka;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 5) && (dodatkowy1 != poprzedni_dodatkowy1)){
      poprzedni_dodatkowy1=dodatkowy1;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 6) && (dodatkowy2 != poprzedni_dodatkowy2)){
      poprzedni_dodatkowy2=dodatkowy2;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 7) && (dodatkowy3 != poprzedni_dodatkowy3)){
      poprzedni_dodatkowy3=dodatkowy3;
      lcd.clear();
      przekazniki();
    }
    if((pozycja_markera == 8) && (dodatkowy4 != poprzedni_dodatkowy4)){
      poprzedni_dodatkowy4=dodatkowy4;
      lcd.clear();
      przekazniki();
    }
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    przekazniki();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis();  
      lampa_plac_enkoder = !lampa_plac_enkoder;
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis();  
    lampa_ogrod_enkoder = !lampa_ogrod_enkoder;
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        time1 =millis(); 
        ping();
       brama_garaz = !brama_garaz;
     }
    
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(300);
        ping();
        time1 =millis(); 
     furtka_enkoder = !furtka_enkoder;
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(300);
        ping();
        time1 =millis();  
     dodatkowy1_enkoder = !dodatkowy1_enkoder;
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis();
      dodatkowy2_enkoder = !dodatkowy2_enkoder;
    }
     if((digitalRead(PinP) ==LOW) && (pozycja_markera==7)){
        delay(30);
        ping();
        time1 =millis(); 
      dodatkowy3_enkoder = !dodatkowy3_enkoder;
    }
     if((digitalRead(PinP) ==LOW) && (pozycja_markera==8)){
        delay(30);
        ping();
        time1 =millis(); 
     dodatkowy4_enkoder = !dodatkowy4_enkoder;
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==9)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_tempKuchnia(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    tempKuchnia();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      temperatura_dht_kuchnia=dht_wew.readTemperature();
      temperatura_dht_kuchnia_min=temperatura_dht_kuchnia;
      dzien_temperatura_dht_kuchnia_min = now.day();
      miesiac_temperatura_dht_kuchnia_min = now.month();
      rok_temperatura_dht_kuchnia_min = now.year();
      pozycja_markera=1;
      licznik=1;
      tempKuchnia_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      temperatura_dht_kuchnia=dht_wew.readTemperature();
      temperatura_dht_kuchnia_min=temperatura_dht_kuchnia;
      dzien_temperatura_dht_kuchnia_min = now.day();
      miesiac_temperatura_dht_kuchnia_min = now.month();
      rok_temperatura_dht_kuchnia_min = now.year();
      pozycja_markera=2;
      licznik=2;
      tempKuchnia_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      temperatura_dht_kuchnia=dht_wew.readTemperature();
      temperatura_dht_kuchnia_max=temperatura_dht_kuchnia;
      dzien_temperatura_dht_kuchnia_max = now.day();
      miesiac_temperatura_dht_kuchnia_max = now.month();
      rok_temperatura_dht_kuchnia_max = now.year();
      pozycja_markera=3;
      licznik=3;
      tempKuchnia_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      temperatura_dht_kuchnia=dht_wew.readTemperature();
      temperatura_dht_kuchnia_max=temperatura_dht_kuchnia;
      dzien_temperatura_dht_kuchnia_max = now.day();
      miesiac_temperatura_dht_kuchnia_max = now.month();
      rok_temperatura_dht_kuchnia_max = now.year();
      pozycja_markera=4;
      licznik=4;
      tempKuchnia_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
      delay(30);
      ping();
      time1 =millis(); 
      dht_wew_maxmin_reset();
      lcd.clear(); 
      DateTime now = czas.now();
      
      temperatura_dht_kuchnia=dht_wew.readTemperature();
      temperatura_dht_kuchnia_min=temperatura_dht_kuchnia;
      dzien_temperatura_dht_kuchnia_min = now.day();
      miesiac_temperatura_dht_kuchnia_min = now.month();
      rok_temperatura_dht_kuchnia_min = now.year();
      temperatura_dht_kuchnia_max=temperatura_dht_kuchnia;
      dzien_temperatura_dht_kuchnia_max = now.day();
      miesiac_temperatura_dht_kuchnia_max = now.month();
      rok_temperatura_dht_kuchnia_max = now.year();
      pozycja_markera=5;
      licznik=5;
      tempKuchnia_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
   lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_wilgKuchnia(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    wilgKuchnia();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
      wilgotnosc_dht_kuchnia_min=wilgotnosc_dht_kuchnia;
      dzien_wilgotnosc_dht_kuchnia_min = now.day();
      miesiac_wilgotnosc_dht_kuchnia_min = now.month();
      rok_wilgotnosc_dht_kuchnia_min = now.year();
      pozycja_markera=5;
      pozycja_markera=1;
      licznik=1;
      wilgKuchnia_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(300);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
      wilgotnosc_dht_kuchnia_min=wilgotnosc_dht_kuchnia;
      dzien_wilgotnosc_dht_kuchnia_min = now.day();
      miesiac_wilgotnosc_dht_kuchnia_min = now.month();
      rok_wilgotnosc_dht_kuchnia_min = now.year();
      pozycja_markera=2;
      licznik=2;
      wilgKuchnia_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
      wilgotnosc_dht_kuchnia_max=wilgotnosc_dht_kuchnia;
      dzien_wilgotnosc_dht_kuchnia_max = now.day();
      miesiac_wilgotnosc_dht_kuchnia_max = now.month();
      rok_wilgotnosc_dht_kuchnia_max = now.year();
      pozycja_markera=3;
      licznik=3;
      wilgKuchnia_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
      wilgotnosc_dht_kuchnia_max=wilgotnosc_dht_kuchnia;
      dzien_wilgotnosc_dht_kuchnia_max = now.day();
      miesiac_wilgotnosc_dht_kuchnia_max = now.month();
      rok_wilgotnosc_dht_kuchnia_max = now.year();
      pozycja_markera=4;
      licznik=4;
      wilgKuchnia_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      
      wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
      wilgotnosc_dht_kuchnia_min=wilgotnosc_dht_kuchnia;
      dzien_wilgotnosc_dht_kuchnia_min = now.day();
      miesiac_wilgotnosc_dht_kuchnia_min = now.month();
      rok_wilgotnosc_dht_kuchnia_min = now.year();
      wilgotnosc_dht_kuchnia_max=wilgotnosc_dht_kuchnia;
      dzien_wilgotnosc_dht_kuchnia_max = now.day();
      miesiac_wilgotnosc_dht_kuchnia_max = now.month();
      rok_wilgotnosc_dht_kuchnia_max = now.year();
      pozycja_markera=5;
      licznik=5;
      wilgKuchnia_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_cisnienie(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    cisnienie();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      cisnienie_bmp_strych=bme.readPressure()/100;
      cisnienie_bmp_strych_min=cisnienie_bmp_strych;
      dzien_cisnienie_bmp_strych_min = now.day();
      miesiac_cisnienie_bmp_strych_min = now.month();
      rok_cisnienie_bmp_strych_min = now.year();
      pozycja_markera=1;
      licznik=1;
      cisnienie_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear();
      DateTime now = czas.now(); 
      cisnienie_bmp_strych=bme.readPressure()/100;
      cisnienie_bmp_strych_min=cisnienie_bmp_strych;
      dzien_cisnienie_bmp_strych_min = now.day();
      miesiac_cisnienie_bmp_strych_min = now.month();
      rok_cisnienie_bmp_strych_min = now.year();
      pozycja_markera=2;
      licznik=2;
      cisnienie_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      cisnienie_bmp_strych=bme.readPressure()/100;
      cisnienie_bmp_strych_max=cisnienie_bmp_strych;
      dzien_cisnienie_bmp_strych_max = now.day();
      miesiac_cisnienie_bmp_strych_max = now.month();
      rok_cisnienie_bmp_strych_max = now.year();
      pozycja_markera=3;
      licznik=3;
      cisnienie_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      cisnienie_bmp_strych=bme.readPressure()/100;
      cisnienie_bmp_strych_max=cisnienie_bmp_strych;
      dzien_cisnienie_bmp_strych_max = now.day();
      miesiac_cisnienie_bmp_strych_max = now.month();
      rok_cisnienie_bmp_strych_max = now.year();
      pozycja_markera=4;
      licznik=4;
      cisnienie_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      cisnienie_bmp_strych=bme.readPressure()/100;
      cisnienie_bmp_strych_min=cisnienie_bmp_strych;
      dzien_cisnienie_bmp_strych_min = now.day();
      miesiac_cisnienie_bmp_strych_min = now.month();
      rok_cisnienie_bmp_strych_min = now.year();
      cisnienie_bmp_strych_max=cisnienie_bmp_strych;
      dzien_cisnienie_bmp_strych_max = now.day();
      miesiac_cisnienie_bmp_strych_max = now.month();
      rok_cisnienie_bmp_strych_max = now.year();
      pozycja_markera=1;
      licznik=1;
      cisnienie_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_tempZew(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    tempZew();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temperatura_dht_zew = dht_zew.readTemperature();
      temperatura_dht_zew_min=temperatura_dht_zew;
      dzien_temperatura_dht_zew_min = now.day();
      miesiac_temperatura_dht_zew_min = now.month();
      rok_temperatura_dht_zew_min = now.year();
      pozycja_markera=1;
      licznik=1;
      tempZew_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temperatura_dht_zew = dht_zew.readTemperature();
      temperatura_dht_zew_min=temperatura_dht_zew;
      dzien_temperatura_dht_zew_min = now.day();
      miesiac_temperatura_dht_zew_min = now.month();
      rok_temperatura_dht_zew_min = now.year();
      pozycja_markera=2;
      licznik=2;
      tempZew_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temperatura_dht_zew = dht_zew.readTemperature();
      temperatura_dht_zew_max=temperatura_dht_zew;
      dzien_temperatura_dht_zew_max = now.day();
      miesiac_temperatura_dht_zew_max = now.month();
      rok_temperatura_dht_zew_max = now.year();
      pozycja_markera=3;
      licznik=3;
      tempZew_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temperatura_dht_zew = dht_zew.readTemperature();
      temperatura_dht_zew_max=temperatura_dht_zew;
      dzien_temperatura_dht_zew_max = now.day();
      miesiac_temperatura_dht_zew_max = now.month();
      rok_temperatura_dht_zew_max = now.year();
      pozycja_markera=4;
      licznik=4;
      tempZew_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temperatura_dht_zew = dht_zew.readTemperature();
      temperatura_dht_zew_min=temperatura_dht_zew;
      dzien_temperatura_dht_zew_min = now.day();
      miesiac_temperatura_dht_zew_min = now.month();
      rok_temperatura_dht_zew_min = now.year();
      temperatura_dht_zew_max=temperatura_dht_zew;
      dzien_temperatura_dht_zew_max = now.day();
      miesiac_temperatura_dht_zew_max = now.month();
      rok_temperatura_dht_zew_max = now.year();
      pozycja_markera=5;
      licznik=5;
      tempZew_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_wilgZew(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    wilgZew();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      DateTime now = czas.now();
      wilgotnosc_dht_zew = dht_zew.readHumidity();
      wilgotnosc_dht_zew_min=wilgotnosc_dht_zew;
      dzien_wilgotnosc_dht_zew_min = now.day();
      miesiac_wilgotnosc_dht_zew_min = now.month();
      rok_wilgotnosc_dht_zew_min = now.year();
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      wilgZew_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      wilgotnosc_dht_zew = dht_zew.readHumidity();
      wilgotnosc_dht_zew_min = wilgotnosc_dht_zew;
      dzien_wilgotnosc_dht_zew_min = now.day();
      miesiac_wilgotnosc_dht_zew_min = now.month();
      rok_wilgotnosc_dht_zew_min = now.year();
      pozycja_markera=2;
      licznik=2;
      wilgZew_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      wilgotnosc_dht_zew = dht_zew.readHumidity();
      wilgotnosc_dht_zew_max = wilgotnosc_dht_zew;
      dzien_wilgotnosc_dht_zew_max = now.day();
      miesiac_wilgotnosc_dht_zew_max = now.month();
      rok_wilgotnosc_dht_zew_max = now.year();
      pozycja_markera=3;
      licznik=3;
      wilgZew_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      wilgotnosc_dht_zew = dht_zew.readHumidity();
      wilgotnosc_dht_zew_max = wilgotnosc_dht_zew;
      dzien_wilgotnosc_dht_zew_max = now.day();
      miesiac_wilgotnosc_dht_zew_max = now.month();
      rok_wilgotnosc_dht_zew_max = now.year();
      pozycja_markera=4;
      licznik=4;
      wilgZew_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      wilgotnosc_dht_zew = dht_zew.readHumidity();
      wilgotnosc_dht_zew_min = wilgotnosc_dht_zew;
      dzien_wilgotnosc_dht_zew_min = now.day();
      miesiac_wilgotnosc_dht_zew_min = now.month();
      rok_wilgotnosc_dht_zew_min = now.year();
      wilgotnosc_dht_zew_max = wilgotnosc_dht_zew;
      dzien_wilgotnosc_dht_zew_max = now.day();
      miesiac_wilgotnosc_dht_zew_max = now.month();
      rok_wilgotnosc_dht_zew_max = now.year();
      pozycja_markera=5;
      licznik=5;
      wilgZew_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_tempGrunt(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    tempGrunt();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_grunt = sensors.getTempC(termometr_grunt);
      temp_grunt_min=temp_grunt;
      dzien_temp_grunt_min = now.day();
      miesiac_temp_grunt_min = now.month();
      rok_temp_grunt_min = now.year();
      pozycja_markera=1;
      licznik=1;
      tempGrunt_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_grunt = sensors.getTempC(termometr_grunt);
      temp_grunt_min=temp_grunt;
      dzien_temp_grunt_min = now.day();
      miesiac_temp_grunt_min = now.month();
      rok_temp_grunt_min = now.year();
      pozycja_markera=2;
      licznik=2;
      tempGrunt_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_grunt = sensors.getTempC(termometr_grunt);
      temp_grunt_max=temp_grunt;
      dzien_temp_grunt_max = now.day();
      miesiac_temp_grunt_max = now.month();
      rok_temp_grunt_max = now.year();
      pozycja_markera=3;
      licznik=3;
      tempGrunt_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_grunt = sensors.getTempC(termometr_grunt);
      temp_grunt_max=temp_grunt;
      dzien_temp_grunt_max = now.day();
      miesiac_temp_grunt_max = now.month();
      rok_temp_grunt_max = now.year();
      pozycja_markera=4;
      licznik=4;
      tempGrunt_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_grunt = sensors.getTempC(termometr_grunt);
      temp_grunt_min=temp_grunt;
      dzien_temp_grunt_min = now.day();
      miesiac_temp_grunt_min = now.month();
      rok_temp_grunt_min = now.year();
      temp_grunt_max=temp_grunt;
      dzien_temp_grunt_max = now.day();
      miesiac_temp_grunt_max = now.month();
      rok_temp_grunt_max = now.year();
      pozycja_markera=5;
      licznik=5;
      tempGrunt_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_tempSlonce(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    tempSlonce();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_slonce = sensors.getTempC(termometr_slonce);
      temp_slonce_min=temp_slonce;
      dzien_temp_slonce_min = now.day();
      miesiac_temp_slonce_min = now.month();
      rok_temp_slonce_min = now.year(); 
      pozycja_markera=1;
      licznik=1;
      tempSlonce_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_slonce = sensors.getTempC(termometr_slonce);
      temp_slonce_min=temp_slonce;
      dzien_temp_slonce_min = now.day();
      miesiac_temp_slonce_min = now.month();
      rok_temp_slonce_min = now.year(); 
      pozycja_markera=2;
      licznik=2;
      tempSlonce_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_slonce = sensors.getTempC(termometr_slonce);
      temp_slonce_max=temp_slonce;
      dzien_temp_slonce_max = now.day();
      miesiac_temp_slonce_max = now.month();
      rok_temp_slonce_max = now.year(); 
      pozycja_markera=3;
      licznik=3;
      tempSlonce_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear();
      DateTime now = czas.now();
      temp_slonce = sensors.getTempC(termometr_slonce);
      temp_slonce_max=temp_slonce;
      dzien_temp_slonce_max = now.day();
      miesiac_temp_slonce_max = now.month();
      rok_temp_slonce_max = now.year(); 
      pozycja_markera=4;
      licznik=4;
      tempSlonce_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_slonce = sensors.getTempC(termometr_slonce);
      temp_slonce_min=temp_slonce;
      dzien_temp_slonce_min = now.day();
      miesiac_temp_slonce_min = now.month();
      rok_temp_slonce_min = now.year(); 
      temp_slonce_max=temp_slonce;
      dzien_temp_slonce_max = now.day();
      miesiac_temp_slonce_max = now.month();
      rok_temp_slonce_max = now.year(); 
      pozycja_markera=5;
      licznik=5;
      tempSlonce_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_tempCO(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    tempCO();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_CO = sensors.getTempC(termometr_CO);
      temp_CO_min=temp_CO;
      dzien_temp_CO_min = now.day();
      miesiac_temp_CO_min = now.month();
      rok_temp_CO_min = now.year();
      pozycja_markera=1;
      licznik=1;
      tempCO_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_CO = sensors.getTempC(termometr_CO);
      temp_CO_min=temp_CO;
      dzien_temp_CO_min = now.day();
      miesiac_temp_CO_min = now.month();
      rok_temp_CO_min = now.year();
      pozycja_markera=2;
      licznik=2;
      tempCO_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_CO = sensors.getTempC(termometr_CO);
      temp_CO_max=temp_CO;
      dzien_temp_CO_max = now.day();
      miesiac_temp_CO_max = now.month();
      rok_temp_CO_max = now.year();
      pozycja_markera=3;
      licznik=3;
      tempCO_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_CO = sensors.getTempC(termometr_CO);
      temp_CO_max=temp_CO;
      dzien_temp_CO_max = now.day();
      miesiac_temp_CO_max = now.month();
      rok_temp_CO_max = now.year();
      pozycja_markera=4;
      licznik=4;
      tempCO_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      temp_CO = sensors.getTempC(termometr_CO);
      temp_CO_min=temp_CO;
      dzien_temp_CO_min = now.day();
      miesiac_temp_CO_min = now.month();
      rok_temp_CO_min = now.year();
      temp_CO_max=temp_CO;
      dzien_temp_CO_max = now.day();
      miesiac_temp_CO_max = now.month();
      rok_temp_CO_max = now.year();
      pozycja_markera=5;
      licznik=5;
      tempCO_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}
void wait_and_checkButton_tempStrych(){ //czekamy czas(interval) i ciągle sprawdzamy przycisk
  while(millis() - time1 <czekanie){
    kontrola_przekazniki();
   pozycja_enkodera();
   if(pozycja_markera != pozycja_markera_poprzednia){
    pozycja_markera_poprzednia = pozycja_markera;
    krotki_ping();
    time1=millis();// jesli pokrecone enkoderem, reset odliczania intervalu
    lcd.clear();
    tempStrych();
   }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==1)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      sensors.requestTemperatures(); 
      temp_strych = sensors.getTempC(termometr_strych);
      temp_strych_min=temp_strych;
      dzien_temp_strych_min = now.day();
      miesiac_temp_strych_min = now.month();
      rok_temp_strych_min = now.year();
      pozycja_markera=1;
      licznik=1;
      tempStrych_1();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==2)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      sensors.requestTemperatures(); 
      temp_strych = sensors.getTempC(termometr_strych);
      temp_strych_min=temp_strych;
      dzien_temp_strych_min = now.day();
      miesiac_temp_strych_min = now.month();
      rok_temp_strych_min = now.year();
      pozycja_markera=2;
      licznik=2;
      tempStrych_2();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==3)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      sensors.requestTemperatures(); 
      temp_strych = sensors.getTempC(termometr_strych);
      temp_strych_max=temp_strych;
      dzien_temp_strych_max = now.day();
      miesiac_temp_strych_max = now.month();
      rok_temp_strych_max = now.year();
      pozycja_markera=3;
      licznik=3;
      tempStrych_3();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==4)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      sensors.requestTemperatures(); 
      temp_strych = sensors.getTempC(termometr_strych);
      temp_strych_max=temp_strych;
      dzien_temp_strych_max = now.day();
      miesiac_temp_strych_max = now.month();
      rok_temp_strych_max = now.year();
      pozycja_markera=4;
      licznik=4;
      tempStrych_4();
    }
    if((digitalRead(PinP) ==LOW) && (pozycja_markera==5)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      DateTime now = czas.now();
      sensors.requestTemperatures(); 
      temp_strych = sensors.getTempC(termometr_strych);
      temp_strych_min=temp_strych;
      dzien_temp_strych_min = now.day();
      miesiac_temp_strych_min = now.month();
      rok_temp_strych_min = now.year();
      temp_strych_max=temp_strych;
      dzien_temp_strych_max = now.day();
      miesiac_temp_strych_max = now.month();
      rok_temp_strych_max = now.year();
      pozycja_markera=5;
      licznik=5;
      tempStrych_5();
    }
   if((digitalRead(PinP) ==LOW) && (pozycja_markera==6)){
        delay(30);
        ping();
        time1 =millis(); 
      lcd.clear(); 
      pozycja_markera=1;
      licznik=1;
      menu_opcje();
    }
   }
    if(millis() - time1 >czekanie){
    lcd.clear(); 
    glowny.restart();
    menu_1=JEDEN;
    menu_glowne();
    }
}



void check_connect() //procedura wywoływana co 1 sek
{
  if (Blynk.connected()) {
    liczreconnect = treconnect;
  } else {
    liczreconnect--;
    if (liczreconnect==0) {
      Blynk.connect();
      liczreconnect = treconnect;
    }
  }
}
void miganieLED(){
  if(blynkMiganie.available()){
   blueLED = !blueLED ;
   if (blueLED == 0) {
    led1.off(); //miganie vLED dla kontroli połączenia
   }
     else {
    led1.on();
    }
    blynkMiganie.restart();
}
}
 



void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensors.begin();
  dht_wew.begin();
  dht_zew.begin();
  bme.begin();
  //czas.adjust(DateTime(__DATE__, __TIME__));
  czas.begin();
  lcd.init(); 
  LED.begin(); 
  LED.show(); 
  
 glowny.begin(1489);
 sekunda.begin(750);
 blynkMiganie.begin(999);
 czujniki.begin(59000);
 sekunddwie.begin(2058);
 blynkConnect.begin(19995);
 alarm_led.begin(495);
  
  Blynk.config(auth);
  Blynk.connect();
  Blynk.begin(auth);
  
  
  lcd.backlight(); // zalaczenie podwietlenia 
  poprzedni_brama_garaz=brama_garaz;
  poprzedni_lampa_plac=lampa_plac;
  poprzedni_lampa_ogrod=lampa_ogrod;
  poprzedni_furtka=furtka;
  poprzedni_dodatkowy1=dodatkowy1;
  poprzedni_dodatkowy2=dodatkowy2;
  poprzedni_dodatkowy3=dodatkowy3;
  poprzedni_dodatkowy4=dodatkowy4;
 
  pinMode(lampa_plac_przekaznik, OUTPUT);
  pinMode(lampa_plac_wlacznik, INPUT);
  pinMode(lampa_ogrod_przekaznik, OUTPUT);
  pinMode(lampa_ogrod_wlacznik, INPUT);
  pinMode(brama_garaz_krancowka, INPUT);
  pinMode(brama_garaz_przekaznik, OUTPUT);
  pinMode(furtka_przekaznik, OUTPUT);
  pinMode(furtka_wlacznik, INPUT);
  pinMode(dodatkowy1_przekaznik, OUTPUT);
  pinMode(dodatkowy1_wlacznik, INPUT);
  pinMode(dodatkowy2_przekaznik, OUTPUT);
  pinMode(dodatkowy2_wlacznik, INPUT);
  pinMode(dodatkowy3_przekaznik, OUTPUT);
  pinMode(dodatkowy3_wlacznik, INPUT);
  pinMode(dodatkowy4_przekaznik, OUTPUT);
  pinMode(dodatkowy4_wlacznik, INPUT);
  pinMode(pin_alarm_pralka, INPUT);
  pinMode(pin_alarm_deszcz, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  digitalWrite(lampa_plac_przekaznik, HIGH);
  digitalWrite(lampa_ogrod_przekaznik, HIGH);
  digitalWrite(brama_garaz_przekaznik, HIGH);
  digitalWrite(furtka_przekaznik, HIGH);
  digitalWrite(dodatkowy1_przekaznik, HIGH);
  digitalWrite(dodatkowy2_przekaznik, HIGH);
  digitalWrite(dodatkowy3_przekaznik, HIGH);
  digitalWrite(dodatkowy4_przekaznik, HIGH);
  
  
  pinMode(PinA,INPUT); 
  pinMode(PinB,INPUT); 
  pinMode(PinP,INPUT_PULLUP); 
  
  attachInterrupt(digitalPinToInterrupt(3), blinkA, HIGH);  
  attachInterrupt(digitalPinToInterrupt(2), blinkB, HIGH);  
  time = millis(); 
  time1=millis(); 
  
  sensors.requestTemperatures(); 
  temp_strych = sensors.getTempC(termometr_strych);
  temp_slonce = sensors.getTempC(termometr_slonce);
  temp_grunt = sensors.getTempC(termometr_grunt);
  temp_CO = sensors.getTempC(termometr_CO);
  temperatura_dht_kuchnia=dht_wew.readTemperature();
  wilgotnosc_dht_kuchnia=dht_wew.readHumidity();
  cisnienie_bmp_strych=bme.readPressure()/100;
  temperatura_bmp_piwnica= bme.readTemperature();
  
  wilgotnosc_dht_zew = dht_zew.readHumidity();
  temperatura_dht_zew = dht_zew.readTemperature();
  temperatura_dht_zew_max = temperatura_dht_zew;
  temperatura_dht_zew_min = temperatura_dht_zew;
  wilgotnosc_dht_zew_max = wilgotnosc_dht_zew;
  wilgotnosc_dht_zew_min = wilgotnosc_dht_zew;
  cisnienie_bmp_strych_max = cisnienie_bmp_strych;
  cisnienie_bmp_strych_min = cisnienie_bmp_strych;
  temperatura_bmp_piwnica_max = temperatura_bmp_piwnica;
  temperatura_bmp_piwnica_min = temperatura_bmp_piwnica;
  temp_strych_max = temp_strych;
  temp_strych_min = temp_strych;
  temp_slonce_max = temp_slonce; 
  temp_slonce_min = temp_slonce;
  temp_grunt_max = temp_grunt; 
  temp_grunt_min = temp_grunt;
  temp_CO_max = temp_CO; 
  temp_CO_min = temp_CO;
  temperatura_dht_kuchnia_max = temperatura_dht_kuchnia;
  temperatura_dht_kuchnia_min = temperatura_dht_kuchnia;
  wilgotnosc_dht_kuchnia_max = wilgotnosc_dht_kuchnia;
  wilgotnosc_dht_kuchnia_min = wilgotnosc_dht_kuchnia;

  DateTime now = czas.now();
    dzien_temp_strych_max = now.day();
    miesiac_temp_strych_max = now.month();
    rok_temp_strych_max = now.year();
    dzien_temp_strych_min = now.day();
    miesiac_temp_strych_min = now.month();
    rok_temp_strych_min = now.year();
    dzien_temp_slonce_max = now.day();
    miesiac_temp_slonce_max = now.month();
    rok_temp_slonce_max = now.year();
    dzien_temp_slonce_min = now.day();
    miesiac_temp_slonce_min = now.month();
    rok_temp_slonce_min = now.year();
    dzien_temp_grunt_max = now.day();
    miesiac_temp_grunt_max = now.month();
    rok_temp_grunt_max = now.year();
    dzien_temp_grunt_min = now.day();
    miesiac_temp_grunt_min = now.month();
    rok_temp_grunt_min = now.year();
    dzien_temp_CO_max = now.day();
    miesiac_temp_CO_max = now.month();
    rok_temp_CO_max = now.year();
    dzien_temp_CO_min = now.day();
    miesiac_temp_CO_min = now.month();
    rok_temp_CO_min = now.year();
    dzien_temperatura_dht_kuchnia_max = now.day();
    miesiac_temperatura_dht_kuchnia_max = now.month();
    rok_temperatura_dht_kuchnia_max = now.year();
    dzien_temperatura_dht_kuchnia_min = now.day();
    miesiac_temperatura_dht_kuchnia_min = now.month();
    rok_temperatura_dht_kuchnia_min = now.year();
    dzien_wilgotnosc_dht_kuchnia_max = now.day();
    miesiac_wilgotnosc_dht_kuchnia_max = now.month();
    rok_wilgotnosc_dht_kuchnia_max = now.year();
    dzien_wilgotnosc_dht_kuchnia_min = now.day();
    miesiac_wilgotnosc_dht_kuchnia_min = now.month();
    rok_wilgotnosc_dht_kuchnia_min = now.year();
    dzien_cisnienie_bmp_strych_max = now.day();
    miesiac_cisnienie_bmp_strych_max = now.month();
    rok_cisnienie_bmp_strych_max = now.year();
    dzien_cisnienie_bmp_strych_min = now.day();
    miesiac_cisnienie_bmp_strych_min = now.month();
    rok_cisnienie_bmp_strych_min = now.year();
    dzien_temperatura_bmp_piwnica_max = now.day();
    miesiac_temperatura_bmp_piwnica_max = now.month();
    rok_temperatura_bmp_piwnica_max = now.year();
    dzien_temperatura_bmp_piwnica_min = now.day();
    miesiac_temperatura_bmp_piwnica_min = now.month();
    rok_temperatura_bmp_piwnica_min = now.year();
    dzien_wilgotnosc_dht_zew_max = now.day();
    miesiac_wilgotnosc_dht_zew_max = now.month();
    rok_wilgotnosc_dht_zew_max = now.year();
    dzien_wilgotnosc_dht_zew_min = now.day();
    miesiac_wilgotnosc_dht_zew_min = now.month();
    rok_wilgotnosc_dht_zew_min = now.year();
    dzien_temperatura_dht_zew_max = now.day();
    miesiac_temperatura_dht_zew_max = now.month();
    rok_temperatura_dht_zew_max = now.year();
    dzien_temperatura_dht_zew_min = now.day();
    miesiac_temperatura_dht_zew_min = now.month();
    rok_temperatura_dht_zew_min = now.year();
 }

void loop() {

  if(blynkConnect.available()){
   check_connect();
   blynkConnect.restart();
  }
  if (Blynk.connected()) {
   Blynk.run();
  }
 brama();
   menu_glowne(); 
   miganieLED(); 
   
//   testconnect();
 
}
