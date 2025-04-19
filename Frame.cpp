#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"

using namespace std;
using namespace sf;

Frame::Frame(RenderWindow& window)
    : window(window), ui(window), currentPage(RESULTS), latitudeText(""),
    latitudeSelected(false), longitudeText(""), longitudeSelected(false), radiusText(""), radiusSelected(false) {
    // Initialize with home screen size
    window.setSize(Vector2u(1680, 600));
}

void Frame::drawFrame() const {

    // White background
    window.clear(Color(250, 250, 250));

    // Draw the top nav on all screens
    ui.drawTopNav();

    // Draw the current screen
    switch (currentPage) {
    case HOME:
        drawHomeScreen();
        break;
    case SEARCH:
        drawSearchScreen();
        break;
    case RESULTS:
        drawResultsScreen();
        break;
    }

    window.display();
}

void Frame::drawHomeScreen() const {
    ui.drawHero();
}

void Frame::drawSearchScreen() const {
    ui.drawHeroBar("SEARCH");
    ui.drawMainSection(latitudeText, latitudeSelected, longitudeText, longitudeSelected, radiusText, radiusSelected,
        algorithmText, algorithmSelected);
}

void Frame::drawResultsScreen() const {
    ui.drawHeroBar("RESULTS");
    ui.drawResults(results);
}

void Frame::switchPage(AppPage page) {
    currentPage = page;
}

bool Frame::handleEvent(Event event) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);

        // Print mouse position for debugging
        cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << endl;

        // Handle events based on current page
        switch (currentPage) {
        case HOME:
            // Check if the START EXPLORING button was clicked
            if (mousePos.x >= 80 && mousePos.x <= 280 &&
                mousePos.y >= 280 && mousePos.y <= 416) {

                switchPage(SEARCH);
                return true;
            }
            break;

        case SEARCH:
            // Check if back button was clicked
            if (mousePos.x >= 50 && mousePos.x <= 275 &&
                mousePos.y >= 56 && mousePos.y <= 282) {

                switchPage(HOME);
                return true;
            }
            // Check if search button was clicked
            if (mousePos.x >= 50 && mousePos.x <= 250 &&
                mousePos.y >= 460 && mousePos.y <= 660) {

                switchPage(RESULTS);
                return true;
            }
            break;

        case RESULTS:
            // Check if back button was clicked
            if (mousePos.x >= 50 && mousePos.x <= 275 &&
                mousePos.y >= 56 && mousePos.y <= 282) {

                switchPage(SEARCH);
                return true;
            }
            break;
        }
    }

    return false;
}