#ifndef CONFIG_H
#define CONFIG_H

// ── TFT (landscape 320x240) ───────────────────────────────────────────────────
#define TFT_WIDTH   320
#define TFT_HEIGHT  240

// ── Touch ─────────────────────────────────────────────────────────────────────
#define TOUCH_CS 33

// ── File sách ─────────────────────────────────────────────────────────────────
#define BOOK_FILE "/truyen_kieu.txt"
#define BOOK_TITLE "Truyện Kiều"

// ── Layout văn bản ────────────────────────────────────────────────────────────
#define MARGIN_X       5    // lề trái/phải (px)
#define MARGIN_Y       12    // lề trên (px)
#define LINE_HEIGHT   18    // khoảng cách dòng body (px)
#define FOOTER_H      20    // chiều cao vùng footer ở đáy màn hình

// ── Header (tiêu đề — chỉ trang 0) ───────────────────────────────────────────
#define HEADER_H      24    // chiều cao vùng tiêu đề (px)

// ── Menu "Page Select" (góc trên phải) ───────────────────────────────────────
#define MENU_W        70
#define MENU_H        16
#define MENU_X        (TFT_WIDTH - MENU_W - 2)
#define MENU_Y        2

// ── Bàn phím số overlay (Page Selector) ──────────────────────────────────────
#define KB_X      60
#define KB_Y      40
#define KB_W     200
#define KB_H     170
#define BTN_W     44
#define BTN_H     26
#define BTN_PAD    6

// ── Vùng văn bản ─────────────────────────────────────────────────────────────
#define TEXT_W        (TFT_WIDTH - MARGIN_X * 2)
#define TEXT_BOTTOM   (TFT_HEIGHT - FOOTER_H - 2)

// ── Trừ thêm 1 dòng buffer để tránh dòng cuối bị cắt ────────────────────────
// maxLines = (TEXT_BOTTOM - textStart) / LINE_HEIGHT - LINE_BUFFER
#define LINE_BUFFER   1

#endif
