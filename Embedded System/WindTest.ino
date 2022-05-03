//Weather Vane Assignments
#define A_PIN 3 //Anemometer
#define W_PIN A3 //Wind Vane
int W_voltage, D_voltage, counter;//values for voltage reads

//Weather data structure
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
  pinMode(A_PIN, INPUT);
  pinMode(W_PIN, INPUT);
}

void loop() {
  //Get_Wind_Dir();
  Get_Wind_Spd();
  Serial.print("Wind Direction: ");
  Serial.println(W_Data.w_dir);
  Serial.print("Wind Speed (Mph): ");
  Serial.println(W_Data.w_spd);
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
  attachInterrupt(digitalPinToInterrupt(A_PIN), Count, FALLING);//increment on rising button push
  delay(1000);//Delay for 1 second interrupt keeps track of the counter
  detachInterrupt(digitalPinToInterrupt(A_PIN));
  W_Data.w_spd = (float)counter * (float)2.4 * (float).62137;//Speed in Miles Per Hour
}
void Count()
{
  counter++;
}
