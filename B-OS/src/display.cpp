#include <display.h>
#include <includes.h>
#include <defines.h>
#include <chronometer.h>

bool disON = true;

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
extern RTC_DS3231 rtc;
extern Adafruit_BMP280 bme;

extern float voltage;

void displayInit()
{
    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    delay(100);
    display.display();
}

void clearDisplay()
{
    display.clearDisplay();
}

void displayDisplay()
{
    display.display();
}

void toggleDisplay()
{
    if (!digitalRead(sw1) && menu == 0)
    {
        if (disON)
        {
            display.ssd1306_command(SSD1306_DISPLAYOFF);
            disON = false;
        }
        else
        {
            display.ssd1306_command(SSD1306_DISPLAYON);
            disON = true;
        }
    }
}

void displayBattery()
{
    readBattery();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(voltage);
    display.setTextSize(1);
    display.print('V');
}

void displayTime()
{
    DateTime now = rtc.now();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 25);
    /*if (10 > now.hour())
  {
    display.print('0');
  }
  display.print(now.hour(), DEC);
  display.setCursor(40, 25);
  display.print(':');
  display.setCursor(52, 25);
  if (10 > now.minute())
  {
    display.print('0');
  }
  display.print(now.minute(), DEC);
  display.setTextSize(2);
  display.setCursor(83, 31);
  display.print(':');
  display.setCursor(91, 31);
  if (10 > now.second())
  {
    display.print('0');
  }
  display.print(now.second(), DEC);*/

    display.print(String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
}

void displayTemperature()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(90, 0);
    display.println(bme.readTemperature() - 7);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(120, 0);
    display.println('C');
}

void displayPressure()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 55);
    display.println(bme.readPressure());
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(60, 55);
    display.println("Pa");
}

void displayDate()
{
    DateTime now = rtc.now();
    char daysOfTheWeek[7][12] = {"Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi"};
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 56);
    display.print(now.day(), DEC);
    display.print(",");
    display.print(daysOfTheWeek[now.dayOfTheWeek()]);
    display.print(",");
    display.print(now.month(), DEC);
    display.print(",");
    display.print(now.year(), DEC);
}

void displayChronometer()
{
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(5, 25);
    if (10 > kronometre_saat)
    {
        display.print('0');
    }
    display.print(kronometre_saat, DEC);
    display.setCursor(35, 25);
    display.print(':');
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(47, 25);
    if (10 > kronometre_dakka)
    {
        display.print('0');
    }
    display.print(kronometre_dakka, DEC);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(78, 31);
    display.print(':');
    display.setCursor(86, 31);
    if (10 > kronometre_saniye)
    {
        display.print('0');
    }
    display.print(kronometre_saniye, DEC);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(110, 38);
    display.print(':');
    display.setCursor(115, 38);
    if (10 > kronometre_salise)
    {
        display.print('0');
    }
    display.print(kronometre_salise, DEC);
}

void displayMenuNum()
{
    if (menu > 0)
    {
        display.setTextSize(1);
        display.setCursor(35, 0);
        display.print("< Menu ");
        display.print(menu);
        display.print(" >");
    }
}

void displayMenuTitle()
{
    if (menu > 0)
    {
        display.setTextSize(1);
        display.setCursor(35, 56);

        switch (menu)
        {
        case 1:
            display.print("Kronometre");
            break;
        case 2:
            display.print("Calar Saat");
            break;
        case 4:
            display.print("Pusula");
            break;
        default:
            break;
        }
        /*if (menu == 1){
        display.print("Kronometre");
      }
      if (menu == 2){
        display.print("Calar Saat");
      }
      if (menu == 4){
        display.print("Pusula");
      }*/
    }
}

void displayAlarmClock()
{
    if (menu == 2)
    {
        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(10, 25);
        if (10 > calar_saat_saat)
        {
            display.print('0');
        }
        display.print(calar_saat_saat, DEC);
        display.setCursor(40, 25);
        display.print(':');
        display.setCursor(52, 25);
        if (10 > calar_saat_dakka)
        {
            display.print('0');
        }
        display.print(calar_saat_dakka, DEC);
        if (digitalRead(sw3) == LOW)
        {
            delay(200);
            if (calar_saat_secim == 0)
            {
                calar_saat_saat = calar_saat_saat + 1;
            }
            if (calar_saat_secim == 1)
            {
                calar_saat_dakka = calar_saat_dakka + 1;
            }
            if (calar_saat_saat >= 24)
            {
                calar_saat_saat = 0;
            }
            if (calar_saat_dakka >= 60)
            {
                calar_saat_dakka = 0;
            }
        }
        if (digitalRead(sw1) == LOW)
        {
            delay(200);
            calar_saat_secim = !calar_saat_secim;
        }
    }
}

void displayTimeSetting()
{
    DateTime now = rtc.now();
    ayar_saat = now.hour();
    ayar_dakka = now.minute();
    ayar_saniye = now.second();
    ayar_yil = now.year();
    ayar_ay = now.month();
    ayar_gun = now.day();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(10, 25);
    if (10 > ayar_saat)
    {
        display.print('0');
    }
    display.print(ayar_saat, DEC);
    display.setCursor(40, 25);
    display.print(':');
    display.setCursor(52, 25);
    if (10 > ayar_dakka)
    {
        display.print('0');
    }
    display.print(ayar_dakka, DEC);
    display.setTextSize(2);
    display.setCursor(83, 31);
    display.print(":");
    display.setCursor(91, 31);
    if (10 > ayar_saniye)
    {
        display.print('0');
    }
    display.print(ayar_saniye, DEC);
    /*  display.setCursor(91, 50);
  display.print(ayar_secim);*/

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 56);
    if (10 > ayar_gun)
    {
        display.print('0');
    }
    display.print(ayar_gun, DEC);
    display.print(",");
    if (10 > ayar_ay)
    {
        display.print('0');
    }
    display.print(ayar_ay, DEC);
    display.print(",");
    if (10 > ayar_yil)
    {
        display.print('0');
    }
    display.print(ayar_yil, DEC);
}

void displayMessage(int textSize, int cursorX, int cursorY, String message)
{
    display.setTextSize(textSize);
    display.setCursor(cursorX, cursorY);
    display.print(message);
}