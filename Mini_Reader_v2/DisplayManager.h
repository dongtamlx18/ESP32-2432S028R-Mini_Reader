#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Config.h"

class DisplayManager
{
private:
    TFT_eSPI tft;

public:
    void begin();
    void clear();

    // Vẽ text body (font 14)
    void drawLine(const String& text, int x, int y);

    // Vẽ tiêu đề (font 18, căn giữa)
    void drawTitle(const String& title);

    // Vẽ footer: "Page X"
    void drawPageNumber(int page);

    // Vẽ nút menu "Page Select"
    void drawMenuButton();

    // Vẽ hộp nhập số trang (bàn phím số đơn giản)
    // Trả về số trang người dùng chọn (-1 nếu cancel)
    int  showPageSelector(int currentPage, int maxPage);

    // Đo pixel width (font hiện tại)
    int  textWidth(const String& text);

    // Trả về số dòng tối đa cho trang body thường và trang đầu (có tiêu đề)
    int  maxLinesNormal();
    int  maxLinesFirstPage();
};

extern DisplayManager Display;

#endif
