#include "ReaderEngine.h"
#include "FileManager.h"


ReaderEngine Reader;


String book;


int page = 0;



void ReaderEngine::begin()
{

    book = Files.readBook();

}



String ReaderEngine::getPage()
{

    int charsPerPage = 700;


    int start =
    page * charsPerPage;



    String result =
    book.substring(
        start,
        start + charsPerPage
    );



    return result;

}



void ReaderEngine::next()
{

    if(
        (page+1)*700 < book.length()
    )
    {
        page++;
    }

}



void ReaderEngine::previous()
{

    if(page>0)
    {
        page--;
    }

}