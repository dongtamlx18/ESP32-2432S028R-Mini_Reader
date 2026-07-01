#include "DisplayManager.h"
#include "TouchManager.h"
#include "FileManager.h"
#include "ReaderEngine.h"
#include "TextRenderer.h"



bool lastTouch=false;



void setup()
{

    Serial.begin(115200);


    Files.begin();


    Display.begin();


    Touch.begin();


    //Files.begin();


    Reader.begin();


    Renderer.show(
        Reader.getPage()
    );

}



void loop()
{


    bool t =
    Touch.pressed();



    if(t && !lastTouch)
    {


        if(
            Touch.x() > 160
        )
        {

            Reader.next();

        }
        else
        {

            Reader.previous();

        }



        Renderer.show(
            Reader.getPage()
        );


    }


    lastTouch=t;


    delay(50);

}