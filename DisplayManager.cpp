#include "DisplayManager.h"
#include <LittleFS.h>

DisplayManager Display;



void DisplayManager::begin()
{
    pinMode(21, OUTPUT);

    digitalWrite(21, HIGH);
    tft.init();


    tft.setRotation(1);


    tft.fillScreen(
        TFT_BLACK
    );

    tft.loadFont("NotoSans-Regular20", LittleFS);
}



void DisplayManager::clear()
{

    tft.fillScreen(
        TFT_BLACK
    );

}



void DisplayManager::body(
String text,
int x,
int y
)
{

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );


    tft.setTextSize(1);


    tft.drawString(
        text,
        x,
        y
    );


}