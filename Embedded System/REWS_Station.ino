/*
 * REWS.ino
 * Description: The weather station currently keeps track of weather and humidity. All other values
 * are generated using random values. After gathering weather data, the weather station sends it
 * serially to the Raspberry Pi.
 * 
 * Version 0.1 Set up Temp Structure and Serial Communication -Brendan A.
 * Version 0.2 Successfuly Tested sending data as String WD and as series of floats f_Data -Brendan A.
 */
 
//Temperature/Humidity Globals
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE    DHT11   
DHT_Unified dht(DHTPIN, DHTTYPE);

//Weather Vane Assignments
#define A_PIN 3 //Anemometer
#define W_PIN A3 //Wind Vane
int W_voltage, D_voltage, counter;//values for voltage reads

//Weather Data Globals
#define STRUCT_SIZE 24 //Size of float * nr of struct members -> 4 * 6 
#define STRUCT_ELEMS 6 // number of elements in structure
char Data[STRUCT_SIZE];//Data to send to Raspberry Pi
float f_Data[STRUCT_ELEMS];
String WD; 
struct Weather {
  float temp;//temperature
  float hum;//humidity
  float pres;//pressure
  float dens;//particulate density for Air Quality
  String w_dir;//wind direction
  float w_spd;//wind speed
} W_Data;//Weather data object

void setup() {
  
  Serial.begin(9600);
  dht.begin();
  pinMode(A_PIN, INPUT);
  pinMode(W_PIN, INPUT);
}

void loop() {
  getData();//Retrievee data from sensors
  sendData();//Sends data to the Raspberry Pi
  delay(10000);//delays next loop for 60 seconds
}

void getData()
{
  Get_Hum_Temp();
  Get_Wind_Dir();
  Get_Wind_Spd();
  get_random_values();
}

void get_random_values()//to use in place of vacant sensors
{
  float rand_float = (float)random(94,103) / (float) random(94,103);//add more randomness
  W_Data.pres = (float) random(999,1019) * rand_float; //generate random float
  W_Data.dens = (float) random(20,25) * rand_float;
}

void sendData()
{
  //Serial.println('$');//send start symbol before data
  WD = String(W_Data.temp);
  WD += ',';
  WD += String(W_Data.hum);
  WD += ',';
  WD += String(W_Data.pres);
  WD += ',';
  WD += String(W_Data.dens);
  WD += ',';
  WD += String(W_Data.w_dir);
  WD += ',';
  WD += String(W_Data.w_spd);
  int val = WD.length();
  char buf[29];//check val if changing size
  WD.toCharArray(buf, val);
  Serial.println(buf);
}

void Get_Hum_Temp()
{
  sensors_event_t event;//create event object to load temp and hum
  dht.temperature().getEvent(&event);//get object values
  if (isnan(event.temperature))//check that value obtained
    Serial.println(F("Error reading temperature!"));
  else 
    W_Data.temp = event.temperature;//assign event to structure
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
    Serial.println(F("Error reading humidity!"));
  else 
    W_Data.hum = event.relative_humidity;
}

void Get_Wind_Dir()
{
  W_voltage = analogRead(W_PIN);
  if (W_voltage < 820 && W_voltage > 810)
    W_Data.w_dir = "S";
  else if (W_voltage < 970 && W_voltage > 960)
    W_Data.w_dir = "SW";
  else if (W_voltage < 1020 && W_voltage > 1010)
    W_Data.w_dir = "W";
  else if (W_voltage <= 1010 && W_voltage > 1005)
    W_Data.w_dir = "NW";
  else if (W_voltage < 1000 && W_voltage > 990)
    W_Data.w_dir = "N";
  else if (W_voltage < 920 && W_voltage > 910)
    W_Data.w_dir = "NE";
  else if (W_voltage < 517 && W_voltage > 508)
    W_Data.w_dir = "E";
  else if (W_voltage < 709 && W_voltage > 699)
    W_Data.w_dir = "SE";
}

void Get_Wind_Spd()
{
  counter = 0;
  attachInterrupt(digitalPinToInterrupt(A_PIN), Count, FALLING);//increment on active low button push
  delay(1000);//Delay for 1 second interrupt keeps track of the counter
  detachInterrupt(digitalPinToInterrupt(A_PIN));
  W_Data.w_spd = (float)counter * (float)2.4 * (float).62137;//Speed in Miles Per Hour
}

void Count()
{
  counter++;
}
