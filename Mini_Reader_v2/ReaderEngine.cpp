#include "ReaderEngine.h"
#include "FileManager.h"
#include "DisplayManager.h"
#include "Config.h"

ReaderEngine Reader;

static String book;

#define MAX_PAGE_HISTORY 500
static int pageOffsets[MAX_PAGE_HISTORY];
static int pageCount   = 0;
static int currentPage = 0;


// ─────────────────────────────────────────────────────────────────────────────
// calcPageEnd — Tính byte offset kết thúc trang bắt đầu từ startByte
// Dùng word-wrap giống TextRenderer để đếm chính xác số dòng vừa màn hình.
// ─────────────────────────────────────────────────────────────────────────────
static int calcPageEnd(int startByte, bool isFirstPage)
{
    int maxLines  = isFirstPage ? Display.maxLinesFirstPage()
                                : Display.maxLinesNormal();
    int chunkSize = maxLines * 80;
    String chunk  = book.substring(startByte, startByte + chunkSize);

    int lineCount = 0;
    int len       = chunk.length();
    int paraStart = 0;
    int usedBytes = 0;

    while (paraStart <= len && lineCount < maxLines)
    {
        int nlPos   = chunk.indexOf('\n', paraStart);
        int paraEnd = (nlPos < 0) ? len : nlPos;

        String para     = chunk.substring(paraStart, paraEnd);
        int    consumed = paraEnd + 1;

        if (para.length() == 0)
        {
            lineCount++;
            usedBytes = consumed;
            paraStart = consumed;
            continue;
        }

        String currentLine = "";
        int    wordStart   = 0;
        int    pLen        = para.length();
        bool   overflow    = false;

        while (wordStart <= pLen)
        {
            int    spacePos = para.indexOf(' ', wordStart);
            int    wordEnd  = (spacePos < 0) ? pLen : spacePos;
            String word     = para.substring(wordStart, wordEnd);
            wordStart       = wordEnd + 1;

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
                    lineCount++;
                    if (lineCount >= maxLines)
                    {
                        int wordPosInPara = wordStart - (int)word.length() - 1;
                        if (wordPosInPara < 0) wordPosInPara = 0;
                        usedBytes = paraStart + wordPosInPara;
                        overflow  = true;
                        break;
                    }
                }

                if (Display.textWidth(word) > TEXT_W)
                {
                    String ch2 = "";
                    for (int i = 0; i < (int)word.length(); i++)
                    {
                        String test = ch2 + word[i];
                        if (Display.textWidth(test) > TEXT_W)
                        {
                            lineCount++;
                            if (lineCount >= maxLines)
                            {
                                int wpp = wordStart - (int)word.length() - 1 + i;
                                usedBytes = paraStart + wpp;
                                overflow  = true;
                                break;
                            }
                            ch2 = String(word[i]);
                        }
                        else { ch2 = test; }
                    }
                    if (overflow) break;
                    currentLine = ch2;
                }
                else
                {
                    currentLine = word;
                }
            }

            if (wordStart > pLen)
            {
                if (currentLine.length() > 0)
                {
                    lineCount++;
                    usedBytes = consumed;
                    if (lineCount >= maxLines) overflow = true;
                }
                break;
            }
        }

        if (overflow) break;
        paraStart = consumed;
    }

    if (usedBytes == 0) usedBytes = len;
    return startByte + usedBytes;
}


void ReaderEngine::begin()
{
    book = Files.readBook();
    pageOffsets[0] = 0;
    pageCount      = 1;
    currentPage    = 0;
}


String ReaderEngine::getPage()
{
    int start     = pageOffsets[currentPage];
    int chunkSize = 20 * 80;
    return book.substring(start, start + chunkSize);
}


int ReaderEngine::currentPageIndex()
{
    return currentPage;
}


void ReaderEngine::next()
{
    int start   = pageOffsets[currentPage];
    int nextEnd = calcPageEnd(start, currentPage == 0);

    if (nextEnd >= (int)book.length()) return;

    if (currentPage + 1 >= pageCount)
    {
        if (pageCount < MAX_PAGE_HISTORY)
        {
            pageOffsets[pageCount] = nextEnd;
            pageCount++;
        }
    }
    currentPage++;
}


void ReaderEngine::previous()
{
    if (currentPage > 0)
        currentPage--;
}


// goToPage: nếu trang đã biết offset → nhảy thẳng.
// Nếu chưa biết → tính tuần tự từ trang cuối đã biết đến trang đích.
void ReaderEngine::goToPage(int targetPage)
{
    if (targetPage < 0) targetPage = 0;

    // Tính các trang chưa biết
    while (pageCount <= targetPage)
    {
        int lastKnown = pageCount - 1;
        int start     = pageOffsets[lastKnown];
        int nextEnd   = calcPageEnd(start, lastKnown == 0);

        if (nextEnd >= (int)book.length()) break;

        if (pageCount < MAX_PAGE_HISTORY)
        {
            pageOffsets[pageCount] = nextEnd;
            pageCount++;
        }
        else break;
    }

    // Clamp về trang cuối nếu vượt
    if (targetPage >= pageCount)
        targetPage = pageCount - 1;

    currentPage = targetPage;
}
