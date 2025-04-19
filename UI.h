#pragma once
#include <SFML/Graphics.hpp>
#include "FileProcessing.h"

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
    void drawHeroBar(const string& textString) const;

    /* ======= Draw Home Elements ======= */
    void drawHero() const;
    void drawHeader(float boxMargin, float boxPosY) const;

    /* ======= Draw Search Elements ======= */
    void drawMenu(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
        const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected,
        const string& algorithmText, const bool& algorithmSelected) const;
    void drawMainSection(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
    const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected, const string& algorithmText,
    const bool& algorithmSelected) const;
    void drawTextField(float x, float y, float width, float height,
        const string& placeholder, const string& textValue, const bool& selected) const;

    /* ======= Draw Results Elements ======= */
    void drawResults(const vector<CrimeData>& results) const;
    void drawResultsTable(const vector<CrimeData>& results) const;
};
