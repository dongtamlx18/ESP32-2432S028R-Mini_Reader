#include "ReaderEngine.h"
#include "FileManager.h"


ReaderEngine Reader;


String book;


int page = 0;



void ReaderEngine::begin()
{

    book =
    Files.readBook();

}



String ReaderEngine::getPage()
{

    int start =
    page * 400;


    return
    book.substring(
        start,
        start + 400
    );

}



void ReaderEngine::next()
{

    page++;

}



void ReaderEngine::previous()
{

    if(page>0)
        page--;

}