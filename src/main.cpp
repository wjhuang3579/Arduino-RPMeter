#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <TimerOne.h>

#define __AVR_ATmega32u4__
#define ddtick  __asm__("nop\n\t"); 

unsigned long counters = 0;
unsigned long rpm_c = 0;
unsigned long rpm = 0;

void counters_rpm();
void counters_count();

void counters_rpm(){
  rpm_c = counters/2;
  counters=0;
  rpm = rpm_c * 1 * 60;
}

void counters_count(){
  counters++;
}

void setup()
{
  Serial.begin(115200);
  Timer1.initialize(1000000);//1000ms
  Timer1.attachInterrupt(counters_rpm);
  pinMode(7, INPUT);
  attachInterrupt(digitalPinToInterrupt(7), counters_count,FALLING);
}

void loop() 
{
  Serial.print(rpm/1000);
  Serial.print(F(","));
  Serial.print((rpm/100)%10);
  Serial.print((rpm/10)%10);
  Serial.print(rpm%10);
  Serial.print(F(" rpm\r\n"));
  delay(1000);
}