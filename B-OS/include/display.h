#include <Arduino.h>

#ifndef DISPLAY_H
#define DISPLAY_H

#pragma once

extern bool disON;

extern int menu;

void displayInit();

void toggleDisplay();

void clearDisplay();

void displayDisplay();

void displayBattery();

void displayTime();

void displayTemperature();

void displayPressure();

void displayDate();

void displayChronometer();

void displayMenuNum();

void displayMenuTitle();

void displayAlarmClock();

void displayTimeSetting();

void displayMessage(int textSize, int cursorX, int cursorY, String message);

#endif