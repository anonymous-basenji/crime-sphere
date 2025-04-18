#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class UI {
    RenderWindow& window;
    Texture heroTexture;

    /* ======= Common UI Elements ======= */
    void drawButton(float x, float y, float width, float height, const string& textString) const;

    /* ======= Helpers ======= */
    void centerText(Text& text, float yPosition) const;
public:
    UI(RenderWindow& window);

    Font fontRegular;
    Font fontBold;

    /* ======= Draw Common Elements ======= */
    void drawTopNav() const;

    /* ======= Draw Home Elements ======= */
    void drawHero() const;
    void drawHeader(float boxMargin, float boxPosY) const;

    /* ======= Draw Search Elements ======= */
    void drawMainSection() const;
    void drawMenu() const;
};
