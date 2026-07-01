#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <TFT_eSPI.h>


class DisplayManager
{

public:

    void begin();

    void clear();

    void title(String text);

    void body(String text);


};


extern DisplayManager Display;


#endif