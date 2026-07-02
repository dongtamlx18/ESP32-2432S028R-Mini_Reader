#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <Arduino.h>

class TextRenderer
{
public:
    // Hiển thị trang — isFirstPage=true → vẽ thêm tiêu đề
    void show(const String& text, int pageIndex);

    // Word-wrap: tách text → mảng lines[], trả về số dòng thực
    int  wrapText(const String& text, String lines[], int maxLines);
};

extern TextRenderer Renderer;

#endif
