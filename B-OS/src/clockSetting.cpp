#include <clockSetting.h>
#include <includes.h>
#include <defines.h>

extern RTC_DS3231 rtc;

char ayar_saat;
char ayar_dakka;
char ayar_saniye;
short ayar_yil;
char ayar_ay;
char ayar_gun;
int ayar_secim = 0;
char ayar_degisti = 0;

void clockSetting()
{
    DateTime now;

    if (menu == 3)
    {
        if (digitalRead(sw3) == LOW)
        {
            delay(150);
            if (ayar_secim == 0)
            {
                ayar_saat = ayar_saat + 1;
            }
            if (ayar_secim == 1)
            {
                ayar_dakka = ayar_dakka + 1;
            }
            if (ayar_secim == 2)
            {
                ayar_saniye = ayar_saniye + 1;
            }
            if (ayar_secim == 3)
            {
                ayar_gun = ayar_gun + 1;
            }
            if (ayar_secim == 4)
            {
                ayar_ay = ayar_ay + 1;
            }
            if (ayar_secim == 5)
            {
                ayar_yil = ayar_yil + 1;
            }
        }
        if (digitalRead(sw1) == LOW)
        {
            delay(300);
            ayar_secim = ayar_secim + 1;
            if (ayar_secim >= 6)
            {
                ayar_secim = 0;
            }
        }
        if (ayar_saat >= 24)
        {
            ayar_saat = 0;
        }
        if (ayar_dakka >= 60)
        {
            ayar_dakka = 0;
        }
        if (ayar_saniye >= 60)
        {
            ayar_saniye = 0;
        }
        if (ayar_gun >= 31)
        {
            ayar_gun = 0;
        }
        if (ayar_ay >= 13)
        {
            ayar_ay = 0;
        }
        if (ayar_yil >= 2103)
        {
            ayar_yil = 2003;
        }
        displayTimeSetting();
    }
    if (menu == 3 && ((now.hour() != ayar_saat) || (now.minute() != ayar_dakka) || (now.second() != ayar_saniye)))
    {
        ayar_degisti = 1;
    }
    if (menu == 0 && ayar_degisti == 1)
    {
        //DateTime now;
        //rtc.adjust(DateTime(ayar_yil, ayar_ay, ayar_gun, ayar_saat, ayar_dakka, ayar_saniye));
        DateTime realTime(DateTime(ayar_yil, ayar_ay, ayar_gun, ayar_saat, ayar_dakka, ayar_saniye));
        rtc.adjust(realTime);
        ayar_degisti = 0;
        DateTime now(ayar_yil, ayar_ay, ayar_gun, ayar_saat, ayar_dakka, ayar_saniye);
    }
    if (menu == 0)
    {
        ayar_secim = 0;
    }
}