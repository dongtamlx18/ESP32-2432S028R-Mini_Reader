#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H


#include <Arduino.h>


class TextRenderer
{

public:

    void show(String text);


};


extern TextRenderer Renderer;


#endif