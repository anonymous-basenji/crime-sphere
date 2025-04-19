#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"

using namespace sf;

enum AppPage {
    HOME,
    SEARCH,
    RESULTS
};

class Frame {
    RenderWindow& window;
    UI ui;
    AppPage currentPage;

    string latitudeText;
    string longitudeText;
    string radiusText;
    string algorithmText;
    bool latitudeSelected;
    bool longitudeSelected;
    bool radiusSelected;
    bool algorithmSelected;
    double algorithmDuration;

    vector<pair<CrimeData, double>> results;
    int resultsPage;
    int resultsPerPage;

    /* ======= Draw Screens ======= */
    void drawHomeScreen() const;
    void drawSearchScreen() const;
    void drawResultsScreen() const;
public:
    /* ======= Draw Window ======= */
    Frame(RenderWindow& window);
    void drawFrame() const;

    /* ======= Event Listeners ======= */
    bool handleEvent(Event event);
    void switchPage(AppPage page);

    /* ======= Data Management ======= */
    void saveUserInput();

    /* ========= Table Paging ========= */
    void nextPage();
    void prevPage();
    int getTotalPages() const;

    double getAlgorithmDuration() const;
};
