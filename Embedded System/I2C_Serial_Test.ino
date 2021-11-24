/*
The following code is used to test multiple streams
of communication from two I2C devices (DS1307, GY-521) and one 
serial device (DHT11). This is in preparation for hooking up the
weather station, which will have similar communication protocals.
-Brendan Aguiar
*/

//Temperature/Humidity Globals
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE    DHT11   
DHT_Unified dht(DHTPIN, DHTTYPE);
//Real Time Clock Globals
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Wire.h>
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
tmElements_t tm;

//Gyroscope Globals
const int MPU_ADDR=0x68; //I2C address of AD0 pin is LOE, address 0x68
int16_t gyro_x, gyro_y, gyro_z;
char tmp_str[7]; //used in convert function
char* convert_int16_to_str(int16_t i) 
{ // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void setup() 
{
  dht.begin();
  set_time();//RTC
  //I2C
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  //Gyroscope
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() 
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43); // starting with register 0x43 (GYRO_XOUT_L) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 6, true); //request 6 registers
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  uint8_t h;
  uint8_t m;
  uint8_t s;
  if (RTC.read(tm)) 
  {//DS1307 library handles Wire transmission
    h = tm.Hour;
    m = tm.Minute;
    s = tm.Second;
  }
  Serial.print("\nCurrent Time: ");
  Serial.print(h);
  Serial.print(':');
  Serial.print(m);
  Serial.write(':');
  Serial.print(s);  
  Serial.println();
  print_temp();
  // delay
  delay(1000);
}

void set_time()
{
  bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) 
  {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) 
      config = true;
  }
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) 
  {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } 
  else if (parse) 
  {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } 
  else 
  {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) 
    return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) 
    return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) 
  {
    if (strcmp(Month, monthName[monthIndex]) == 0) 
      break;
  }
  if (monthIndex >= 12) 
    return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
void print_temp()
{
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
    Serial.println(F("Error reading temperature!"));
  else 
  {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
    Serial.println(F("Error reading humidity!"));
  else 
  {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
