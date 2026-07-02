#include "DisplayManager.h"
#include "TouchManager.h"
#include "FileManager.h"
#include "ReaderEngine.h"
#include "TextRenderer.h"

bool lastTouch = false;

void setup()
{
    Serial.begin(115200);
    Files.begin();
    Display.begin();
    Touch.begin();
    Reader.begin();
    Renderer.show(Reader.getPage(), Reader.currentPageIndex());
}

void loop()
{
    bool t = Touch.pressed();

    if (t && !lastTouch)
    {
        int tx = Touch.x();
        int ty = Touch.y();

        // ── Chạm vào nút "Page Select" ───────────────────────────────────────
        // Kiểm tra TRƯỚC khi kiểm tra next/prev để tránh nhầm lẫn
        // Vùng chạm nút menu mở rộng thêm padding 10px để dễ bấm
        if (tx >= MENU_X - 10 && tx <= MENU_X + MENU_W + 4 &&
            ty >= MENU_Y      && ty <= MENU_Y + MENU_H + 10)
        {
            int targetPage = Display.showPageSelector(
                Reader.currentPageIndex(), 9999
            );

            if (targetPage >= 0)
                Reader.goToPage(targetPage);

            // Reset lastTouch = true để tránh touch release sau khi đóng menu
            // trigger next/prev page
            lastTouch = true;
            Renderer.show(Reader.getPage(), Reader.currentPageIndex());
            return;   // thoát loop ngay, không xử lý next/prev
        }
        // ── Chạm nửa phải → trang tiếp ──────────────────────────────────────
        else if (tx > 160)
        {
            Reader.next();
            Renderer.show(Reader.getPage(), Reader.currentPageIndex());
        }
        // ── Chạm nửa trái → trang trước ─────────────────────────────────────
        else
        {
            Reader.previous();
            Renderer.show(Reader.getPage(), Reader.currentPageIndex());
        }
    }

    lastTouch = t;
    delay(50);
}
