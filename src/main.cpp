#include <Arduino.h>
#include <SSD1306.h>
SSD1306   display(0x3c, 4, 5, GEOMETRY_128_32);

int val = 0;
int LED = 15;
float avg = 0;
float pre_avg = 0;
float alpha = 0.1;
char str_val[5];
char str_avg[10];

void setup() 
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.display();

  val = analogRead(0);
  Serial.println(val);

  avg = val*alpha + (1 - alpha)*pre_avg;
  pre_avg = avg;
  itoa(val, str_val, 10);

  snprintf(str_avg, sizeof(str_avg), "%.3f", avg);

  display.setColor(BLACK);
  display.fillRect(80, 11, 100, 33);
  display.setColor(WHITE);
  display.display();

  display.drawString(10, 10, str_val);
  display.drawString(70, 10, str_avg);
  display.display();

  if(val<200) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
  delay(500);
}