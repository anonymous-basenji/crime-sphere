#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Frame {
    RenderWindow& window;
    Font fontRegular, fontBold;

    /* ======= Draw Prompt ======= */
    void drawHeader();
    void drawMenu();

    /* ======= Helpers ======= */
    void centerText(Text& text, float yPosition) const;
public:
    Frame(RenderWindow& window);
    void drawFrame();
};
