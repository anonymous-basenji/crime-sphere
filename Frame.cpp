#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"
#include "kdtree/KDTwoTree.h"
#include "heap/CrimeHeap.h"

using namespace std;
using namespace sf;

Frame::Frame(RenderWindow& window)
    : window(window), ui(window), currentPage(HOME), latitudeText(""),
    latitudeSelected(false), longitudeText(""), longitudeSelected(false), radiusText(""), radiusSelected(false),
    algorithmText(""), algorithmSelected(false), resultsPage(0), resultsPerPage(10) {

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
    ui.drawResults(results, resultsPage, resultsPerPage, getTotalPages(), getAlgorithmDuration());
}

void Frame::switchPage(AppPage page) {
    const AppPage previousPage = currentPage;
    currentPage = page;

    // Adjust window size based on the page
    if (page == RESULTS) {
        resultsPage = 0;
        window.setSize(Vector2u(window.getSize().x, 900));

        // Create a new view with the same width but taller height
        View view = window.getView();
        view.setSize(view.getSize().x, 900);
        view.setCenter(view.getCenter().x, 450);
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

// https://www.sfml-dev.org/tutorials/3.0/window/events/
bool Frame::handleEvent(Event event) {
    if (event.type == Event::MouseButtonPressed) {
        const Vector2i mousePos = Mouse::getPosition(window);

        // Deselect all text fields
        latitudeSelected = false;
        longitudeSelected = false;
        radiusSelected = false;
        algorithmSelected = false;

        cout << "Mouse clicked: " << mousePos.x << " " << mousePos.y << endl;

        // Handle events based on current page
        switch (currentPage) {
            case HOME:
                // Check if the START EXPLORING button was clicked
                if (mousePos.x >= 80 && mousePos.x <= 280 &&
                    mousePos.y >= 120 && mousePos.y <= 450) {

                    switchPage(SEARCH);
                    return true;
                }

                // Add events to Video and Documentation
                if (mousePos.x >= 1410 && mousePos.x <= 1456 &&
                     mousePos.y >= 38 && mousePos.y <= 50) {
                    // Open YouTube video
                    string youtubeUrl = "https://youtu.be/1dyumKsxfC0";
                    openURL(youtubeUrl);
                    return true;
                }
                if (mousePos.x >= 1503 && mousePos.x <= 1626 &&
                    mousePos.y >= 38 && mousePos.y <= 50) {
                    // Open Documentation
                    string readme = "https://github.com/anonymous-basenji/crime-sphere?tab=readme-ov-file#crime-sphere";
                    openURL(readme);
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

                // Add events to Video and Documentation
                if (mousePos.x >= 1410 && mousePos.x <= 1456 &&
                     mousePos.y >= 38 && mousePos.y <= 50) {
                    // Open YouTube video
                    string youtubeUrl = "https://youtu.be/1dyumKsxfC0";
                    openURL(youtubeUrl);
                    return true;
                }
                if (mousePos.x >= 1503 && mousePos.x <= 1626 &&
                    mousePos.y >= 38 && mousePos.y <= 50) {
                    // Open Documentation
                    string readme = "https://github.com/anonymous-basenji/crime-sphere?tab=readme-ov-file#crime-sphere";
                    openURL(readme);
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

                // Add pagination button handling
                const float windowWidth = static_cast<float>(window.getSize().x),
                paginationY = 800.f;

                // Previous button
                if (resultsPage > 0 &&
                    mousePos.x >= windowWidth / 2 - 250.f && mousePos.x <= windowWidth / 2 - 130.f &&
                    mousePos.y >= paginationY && mousePos.y <= paginationY + 40.f) {

                    resultsPage--;
                    return true;
                    }

                // Next button
                if (resultsPage < getTotalPages() - 1 &&
                    mousePos.x >= windowWidth / 2 + 80.f && mousePos.x <= windowWidth / 2 + 180.f &&
                    mousePos.y >= paginationY && mousePos.y <= paginationY + 40.f) {

                    resultsPage++;

                    drawFrame();

                    return true;
                }


                // Add events to Video and Documentation
                if (mousePos.x >= 1410 && mousePos.x <= 1456 &&
                     mousePos.y >= 38 && mousePos.y <= 50) {
                    // Open YouTube video
                    string youtubeUrl = "https://youtu.be/1dyumKsxfC0";
                    openURL(youtubeUrl);
                    return true;
                }
                if (mousePos.x >= 1503 && mousePos.x <= 1626 &&
                    mousePos.y >= 38 && mousePos.y <= 50) {
                    // Open Documentation
                    string readme = "https://github.com/anonymous-basenji/crime-sphere?tab=readme-ov-file#crime-sphere";
                    openURL(readme);
                    return true;
                }
            break;
        }
    }
    else if (event.type == Event::TextEntered) {
        if (currentPage == SEARCH) {
            // Only handle printable ASCII characters and backspace
            // https://www.sfml-dev.org/tutorials/3.0/window/events/#the-focuslost-and-focusgained-events
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

// Save user input from form
void Frame::saveUserInput() {

    try {
        double latitude;
        double longitude;
        double radius = 0;
        string algorithm;

        // Convert string input to appropriate types
        if (!latitudeText.empty())
            latitude = stod(latitudeText);
        else
            latitude = 0.0;

        if (!longitudeText.empty())
            longitude = stod(longitudeText);
        else
            longitude = 0.0;

        if (!radiusText.empty()) {
            radius = stoi(radiusText);
            // Ensure radius is within valid range
            if (radius < 1) radius = 1;
            if (radius > 10) radius = 10;
        }

        if (!algorithmText.empty()) {
            // Call what algorithm to use
            if (algorithmText == "1")
                algorithm = "1";
            else if (algorithmText == "2")
                algorithm = "2";
            else
                algorithm = "0";
        }

        // Add the search parameters for filtering
        FileProcessing::addSearchParameters(latitude, longitude, radius, algorithm);

        // Time how fast algorithms run
        const clock_t before = clock();

        if (algorithm == "1") {
            KDTwoTree kdTree(FileProcessing::getData());
            results = kdTree.findInRadius(latitude, longitude, radius);
        }
        else if (algorithm == "2") {
            CrimeHeap heap(radius, latitude, longitude);
            results = heap.getCrimesInRadius();
        }
        else {
            results = {};
        }

        clock_t duration = clock() - before;
        algorithmDuration = ((float)duration)/CLOCKS_PER_SEC;

    } catch (const exception& e) {
        cerr << "Error saving user input: " << e.what() << endl;
    }
}

/* ========= Table Paging ========= */
void Frame::nextPage() {
    if ((resultsPage + 1) * resultsPerPage < results.size())
        resultsPage++;
}

void Frame::prevPage() {
    if (resultsPage > 0)
        resultsPage--;
}

int Frame::getTotalPages() const {
    if (results.empty()) return 0;
    return (results.size() + resultsPerPage - 1) / resultsPerPage;
}

double Frame::getAlgorithmDuration() const {
    return algorithmDuration;
}

// https://en.sfml-dev.org/forums/index.php?topic=28740.0
// https://stackoverflow.com/questions/17347950/how-do-i-open-a-url-from-c
void Frame::openURL(const string& url) {
    #ifdef _WIN32
        // Windows
        string command = "start " + url;
        system(command.c_str());
    #elif __APPLE__
        // macOS
        string command = "open " + url;
        system(command.c_str());
    #else
        // Linux and other Unix-like systems
        string command = "xdg-open " + url;
        system(command.c_str());
    #endif
}