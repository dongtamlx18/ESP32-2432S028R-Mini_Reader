#include "FileManager.h"
#include <LittleFS.h>
#include "Config.h"



FileManager Files;



bool FileManager::begin()
{

    return LittleFS.begin(true);

}



String FileManager::readBook()
{

    File f = 
     LittleFS.open(
         BOOK_FILE,
         "r"
     );


    if(!f)
    {
        return "BOOK ERROR";
    }


    String data =
    f.readString();
    

    f.close();


    return data;

}