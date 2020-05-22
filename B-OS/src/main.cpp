/*WhatchX B-OS developed by Berk Akarcalioglu
Still in progress :P*/

#include <includes.h>
#include <defines.h>

extern RTC_DS3231 rtc;
extern MPU6050 mpu;
extern MAG3110 mag;
extern Adafruit_BMP280 bme;
extern int menu;

void setup()
{
  initialize();
  Serial.begin(9600);

  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);

   if (!bme.begin()) {
    Serial.println("BMP280 Bulunamadı");
    while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (!rtc.begin())
  {
    Serial.println("RTC Bulunamadı");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC'ye güç gitmiyor, Zamanı Ayarlayın");
    DateTime realTime(DateTime(F(__DATE__), F(__TIME__)));
    rtc.adjust(realTime);
  }

  displayInit();

  //vDiv = (R2 / (R1 + R2));

  menu = 0;
}

/*void BMP280_yazdir_serial()
{
  Serial.print("Sıicaklik = ");
  Serial.print(bme.readTemperature() - 7);
  Serial.println(' C');

  Serial.print("Basinc = ");
  Serial.print(bme.readPressure());
  Serial.println(" Pa");

  Serial.print("Yaklasik Yukseklik = ");
  Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(' m');

  Serial.println();
}*/

void buton_kontrol()
{
  if (digitalRead(sw2) == LOW)
  {
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
  }
  if (digitalRead(sw3) == LOW)
  {
    digitalWrite(6, HIGH);
    delay(50);
    digitalWrite(6, LOW);
  }
  if (digitalRead(sw1) == LOW)
  {
    digitalWrite(13, HIGH);
    digitalWrite(6, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(6, LOW);
  }
}

void saat_fonksiyon()
{
  if (menu == 0)
  {
    displayTime();
    displayTemperature();
    //  displayPressure();
    //  saat_yazdir_serial();
    //  BMP280_yazdir_serial();
    displayBattery();
    displayDate();
    buton_kontrol();
    delay(50);
  }
}

void menu_sec()
{
  if (digitalRead(sw2) == LOW)
  {
    menu = menu + 1;
    delay(500);
    if (menu > 4)
    {
      menu = 0;
    }
  }
}


void pusula()
{
  if (menu == 4)
  {
    mag.exitStandby();
    if (digitalRead(sw1) == LOW)
    {
      clearDisplay();
      displayMessage(1, 0, 30, "Kalibre Ediliyor...");
      displayDisplay();
      mag.enterCalMode();
      while (mag.isCalibrating())
      {
        mag.calibrate();
      }
    }

    if (mag.isCalibrated())
    {
      delay(100);
      char aci = (short)mag.readHeading();
      aci = map(aci, -180, 180, 0, 360);
      char yon = ' ';
      if (aci >= 315 || aci < 45)
        yon = 'K';
      if (aci >= 180 - 45 && aci < 180 + 45)
        yon = 'G';
      if (aci >= 45 && aci < 135)
        yon = 'D';
      if (aci >= 135 && aci < 315)
        yon = 'B';
      /*display.setTextSize(3);
      display.setCursor(30, 20);
      display.print(yon);
      display.print(' ');*/
      displayMessage(3, 30, 20, String(yon) + " ");
      delay(100);
      displayMessage(3, 30, 20, String(aci));
    }
    else
    {
      displayMessage(1, 0, 30, "Kalibre Edin");
    }
  }
}

void loop()
{

  if (!(USBSTA & (1 << VBUS)))
  {
    USBDevice.attach();
  }

  toggleDisplay();

  mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
  mag.initialize();
  mag.start();
  Vector rawAccel = mpu.readRawAccel();
  Activites act = mpu.readActivites();
  clearDisplay();
  saat_fonksiyon();
  chronometer();
  menu_sec();
  displayMenuNum();
  displayMenuTitle();
  clockSetting();
  alarmClock();
  pusula();
  displayDisplay();
}