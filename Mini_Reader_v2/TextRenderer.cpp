#include "TextRenderer.h"
#include "DisplayManager.h"
#include "Config.h"

TextRenderer Renderer;


// ─────────────────────────────────────────────────────────────────────────────
// wrapText — Word-wrap ngang
// ─────────────────────────────────────────────────────────────────────────────
int TextRenderer::wrapText(const String& text, String lines[], int maxLines)
{
    int lineCount = 0;
    int len       = text.length();
    int paraStart = 0;

    while (paraStart <= len && lineCount < maxLines)
    {
        int nlPos   = text.indexOf('\n', paraStart);
        int paraEnd = (nlPos < 0) ? len : nlPos;

        String para = text.substring(paraStart, paraEnd);
        paraStart   = paraEnd + 1;

        // Đoạn rỗng → dòng trống
        if (para.length() == 0)
        {
            if (lineCount < maxLines)
                lines[lineCount++] = "";
            continue;
        }

        // Word-wrap ngang
        String currentLine = "";
        int    wordStart   = 0;
        int    pLen        = para.length();

        while (wordStart <= pLen && lineCount < maxLines)
        {
            int spacePos = para.indexOf(' ', wordStart);
            int wordEnd  = (spacePos < 0) ? pLen : spacePos;

            String word = para.substring(wordStart, wordEnd);
            wordStart   = wordEnd + 1;

            String candidate = currentLine.length() > 0
                                ? (currentLine + " " + word)
                                : word;

            if (Display.textWidth(candidate) <= TEXT_W)
            {
                currentLine = candidate;
            }
            else
            {
                if (currentLine.length() > 0)
                {
                    lines[lineCount++] = currentLine;
                    if (lineCount >= maxLines) break;
                }

                // Từ quá dài → cắt ký tự
                if (Display.textWidth(word) > TEXT_W)
                {
                    String chunk = "";
                    for (int i = 0; i < (int)word.length(); i++)
                    {
                        String test = chunk + word[i];
                        if (Display.textWidth(test) > TEXT_W)
                        {
                            lines[lineCount++] = chunk;
                            if (lineCount >= maxLines) break;
                            chunk = String(word[i]);
                        }
                        else { chunk = test; }
                    }
                    currentLine = chunk;
                }
                else
                {
                    currentLine = word;
                }
            }

            if (wordStart > pLen && currentLine.length() > 0)
            {
                lines[lineCount++] = currentLine;
                currentLine = "";
            }
        }
    }

    return lineCount;
}


// ─────────────────────────────────────────────────────────────────────────────
// show — Hiển thị trang văn bản
// ─────────────────────────────────────────────────────────────────────────────
void TextRenderer::show(const String& text, int pageIndex)
{
    Display.clear();

    bool isFirst  = (pageIndex == 0);
    int  maxLines = isFirst ? Display.maxLinesFirstPage()
                            : Display.maxLinesNormal();
    int  textY    = isFirst ? (HEADER_H + 12)
                            : MARGIN_Y;

    // Tiêu đề trang đầu
    if (isFirst)
        Display.drawTitle(BOOK_TITLE);

    // Nút menu (mọi trang)
    Display.drawMenuButton();

    // Wrap & vẽ từng dòng
    String lines[20];   // MAX_LINES tối đa ~20 dòng trên 240px
    int    count = wrapText(text, lines, maxLines);

    for (int i = 0; i < count; i++)
    {
        int y = textY + i * LINE_HEIGHT;
        Display.drawLine(lines[i], MARGIN_X, y);
    }

    // Footer số trang
    Display.drawPageNumber(pageIndex);
}
