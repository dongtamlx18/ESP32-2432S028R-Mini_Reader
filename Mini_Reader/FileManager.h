#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <Arduino.h>


class FileManager
{

public:

    bool begin();

    String readBook();


};


extern FileManager Files;


#endif