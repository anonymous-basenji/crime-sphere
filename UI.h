#pragma once
#include <SFML/Graphics.hpp>
#include "FileProcessing.h"

using namespace sf;
using namespace std;

class UI {
    RenderWindow& window;
    Texture heroTexture;
    Texture logo;

    /* ======= Common UI Elements ======= */
    void drawButton(float x, float y, float width, float height, const string& textString) const;

    /* ======= Helpers ======= */
    void centerText(Text& text, float yPosition) const;

    string fixTime(const string& time) const;
public:
    UI(RenderWindow& window);

    Font fontRegular;
    Font fontBold;

    string summarizeCrimeResults(const vector<pair<CrimeData, double>>& results) const;
    
    /* ======= Draw Common Elements ======= */
    void drawTopNav() const;
    void drawHeroBar(const string& textString) const;

    /* ======= Draw Home Elements ======= */
    void drawHero() const;
    void drawHeader(float boxMargin, float boxPosY) const;

    /* ======= Draw Search Elements ======= */
    void drawMainSection(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
    const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected, const string& algorithmText,
    const bool& algorithmSelected) const;
    void drawForm(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
        const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected, const string& algorithmText,
        const bool& algorithmSelected) const;
    void drawTextField(float x, float y, float width, float height,
        const string& placeholder, const string& textValue, const bool& selected) const;

    /* ======= Draw Results Elements ======= */
    void drawResults(const vector<pair<CrimeData, double>>& results, int currentPage, int itemsPerPage, int totalPages,
        double algorithmDuration) const;
    void drawResultsTable(const vector<pair<CrimeData, double>>& results, int currentPage, int itemsPerPage,
        double algorithmDuration) const;
    void drawPagination(int currentPage, int totalPages) const;
};
