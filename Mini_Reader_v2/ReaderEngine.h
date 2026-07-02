#ifndef READER_ENGINE_H
#define READER_ENGINE_H

#include <Arduino.h>

class ReaderEngine
{
public:
    void   begin();
    String getPage();
    void   next();
    void   previous();
    void   goToPage(int pageIndex);   // nhảy đến trang bất kỳ
    int    currentPageIndex();
};

extern ReaderEngine Reader;

#endif
