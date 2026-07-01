#include "TextRenderer.h"
#include "DisplayManager.h"



TextRenderer Renderer;



void TextRenderer::show(String text)
{


    Display.clear();



    int y = 5;


    int lineHeight = 20;



    while(text.length())
    {


        int index =
        text.indexOf('\n');



        String line;



        if(index >= 0)
        {

            line =
            text.substring(
                0,
                index
            );


            text.remove(
                0,
                index + 1
            );


        }
        else
        {

            line = text;

            text = "";

        }



        Display.body(
            line,
            5,
            y
        );



        y += lineHeight;



        if(y > 220)
        {
            break;
        }


    }


}