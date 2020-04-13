
#define TEMPERATURE_SENSOR_PIN 1

int val;

float ReadTemperature() {
  val = analogRead(TEMPERATURE_SENSOR_PIN);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  return cel;
}

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  float temp = ReadTemperature();
  Serial.print("TEMPERATURE = ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  delay(1000);
}
