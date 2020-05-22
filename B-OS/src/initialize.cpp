#include <initialize.h>
#include <includes.h>
#include <defines.h>

MAG3110 mag = MAG3110();
MPU6050 mpu;
RTC_DS3231 rtc;
Adafruit_BMP280 bme;
int menu;

void initialize()
{
    menu = 0;
}