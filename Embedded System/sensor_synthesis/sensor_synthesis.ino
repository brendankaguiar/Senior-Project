





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

#include <Seeed_HM330X.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define Altitude 4505
#define DHTPIN 2
#define DHTTYPE    DHT11   
DHT_Unified dht(DHTPIN, DHTTYPE);

//Weather Vane Assignments
#define A_PIN 3 //Anemometer
#define W_PIN A3 //Wind Vane

SFE_BMP180 pSensor;
HM330X sensor;
uint8_t buf[30];
int W_voltage, D_voltage, counter;//values for voltage reads

const char* str[] = {"sensor num: ", "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                    };

HM330XErrorCode print_result(const char* str, uint16_t value) {
    if (NULL == str) {
        return ERROR_PARAM;
    }
    Serial.print(str);
    Serial.println(value);
    return NO_ERROR;
}

/*parse buf with 29 uint8_t-data*/
HM330XErrorCode parse_result(uint8_t* data) {
    uint16_t value = 0;
    if (NULL == data) {
        return ERROR_PARAM;
    }
    for (int i = 1; i < 8; i++) {
        value = (uint16_t) data[i * 2] << 8 | data[i * 2 + 1];
        print_result(str[i - 1], value);

    }

    return NO_ERROR;
}

HM330XErrorCode parse_result_value(uint8_t* data) {
    if (NULL == data) {
        return ERROR_PARAM;
    }
    Serial.println("");
    return NO_ERROR;
}


/*30s*/
void setup() {
    Serial.begin(9600);
    pSensor.begin();
    dht.begin();
    pinMode(A_PIN, INPUT);
    pinMode(W_PIN, INPUT);
    delay(100);
    Serial.println("Serial start");
    if (sensor.init()) {
        Serial.println("HM330X init failed!!");
        while (1);
    }

}


void loop() {
    getData();
    if (sensor.read_sensor_value(buf, 29)) {
        Serial.println("HM330X read result failed!!");
    }
    parse_result_value(buf);
    parse_result(buf);
    int value = analogRead(A3);
    Serial.println("Analog Read: ");
    Serial.print(value);
    Serial.println("");
    delay(5000);
}

void getData()
{
  Get_Hum_Temp();
  Get_Wind_Dir();
  Get_Wind_Spd();
  get_random_values();
  getPressure();
  sendData();
}

void getPressure()
{
  // put your main code here, to run repeatedly:
  //bool status;
  double T,AP,RP;
  pSensor.startTemperature();
  delay(100);
  pSensor.getTemperature(T);
  delay(100);
  pSensor.startPressure(3);
  delay(100);
  pSensor.getPressure(AP,T);
  Serial.print("Absolute Pressure: ");
  Serial.print((float)AP,4);
  Serial.print(" Millibars\n");
  RP = pSensor.sealevel(AP, Altitude);
  Serial.print("Relative to Sea Level Pressure: ");
  Serial.print((float)RP,4);
  Serial.print(" Millibars\n\n");
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
  WD += '\n';
  WD += String(W_Data.hum);
  WD += '\n';
  WD += String(W_Data.pres);
  WD += '\n';
  WD += String(W_Data.dens);
  WD += '\n';
  WD += String(W_Data.w_dir);
  WD += '\n';
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
  else if (W_voltage < 520 && W_voltage > 508)
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
