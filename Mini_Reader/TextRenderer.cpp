#include "TextRenderer.h"
#include "DisplayManager.h"


TextRenderer Renderer;



void TextRenderer::show(String text)
{

    Display.clear();

    Display.body(text);

}