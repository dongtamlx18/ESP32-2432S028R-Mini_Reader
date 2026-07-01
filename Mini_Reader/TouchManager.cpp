#include "TouchManager.h"
#include "Config.h"


SPIClass touchSPI = SPIClass(VSPI);


XPT2046_Touchscreen ts(
    TOUCH_CS
);


TouchManager Touch;


int tx;
int ty;



void TouchManager::begin()
{

    touchSPI.begin(
        25,
        39,
        32,
        33
    );


    ts.begin(
        touchSPI
    );


    ts.setRotation(1);

}



bool TouchManager::pressed()
{

    if(ts.touched())
    {

        TS_Point p = ts.getPoint();

        tx = map(
            p.x,
            200,
            3800,
            0,
            320
        );


        ty = map(
            p.y,
            200,
            3800,
            0,
            240
        );


        return true;

    }


    return false;

}



int TouchManager::x()
{
    return tx;
}



int TouchManager::y()
{
    return ty;
}