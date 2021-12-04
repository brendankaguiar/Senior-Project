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
  float w_dir;//wind direction
  float w_spd;//wind speed
} W_Data;//Weather data object

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  RecordData();//UC..%need to change name according to P3 schematics

  InsertData();//UC.. %^^
  //ReceiveData();
  //clearData();
  delay(2000);
}
void clearData()
{
  
  for (int i = 0; i < STRUCT_SIZE; i++)
    Data[i] = 0;//clear data to prep for receiving new data
   
}
void ReceiveData(){//Test function to make sure bits of W_Data are unpacked correctly
  Serial.readBytesUntil('\n', Data, sizeof(Data)); 
  float temp_loc = ((byte)Data[0] << 24) 
                     + ((byte)Data[1] << 16) 
                     + ((byte)Data[2] << 8) 
                     + ((byte)Data[3]);
      float hum_loc = ((byte)Data[4] << 24) 
                     + ((byte)Data[5] << 16) 
                     + ((byte)Data[6] << 8) 
                     + ((byte)Data[7]);
      float pres_loc = ((byte)Data[8] << 24) 
                     + ((byte)Data[9] << 16) 
                     + ((byte)Data[10] << 8) 
                     + ((byte)Data[11]);
      float dens_loc = ((byte)Data[12] << 24) 
                     + ((byte)Data[13] << 16) 
                     + ((byte)Data[14] << 8) 
                     + ((byte)Data[15]);
      float w_dir_loc = ((byte)Data[16] << 24) 
                     + ((byte)Data[17] << 16) 
                     + ((byte)Data[18] << 8) 
                     + ((byte)Data[19]);
      float w_spd_loc = ((byte)Data[20] << 24) 
                     + ((byte)Data[21] << 16) 
                     + ((byte)Data[22] << 8) 
                     + ((byte)Data[23]);     
  Serial.print("Printing Real Values: "); 
  Serial.print("Temp in Celcuius = ");
  Serial.print(temp_loc);
  Serial.print(" Hu in % = ");
  Serial.println(hum_loc);
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
  /*
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
  Serial.println(WD);
  */
  /*
  for (int i = 0; i < 4; i++)
  {
    //(byte to type's current index = temp byte shifted the total size from the indexed position
    Data[i] = (byte)((long)W_Data.temp >> (24 - (8 * i)) & 0xFF);//& 0xFF is added to preserve bit places
    Data[i + 4] = (byte)((unsigned long)W_Data.hum >> (24 - (8 * i)) & 0xFF);
    Data[i + 8] = (byte)((unsigned long)W_Data.pres >> (24 - (8 * i)) & 0xFF);
    Data[i + 12] = (byte)((unsigned long)W_Data.dens >> (24 - (8 * i)) & 0xFF);
    Data[i + 16] = (byte)((unsigned long)W_Data.w_dir >> (24 - (8 * i)) & 0xFF);
    Data[i + 20] = (byte)((unsigned long)W_Data.w_spd >> (24 - (8 * i)) & 0xFF);
  }*/
  //Serial.println(Data);
  
  //Serial.print("Printing binary Data: ");
  f_Data[0] = W_Data.temp;
  f_Data[1] = W_Data.hum;
  f_Data[2] = W_Data.pres;
  f_Data[3] = W_Data.dens;
  f_Data[4] = W_Data.w_dir;
  f_Data[5] = W_Data.w_spd;
  Serial.println('$');//send start symbol
  for(int i = 0; i < STRUCT_ELEMS; i++)
    Serial.println(f_Data[i]);//send data
  /*  
  Serial.print(W_Data.temp);
  Serial.print(',');
  Serial.print(W_Data.hum);
  Serial.print(',');
  Serial.print(W_Data.pres);
  Serial.print(',');
  Serial.print(W_Data.dens);
  Serial.print(',');
  Serial.print(W_Data.w_dir);
  Serial.print(',');
  Serial.print(W_Data.w_spd);
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