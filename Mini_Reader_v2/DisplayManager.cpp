#include "DisplayManager.h"
#include "TouchManager.h"
#include <LittleFS.h>

DisplayManager Display;

static int currentFontSize = 0;

static void setFont(TFT_eSPI& tft, int size)
{
    if (currentFontSize == size) return;
    switch (size)
    {
        case 10: tft.loadFont("NotoSans-Regular10", LittleFS); break;
        case 18: tft.loadFont("NotoSans-Regular18", LittleFS); break;
        default: tft.loadFont("NotoSans-Regular14", LittleFS); break;
    }
    currentFontSize = size;
}


void DisplayManager::begin()
{
    pinMode(21, OUTPUT);
    digitalWrite(21, HIGH);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    currentFontSize = 0;
    setFont(tft, 14);
}


void DisplayManager::clear()
{
    tft.fillScreen(TFT_BLACK);
}


void DisplayManager::drawLine(const String& text, int x, int y)
{
    setFont(tft, 14);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(text, x, y);
}


void DisplayManager::drawTitle(const String& title)
{
    setFont(tft, 18);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    int tw = tft.textWidth(title);
    int x  = (TFT_WIDTH - tw) / 2;
    tft.drawString(title, x, MARGIN_Y);
    // Đường kẻ ngang dưới tiêu đề — thụt xuống thêm để không sát nút menu
    tft.drawLine(0, HEADER_H + 4, TFT_WIDTH, HEADER_H + 4, TFT_DARKGREY);
}


void DisplayManager::drawPageNumber(int page)
{
    setFont(tft, 10);

    int footerY = TFT_HEIGHT - FOOTER_H;   // y = 220

    // Xóa vùng footer
    tft.fillRect(0, footerY, TFT_WIDTH, FOOTER_H, TFT_BLACK);

    // Đường kẻ ngang trên footer — kéo sát dòng text cuối hơn
    // TEXT_BOTTOM = 218, dòng cuối kết thúc tại khoảng TEXT_BOTTOM - vài px
    // Vẽ đường kẻ tại footerY - 4 thay vì footerY - 1
    tft.drawLine(0, footerY - 4, TFT_WIDTH, footerY - 4, TFT_DARKGREY);

    // Vẽ text "Page X" — căn giữa ngang, đặt tại footerY + 4
    String label = "Page " + String(page + 1);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    int tw = tft.textWidth(label);
    int x  = (TFT_WIDTH - tw) / 2;
    tft.drawString(label, x, footerY - 10);
}


void DisplayManager::drawMenuButton()
{
    tft.fillRoundRect(MENU_X, MENU_Y, MENU_W, MENU_H, 3, TFT_NAVY);
    tft.drawRoundRect(MENU_X, MENU_Y, MENU_W, MENU_H, 3, TFT_CYAN);

    setFont(tft, 10);
    tft.setTextColor(TFT_CYAN, TFT_NAVY);
    String label = "Page select";
    int tw = tft.textWidth(label);
    int tx = MENU_X + (MENU_W - tw) / 2;
    int ty = MENU_Y + (MENU_H - 10) / 2;
    tft.drawString(label, tx, ty);
}


int DisplayManager::showPageSelector(int currentPage, int maxPage)
{
    tft.fillRoundRect(KB_X, KB_Y, KB_W, KB_H, 6, TFT_NAVY);
    tft.drawRoundRect(KB_X, KB_Y, KB_W, KB_H, 6, TFT_CYAN);

    setFont(tft, 14);
    tft.setTextColor(TFT_WHITE, TFT_NAVY);
    tft.drawString("Go to page:", KB_X + 8, KB_Y + 6);

    int dispX = KB_X + 8;
    int dispY = KB_Y + 26;
    tft.fillRect(dispX, dispY, KB_W - 16, 20, TFT_BLACK);
    tft.drawRect(dispX, dispY, KB_W - 16, 20, TFT_CYAN);

    const char* keys[] = {
        "1","2","3",
        "4","5","6",
        "7","8","9",
        "<","0","OK"
    };

    int startX = KB_X + (KB_W - (BTN_W * 3 + BTN_PAD * 2)) / 2;
    int startY = KB_Y + 52;

    auto drawBtn = [&](int col, int row, const char* label, bool highlight = false) {
        int bx = startX + col * (BTN_W + BTN_PAD);
        int by = startY + row * (BTN_H + BTN_PAD);
        tft.fillRoundRect(bx, by, BTN_W, BTN_H, 4,
                          highlight ? TFT_CYAN : TFT_DARKGREY);
        tft.setTextColor(highlight ? TFT_BLACK : TFT_WHITE,
                         highlight ? TFT_CYAN  : TFT_DARKGREY);
        int tw = tft.textWidth(String(label));
        tft.drawString(String(label), bx + (BTN_W - tw) / 2,
                       by + (BTN_H - 14) / 2);
    };

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 3; c++)
            drawBtn(c, r, keys[r * 3 + c]);

    String input  = "";
    bool   done   = false;
    int    result = -1;

    // Tunggu sampai layar tidak disentuh dulu sebelum masuk loop
    // để tránh touch mở menu bị tính luôn vào bàn phím
    delay(300);
    while (Touch.pressed()) delay(20);   // tunggu jari diangkat

    unsigned long lastT = 0;

    while (!done)
    {
        if (Touch.pressed())
        {
            unsigned long now = millis();
            if (now - lastT < 250) { delay(20); continue; }
            lastT = now;

            int tx = Touch.x();
            int ty = Touch.y();

            bool hitBtn = false;
            for (int r = 0; r < 4; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int bx = startX + c * (BTN_W + BTN_PAD);
                    int by = startY + r * (BTN_H + BTN_PAD);
                    if (tx >= bx && tx <= bx + BTN_W &&
                        ty >= by && ty <= by + BTN_H)
                    {
                        hitBtn = true;
                        const char* k = keys[r * 3 + c];
                        drawBtn(c, r, k, true);
                        delay(60);
                        drawBtn(c, r, k, false);

                        if (strcmp(k, "<") == 0)
                        {
                            if (input.length() > 0)
                                input = input.substring(0, input.length() - 1);
                        }
                        else if (strcmp(k, "OK") == 0)
                        {
                            if (input.length() > 0)
                            {
                                int pg = input.toInt() - 1;
                                if (pg < 0) pg = 0;
                                result = pg;
                            }
                            done = true;
                        }
                        else
                        {
                            if (input.length() < 4)
                                input += String(k);
                        }

                        tft.fillRect(dispX + 2, dispY + 2,
                                     KB_W - 20, 16, TFT_BLACK);
                        tft.setTextColor(TFT_WHITE, TFT_BLACK);
                        tft.drawString(
                            input.length() > 0 ? input : "_",
                            dispX + 4, dispY + 3
                        );

                        // Chờ jari diangkat sebelum lanjut
                        while (Touch.pressed()) delay(20);
                    }
                }
            }

            // Chạm ngoài overlay → cancel
            if (!hitBtn &&
                (tx < KB_X || tx > KB_X + KB_W ||
                 ty < KB_Y || ty > KB_Y + KB_H))
                done = true;
        }
        delay(30);
    }

    // Chờ ngón tay nhấc lên hoàn toàn trước khi return
    // để tránh touch đóng menu bị tính là Next Page
    delay(200);
    while (Touch.pressed()) delay(20);

    return result;
}


int DisplayManager::textWidth(const String& text)
{
    setFont(tft, 14);
    return tft.textWidth(text);
}


int DisplayManager::maxLinesNormal()
{
    // Trừ LINE_BUFFER để dòng cuối không bị cắt
    return (TEXT_BOTTOM - MARGIN_Y) / LINE_HEIGHT - LINE_BUFFER;
}


int DisplayManager::maxLinesFirstPage()
{
    return (TEXT_BOTTOM - (HEADER_H + 6)) / LINE_HEIGHT - LINE_BUFFER;
}
