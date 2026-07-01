#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H


#include <Arduino.h>
#include <TFT_eSPI.h>



class DisplayManager
{

private:

    TFT_eSPI tft;



public:

    void begin();


    void clear();


    void body(
        String text,
        int x,
        int y
    );


};



extern DisplayManager Display;


#endif