#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"

using namespace std;
using namespace sf;

Frame::Frame(RenderWindow& window)
    : window(window), ui(window), currentPage(RESULTS), latitudeText(""),
    latitudeSelected(false), longitudeText(""), longitudeSelected(false), radiusText(""), radiusSelected(false),
    algorithmText(""), algorithmSelected(false) {

    // Initialize with home screen size
    window.setSize(Vector2u(1680, 600));

    FileProcessing::ReadFile();
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
    const AppPage previousPage = currentPage;
    currentPage = page;

    // Adjust window size based on the page
    if (page == RESULTS) {
        window.setSize(Vector2u(window.getSize().x, 800));

        // Create a new view with the same width but taller height
        View view = window.getView();
        view.setSize(view.getSize().x, 800);
        view.setCenter(view.getCenter().x, 400);
        window.setView(view);

        // Adjust window position to keep it centered
        const Vector2i windowPos = window.getPosition();
        window.setPosition(windowPos - Vector2i(0, 100));
    } else if (previousPage == RESULTS) {

        // Coming from results page to another page
        window.setSize(Vector2u(window.getSize().x, 600));

        // Reset the view to the standard size
        View view = window.getView();
        view.setSize(view.getSize().x, 600);
        view.setCenter(view.getCenter().x, 300);
        window.setView(view);

        // Adjust window position to keep it centered
        const Vector2i windowPos = window.getPosition();
        window.setPosition(windowPos + Vector2i(0, 100));
    }
}

bool Frame::handleEvent(Event event) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);

        // Print mouse position for debugging
        cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << endl;

        // Deselect all text fields
        latitudeSelected = false;
        longitudeSelected = false;
        radiusSelected = false;
        algorithmSelected = false;

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
            // Check latitude text field
            if (mousePos.x >= 50 && mousePos.x <= 350 &&
                mousePos.y >= 380 && mousePos.y <= 420) {
                latitudeSelected = true;
                return true;
            }

            // Check longitude text field
            if (mousePos.x >= 420 && mousePos.x <= 720 &&
                mousePos.y >= 380 && mousePos.y <= 420) {
                longitudeSelected = true;
                return true;
            }

            // Check radius text field
            if (mousePos.x >= 780 && mousePos.x <= 1080 &&
                mousePos.y >= 380 && mousePos.y <= 420) {
                radiusSelected = true;
                return true;
            }

            // Check algorithm text field
            if (mousePos.x >= 1140 && mousePos.x <= 1440 &&
                mousePos.y >= 380 && mousePos.y <= 420) {
                algorithmSelected = true;
                return true;
            }

            // Check if search button was clicked
            if (mousePos.x >= 50 && mousePos.x <= 250 &&
                mousePos.y >= 460 && mousePos.y <= 660) {

                saveUserInput();

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
    else if (event.type == Event::TextEntered) {
        if (currentPage == SEARCH) {
            // Only handle printable ASCII characters and backspace
            if ((event.text.unicode >= 32 && event.text.unicode < 127) ||
                event.text.unicode == 8) {

                string* selectedText = nullptr;

                // Determine which text field is selected
                if (latitudeSelected)
                    selectedText = &latitudeText;
                else if (longitudeSelected)
                    selectedText = &longitudeText;
                else if (radiusSelected)
                    selectedText = &radiusText;
                else if (algorithmSelected)
                    selectedText = &algorithmText;

                // If a text field is selected, update its text
                if (selectedText != nullptr) {
                    // Backspace
                    if (event.text.unicode == 8) {
                        if (!selectedText->empty())
                            selectedText->pop_back();
                    }
                    else
                        *selectedText += static_cast<char>(event.text.unicode);
                    return true;
                }
            }
        }
    }
    else if (event.type == Event::KeyPressed) {
        // Handle TAB key to switch between text fields
        if (event.key.code == Keyboard::Tab && currentPage == SEARCH) {
            if (latitudeSelected) {
                latitudeSelected = false;
                longitudeSelected = true;
            }
            else if (longitudeSelected) {
                longitudeSelected = false;
                radiusSelected = true;
            }
            else if (radiusSelected) {
                radiusSelected = false;
                algorithmSelected = true;
            }
            else if (algorithmSelected) {
                algorithmSelected = false;
                latitudeSelected = true;
            }
            else {
                // If no field is selected, select the first one
                latitudeSelected = true;
            }

            return true;
        }
    }

    return false;
}
// Add this method to your Frame class implementation (Frame.cpp)

void Frame::saveUserInput() {
    CrimeData userInput;

    try {
        // Convert string input to appropriate types
        if (!latitudeText.empty())
            userInput.latitude = stod(latitudeText);
        else
            userInput.latitude = 0.0;

        if (!longitudeText.empty())
            userInput.longitude = stod(longitudeText);
        else
            userInput.longitude = 0.0;

        if (!radiusText.empty()) {
            userInput.radius = stoi(radiusText);
            // Ensure radius is within valid range
            if (userInput.radius < 1) userInput.radius = 1;
            if (userInput.radius > 10) userInput.radius = 10;
        }

        if (!algorithmText.empty()) {
            // Add what algorithm to call here depending on the option selected
            if (algorithmText == "kd-tree") {
                // load kd-tree
                userInput.algorithm = "kd-tree";
            }
            else if (algorithmText == "heap") {
                // load heap
                userInput.algorithm = "heap";
            }
        }

        // Add the new entry to the data vector
        FileProcessing::addCrimeData(userInput);

        // Also add the search parameters for filtering
        FileProcessing::addSearchParameters(userInput.latitude, userInput.longitude, userInput.radius, userInput.algorithm);

        // Print confirmation message
        cout << "User input saved to data vector." << endl;
        cout << "Latitude: " << userInput.latitude << ", Longitude: " << userInput.longitude
             << ", Radius: " << userInput.radius << ", Algorithm: " << userInput.algorithm << endl;

        // Update the results to include the user's entry
        results = FileProcessing::getData();

    } catch (const exception& e) {
        cerr << "Error saving user input: " << e.what() << endl;
    }
}