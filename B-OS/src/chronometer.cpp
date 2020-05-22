#include <chronometer.h>
#include <defines.h>
#include <Arduino.h>
#include <display.h>

char kronometre_salise;
char kronometre_saniye;
char kronometre_dakka;
char kronometre_saat;
char kronometre_basla = 0;

void chronometer(){
    if (menu == 1)
  {
    if (digitalRead(sw3) == LOW)
    {
      kronometre_basla = !kronometre_basla;
      delay(150);
    }
    if (kronometre_basla == 1)
    {
      kronometre_salise = kronometre_salise + 1;
      if (kronometre_salise >= 60)
      {
        kronometre_salise = 0;
        kronometre_saniye = kronometre_saniye + 1;
        if (kronometre_saniye >= 60)
        {
          kronometre_saniye = 0;
          kronometre_dakka = kronometre_dakka + 1;
          if (kronometre_dakka >= 60)
          {
            kronometre_dakka = 0;
            kronometre_saat = kronometre_saat + 1;
          }
        }
      }
    }

    if (kronometre_basla == 0)
    {
      if (digitalRead(sw1) == LOW)
      {
        kronometre_saat = 0;
        kronometre_dakka = 0;
        kronometre_saniye = 0;
        kronometre_salise = 0;
      }
    }
    displayChronometer();
  }
}