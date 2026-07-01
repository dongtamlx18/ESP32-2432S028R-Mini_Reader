#ifndef TOUCH_MANAGER_H
#define TOUCH_MANAGER_H

#include <Arduino.h>
#include <XPT2046_Touchscreen.h>


class TouchManager
{

public:

    void begin();

    bool pressed();

    int x();

    int y();


};


extern TouchManager Touch;


#endif