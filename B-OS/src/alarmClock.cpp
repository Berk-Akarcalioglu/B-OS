#include <alarmClock.h>
#include <defines.h>
#include <Arduino.h>
#include <display.h>

char calar_saat_saat;
char calar_saat_dakka;
char calar_saat_secim = 0;
char calar_saat_ac = 0;

char bzz = 0;

void alarmClock(){
    DateTime now;
  if (menu == 0)
  {
    if (digitalRead(sw1) == LOW && digitalRead(sw3) == LOW)
    {
      delay(400);
      calar_saat_ac = !calar_saat_ac;
    }
    if (calar_saat_saat == now.hour())
    {
      if (calar_saat_dakka == now.minute())
      {
        Serial.print("Alarm");
        if (calar_saat_ac == 1)
        {
          bzz = !bzz;
          delay(200);
          bzz = !bzz;
          while (bzz == 1)
          {
            delay(100);
          }
        }
      }
    }
  }
  displayAlarmClock();
}