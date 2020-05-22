#include <battery.h>
#include <includes.h>
#include <defines.h>

float vDiv = R2/(R1+R2);
float voltage;

void readBattery()
{
    digitalWrite(battEn, HIGH);
    delay(50);
    voltage = analogRead(bPin);
    voltage = (voltage / 1024) * 3.35;
    voltage = voltage / vDiv;
    delay(50);
    digitalWrite(battEn, LOW);
}