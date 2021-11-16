/*
 * REWS_Station.ino
 * Description: The weather station currently keeps track of weather and humidity. All other values
 * are generated using random values. After gathering weather data, the weather station sends it
 * serially to the Raspberry Pi.
 * 
 * Version 0.1 Set up Temp Structure and Serial Communication -Brendan Aguiar
 */
//Temperature/Humidity Globals
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE    DHT11   
DHT_Unified dht(DHTPIN, DHTTYPE);
#define STRUCT_SIZE 24 //Size float * number of float datapoints
byte Data[STRUCT_SIZE];//Data to send to Raspberry Pi
struct Weather {
  float temp;//temperature
  float hum;//humidity
  float pres;//pressure
  float dens;//particulate density for Air Quality
  float w_dir;//wind direction
  float w_spd;//wind speed
} W_Data;//Weather data object

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  RecordData();//UC16
  InsertData();//UC10
  delay(1000);
}
void RecordData()
{
  Get_Hum_Temp();
  get_random_values();
}
void get_random_values()//to use in place of vacant sensors
{
  float rand_float = (float)random(94,103) / (float) random(94,103);
  W_Data.pres = (float) random(999,1019) * rand_float; //generate random float
  W_Data.dens = (float) random(20,25) * rand_float;
  W_Data.w_dir = (float) random(220,250) * rand_float;  
  W_Data.w_spd = (float) random(3, 5) * rand_float;
}
void InsertData()
{
  for (int i = 0; i < 4; i++)
  {
    Data[i] = (byte)((long)W_Data.temp >> (24 - (8 * i)) & 0xFF);
    Data[i + 4] = (byte)((unsigned long)W_Data.hum >> (24 - (8 * i)) & 0xFF);
    Data[i + 8] = (byte)((unsigned long)W_Data.pres >> (24 - (8 * i)) & 0xFF);
    Data[i + 12] = (byte)((unsigned long)W_Data.dens >> (24 - (8 * i)) & 0xFF);
    Data[i + 16] = (byte)((unsigned long)W_Data.w_dir >> (24 - (8 * i)) & 0xFF);
    Data[i + 20] = (byte)((unsigned long)W_Data.w_spd >> (24 - (8 * i)) & 0xFF);
  }
  for (int i = 0; i < 24; i++)
    Serial.print(Data[i]);
 /* Serial.print("\n");
  Serial.print("Temp: ");
  Serial.print(W_Data.temp);
  Serial.print(", Humidity: ");
  Serial.println(W_Data.hum);
  Serial.print("Pressure: ");
  Serial.print(W_Data.pres);
  Serial.print(", Air Quality: ");
  Serial.println(W_Data.dens);
  Serial.print("Wind Dir.: ");
  Serial.print(W_Data.w_dir);
  Serial.print("Wind Speed :");
  Serial.println(W_Data.w_spd);
  */
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