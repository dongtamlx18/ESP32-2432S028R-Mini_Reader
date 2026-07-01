#ifndef READER_ENGINE_H
#define READER_ENGINE_H

#include <Arduino.h>


class ReaderEngine
{

public:

    void begin();

    String getPage();

    void next();

    void previous();


};


extern ReaderEngine Reader;


#endif