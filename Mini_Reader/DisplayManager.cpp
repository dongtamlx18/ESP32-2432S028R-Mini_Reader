#include "DisplayManager.h"


TFT_eSPI tft = TFT_eSPI();


DisplayManager Display;


void DisplayManager::begin()
{
     pinMode(21, OUTPUT);

    digitalWrite(21, HIGH);
    
    tft.init();

    tft.setRotation(1);

    tft.fillScreen(TFT_BLACK);

}



void DisplayManager::clear()
{

    tft.fillScreen(TFT_BLACK);

}



void DisplayManager::title(String text)
{

    tft.setTextColor(TFT_YELLOW);

    tft.setTextSize(2);

    tft.drawString(text,10,10);

}



void DisplayManager::body(String text)
{

    tft.setTextColor(TFT_WHITE);

    tft.setTextSize(1);

    tft.drawString(text,10,50);

}