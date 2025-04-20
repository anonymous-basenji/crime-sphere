#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "FileProcessing.h"
#include "UI.h"

using namespace std;
using namespace sf;

UI::UI(RenderWindow& window) : window(window) {
    // Load Fonts
    if (!fontRegular.loadFromFile("font/Inter-Regular.ttf"))
        cerr << "Failed to load font!" << endl;
    if (!fontBold.loadFromFile("font/Inter-Bold.ttf"))
        cerr << "Failed to load font!" << endl;

    // Load images
    if (!heroTexture.loadFromFile("images/hero-cropped.jpg"))
        cerr << "Failed to load hero image!" << endl;
    if (!logo.loadFromFile("images/logo.png"))
        cerr << "Failed to load log!" << endl;
}

void UI::drawTopNav() const {

    // Create navigation bar
    RectangleShape navBar(Vector2f(window.getSize().x, 90.f));
    navBar.setFillColor(Color(250, 250, 250));
    window.draw(navBar);

    // Create a sprite using the logo texture
    Sprite logoSprite;
    logoSprite.setTexture(logo);
    const float originalWidth = logoSprite.getLocalBounds().width;
    const float targetWidth = 120.f;
    const float scaleFactor = targetWidth / originalWidth;
    logoSprite.setScale(scaleFactor, scaleFactor);

    // Position below the nav bar
    logoSprite.setPosition(50.f, 5.f);

    window.draw(logoSprite);

    // Create the first link
    Text link1;
    link1.setFont(fontRegular);
    link1.setString("Video");
    link1.setCharacterSize(18);
    link1.setFillColor(Color(44, 62, 80));
    link1.setPosition(window.getSize().x - 270.f, 35.f); // Right-aligned
    window.draw(link1);

    // Create the second link
    Text link2;
    link2.setFont(fontRegular);
    link2.setString("Documentation");
    link2.setCharacterSize(18);
    link2.setFillColor(Color(44, 62, 80));
    link2.setPosition(window.getSize().x - 180.f, 35.f); // Right-aligned
    window.draw(link2);
}

void UI::drawHeroBar(const string& textString) const {
    float windowWidth = static_cast<float>(window.getSize().x);
    RectangleShape titleBar(Vector2f(windowWidth, 150));
    titleBar.setFillColor(Color(52, 152, 219));
    titleBar.setPosition(0, 90);

    window.draw(titleBar);

    // Add subtitle text
    Text subtitle;
    subtitle.setFont(fontBold);
    subtitle.setString(textString);
    subtitle.setCharacterSize(30);
    subtitle.setFillColor(Color::White);
    subtitle.setPosition(50, 145);
    window.draw(subtitle);
}

void UI::drawHero() const {
    // Create a sprite using the hero texture
    Sprite heroSprite;
    heroSprite.setTexture(heroTexture);

    // Calculate scaling to make the image fit properly
    float windowWidth = static_cast<float>(window.getSize().x);
    float imageWidth = static_cast<float>(heroTexture.getSize().x);
    float scale = windowWidth / imageWidth;

    heroSprite.setScale(scale, scale);

    // Position below the nav bar
    heroSprite.setPosition(0, 90);

    // Add a semi-transparent overlay for better text readability
    RectangleShape overlay(Vector2f(windowWidth, heroTexture.getSize().y * scale));
    overlay.setPosition(0, 90);
    // Precisely 30% opacity
    overlay.setFillColor(Color(0, 0, 0, static_cast<Uint8>(0.3f * 255)));

    // Draw the hero image and overlay
    window.draw(heroSprite);
    window.draw(overlay);

    // Create a white box for text
    float boxWidth = windowWidth / 2.5f;
    float boxHeight = 230;
    float boxMargin = 50;

    // Calculate the hero image's scaled height
    float heroHeight = heroTexture.getSize().y * scale;
    float boxPosY = 90 + (heroHeight - boxHeight) / 2;

    RectangleShape textBox(Vector2f(boxWidth, boxHeight));
    // White with slight transparency
    textBox.setFillColor(Color(255, 255, 255, 230));
    // Positioned within the hero area
    textBox.setPosition(boxMargin, boxPosY);

    window.draw(textBox);

    // Draw the text on top of the white box
    drawHeader(boxMargin, boxPosY);
}

void UI::drawHeader(const float boxMargin, const float boxPosY) const {
    const float textPadding = 30;

    Text title;
    title.setFont(fontBold);
    title.setString("Welcome to CrimeSphere!");
    title.setCharacterSize(32);
    title.setFillColor(Color(44, 62, 80));
    title.setPosition(boxMargin + textPadding, boxPosY + textPadding);
    window.draw(title);

    Text subtitle;
    subtitle.setFont(fontRegular);
    subtitle.setString("Step into the future of crime data visualization and exploration");
    subtitle.setCharacterSize(20);
    subtitle.setFillColor(Color(44, 62, 80));
    subtitle.setPosition(boxMargin + textPadding, boxPosY + textPadding + 60);
    window.draw(subtitle);

    drawButton(boxMargin + textPadding, boxPosY + textPadding + 115, 200, 50,
        "START EXPLORING");
}

void UI::drawMainSection(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
    const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected, const string& algorithmText,
    const bool& algorithmSelected) const {

    const float textPadding = 50;

    // Add back button
    Text back;
    back.setFont(fontBold);
    back.setString("Back to Home");
    back.setCharacterSize(16);
    back.setFillColor(Color(52, 152, 219));
    back.setPosition(textPadding, 260);
    window.draw(back);

    Text mainSectionText;
    mainSectionText.setFont(fontBold);
    mainSectionText.setString("Explore 2024 crime data across Los Angeles. Enter a location and set your radius to "
                              "discover incidents happening nearby - fast, focused, and accurate.");
    mainSectionText.setCharacterSize(20);
    mainSectionText.setFillColor(Color(44, 62, 80));
    mainSectionText.setPosition(textPadding, 300);
    window.draw(mainSectionText);

    drawForm(latitudeText, latitudeSelected, longitudeText, longitudeSelected, radiusText, radiusSelected,
        algorithmText, algorithmSelected);
}

void UI::drawForm(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
    const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected,
    const string& algorithmText, const bool& algorithmSelected) const {

    const float textPadding = 50;

    // Create form input fields
    Text latitudeLabel;
    latitudeLabel.setFont(fontRegular);
    latitudeLabel.setString("Enter latitude");
    latitudeLabel.setCharacterSize(16);
    latitudeLabel.setFillColor(Color(44, 62, 80));
    latitudeLabel.setPosition(textPadding, 350);

    window.draw(latitudeLabel);

    drawTextField(50, 380, 300, 40, "e.g., 34.052235",
        latitudeText, latitudeSelected);

    Text longitudeLabel;
    longitudeLabel.setFont(fontRegular);
    longitudeLabel.setString("Enter longitude");
    longitudeLabel.setCharacterSize(16);
    longitudeLabel.setFillColor(Color(44, 62, 80));
    longitudeLabel.setPosition(420, 350);

    window.draw(longitudeLabel);

    drawTextField(420, 380, 300, 40, "e.g., -77.0364",
        longitudeText, longitudeSelected);

    Text radiusLabel;
    radiusLabel.setFont(fontRegular);
    radiusLabel.setString("Enter radius between 1 and 10 miles");
    radiusLabel.setCharacterSize(16);
    radiusLabel.setFillColor(Color(44, 62, 80));
    radiusLabel.setPosition(780, 350);

    window.draw(radiusLabel);

    drawTextField(780, 380, 300, 40, "e.g., 6",
        radiusText, radiusSelected);

    Text algorithmLabel;
    algorithmLabel.setFont(fontRegular);
    algorithmLabel.setString("Select algorithm");
    algorithmLabel.setCharacterSize(16);
    algorithmLabel.setFillColor(Color(44, 62, 80));
    algorithmLabel.setPosition(1140, 350);

    window.draw(algorithmLabel);

    drawTextField(1140, 380, 300, 40, "Type 1 for K-D Tree or 2 for Heap",
    algorithmText, algorithmSelected);

    drawButton(textPadding, 460, 200, 50, "SEARCH");
}

void UI::drawTextField(float x, float y, float width, float height, const string& placeholder,
                     const string& textValue, const bool& selected) const {

    // Create the text field background
    RectangleShape background(Vector2f(width, height));
    background.setPosition(x, y);
    background.setFillColor(Color::White);

    // Change outline color based on selection state
    if (selected) {
        background.setOutlineColor(Color(52, 152, 219)); // Blue when selected
        background.setOutlineThickness(2);
    } else {
        background.setOutlineColor(Color(200, 200, 200)); // Gray when not selected
        background.setOutlineThickness(1);
    }

    window.draw(background);

    // Create the text display
    Text displayText;
    displayText.setFont(fontRegular);
    displayText.setCharacterSize(16);

    // Display either the text value or placeholder
    if (textValue.empty() && !selected) {
        displayText.setString(placeholder);
        displayText.setFillColor(Color(150, 150, 150)); // Lighter gray for placeholder
    } else {
        displayText.setString(textValue);
        displayText.setFillColor(Color(70, 70, 70)); // Darker gray for actual text
    }

    // Position text with a small padding
    displayText.setPosition(x + 10, y + (height - displayText.getCharacterSize()) / 2);
    window.draw(displayText);

    // Draw a cursor if the field is selected
    if (selected) {
        // Get current time to make cursor blink (about once per second)
        static Clock cursorClock;
        if (static_cast<int>(cursorClock.getElapsedTime().asSeconds() * 2) % 2 == 0) {
            RectangleShape cursor(Vector2f(1, height - 10));
            cursor.setFillColor(Color(70, 70, 70));

            // Position cursor at the end of the text
            FloatRect textBounds = displayText.getLocalBounds();
            cursor.setPosition(x + 10 + textBounds.width + 2, y + 5);

            window.draw(cursor);
        }
    }
}

void UI::drawResults(const vector<pair<CrimeData, double>>& results, int currentPage, int itemsPerPage, int totalPages,
    double algorithmDuration) const {
    const float textPadding = 50;

    // Add back button
    Text back;
    back.setFont(fontBold);
    back.setString("Back to Search");
    back.setCharacterSize(16);
    back.setFillColor(Color(52, 152, 219));
    back.setPosition(textPadding, 260);
    window.draw(back);

    drawResultsTable(results, currentPage, itemsPerPage, algorithmDuration);

    // Add summary to the right of the table
    if (!results.empty() && totalPages > 1) {
        drawPagination(currentPage, totalPages);

        Text summary;
        summary.setFont(fontRegular);
        summary.setCharacterSize(14);
        summary.setFillColor(Color(44, 62, 80));
        summary.setString(summarizeCrimeResults(results));
        summary.setPosition(1300, 300);
        window.draw(summary);
    }
}

void UI::drawButton(const float x, const float y, const float width, const float height, const string& textString) const {
    // Background rectangle
    RectangleShape button(Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(Color(52, 152, 219)); // #3498DB

    // Button text
    Text text;
    text.setFont(fontBold);
    text.setString(textString);
    text.setCharacterSize(16);
    text.setFillColor(Color::White);

    // Center text inside the button
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(x + width / 2, y + height / 2);

    // Draw to window
    window.draw(button);
    window.draw(text);
}

void UI::centerText(Text& text, const float yPosition) const {
    // Get window size for centering
    const Vector2u windowSize = window.getSize();
    const float windowWidth = static_cast<float>(windowSize.x);

    // Center the text dynamically
    FloatRect titleBounds = text.getLocalBounds();
    text.setOrigin(titleBounds.width / 2, 0);
    text.setPosition(windowWidth / 2, yPosition);
}

// https://stackoverflow.com/questions/73682637/how-can-i-convert-military-time-to-regular-time-the-regular-time-must-be-a-stri
string UI::fixTime(const string &time) const {
    int timeAsNum = stoi(time);

    int hours = timeAsNum / 100;
    int minutes = timeAsNum % 100;

    ostringstream oss;
    oss << setw(2) << setfill('0') << hours
        << ":"
        << setw(2) << setfill('0') << minutes;

    return oss.str();
}

void UI::drawResultsTable(const vector<pair<CrimeData, double>>& results, int currentPage, int itemsPerPage, double algorithmDuration) const {

    // Constants for table layout
    const float tableX = 50.f;
    const float tableY = 330.f;
    const float rowHeight = 40.f;
    const float colWidth[] = {150.f, 120.f, 150.f, 600.f, 200.f};
    const int numCols = 5;

    // Calculate start and end indices for current page
    int startIdx = currentPage * itemsPerPage;
    int endIdx = min(startIdx + itemsPerPage, static_cast<int>(results.size()));
    const int rowCount = endIdx - startIdx;

    // Show results
    Text resultCount;
    resultCount.setFont(fontRegular);

    if (results.empty())
        resultCount.setString("No search results found");
    else {
        int totalPages = (results.size() + itemsPerPage - 1) / itemsPerPage;
        resultCount.setString("Found " + to_string(results.size()) + " results" +
                  " (showing page " + to_string(currentPage + 1) + " of " +
                  to_string(totalPages) + ")");

        Text secondsText;
        secondsText.setFont(fontRegular);
        secondsText.setString("Seconds for algorithm to run: " + to_string(algorithmDuration));
        secondsText.setCharacterSize(15);
        secondsText.setFillColor(Color(100, 100, 100));
        secondsText.setPosition(400, 300);
        window.draw(secondsText);
    }

    resultCount.setCharacterSize(14);
    resultCount.setFillColor(Color(100, 100, 100));
    resultCount.setPosition(50, 300);
    window.draw(resultCount);

    // Table headers
    const string headers[] = {"Date", "Time", "Area", "Crime Type", "Location"};

    for (int col = 0; col < numCols; col++) {
        float x = tableX;
        for (int i = 0; i < col; i++) {
            x += colWidth[i];
        }

        // Header background
        RectangleShape headerBg(Vector2f(colWidth[col], rowHeight));
        headerBg.setPosition(x, tableY);
        headerBg.setFillColor(Color(52, 152, 219));
        window.draw(headerBg);

        // Header text
        Text headerText;
        headerText.setFont(fontBold);
        headerText.setString(headers[col]);
        headerText.setCharacterSize(16);
        headerText.setFillColor(Color::White);
        headerText.setPosition(x + 10.f, tableY + 10.f);
        window.draw(headerText);
    }

    // Draw table rows
    for (int row = 0; row < rowCount; row++) {
        const CrimeData& data = results[startIdx + row].first;
        float y = tableY + (row + 1) * rowHeight;

        // Row background (alternating colors for readability)
        RectangleShape rowBg(Vector2f(colWidth[0] + colWidth[1] + colWidth[2] + colWidth[3] + colWidth[4], rowHeight));
        rowBg.setPosition(tableX, y);
        rowBg.setFillColor(row % 2 == 0 ? Color(240, 240, 240) : Color(255, 255, 255));
        window.draw(rowBg);

        // Cell values
        string cellValues[] = {
            data.date,
            fixTime(data.time),
            data.areaName,
            data.category,
            to_string(data.latitude).substr(0, 8) + ", " + to_string(data.longitude).substr(0, 9)
        };

        // Draw each cell
        float x = tableX;
        for (int col = 0; col < numCols; col++) {
            Text cellText;
            cellText.setFont(fontRegular);
            cellText.setString(cellValues[col]);
            cellText.setCharacterSize(14);
            cellText.setFillColor(Color(44, 62, 80));
            cellText.setPosition(x + 10.f, y + 10.f);
            window.draw(cellText);

            x += colWidth[col];
        }
    }
}

void UI::drawPagination(int currentPage, int totalPages) const {
    // Position the pagination controls at the bottom of the table
    float windowWidth = static_cast<float>(window.getSize().x);
    float paginationY = 800.f;

    // Previous button
    if (currentPage > 0)
        drawButton(windowWidth / 2 - 250.f, paginationY, 120.f, 40.f, "< Previous");

    // Page indicator
    Text pageText;
    pageText.setFont(fontRegular);
    pageText.setString("Page " + to_string(currentPage + 1) + " of " + to_string(totalPages));
    pageText.setCharacterSize(15);
    pageText.setFillColor(Color(44, 62, 80));

    // Center the text
    FloatRect textBounds = pageText.getLocalBounds();
    pageText.setOrigin(textBounds.width / 2, 0);
    pageText.setPosition(windowWidth / 2 - 20.f, paginationY + 10.f);
    window.draw(pageText);

    // Next button
    if (currentPage < totalPages - 1)
        drawButton(windowWidth / 2 + 80.f, paginationY, 100.f, 40.f, "Next >");
}

string UI::summarizeCrimeResults(const vector<pair<CrimeData, double>>& results) const {
    // 1. Total crimes found
    string summaryString;
    summaryString += "Total crimes found: " + to_string(results.size()) + "\n\n";

    // Categories
    unordered_map<string, int> categoryCounts;
    unordered_map<string, int> dateCounts;
    unordered_map<string, int> areaCounts;

    for (const pair<CrimeData, double>& result : results) {
        categoryCounts[result.first.generalCategory]++;
        dateCounts[result.first.date]++;
        areaCounts[result.first.areaName]++;
    }

    auto comparer = [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    };

    vector<pair<string, int>> sortedCategories(categoryCounts.begin(), categoryCounts.end());
    sort(sortedCategories.begin(), sortedCategories.end(), comparer);

    summaryString += "Crimes by General Category:\n";
    for (int i = 0; i < sortedCategories.size() && i < 10; ++i) {
        summaryString += " - " + sortedCategories[i].first + ": " + to_string(sortedCategories[i].second) + "\n";
    }
    summaryString += "\n";

    vector<pair<string, int>> sortedDates(dateCounts.begin(), dateCounts.end());
    sort(sortedDates.begin(), sortedDates.end(), comparer);

    summaryString += "Top 3 Crime Dates:\n";
    for (int i = 0; i < sortedDates.size() && i < 3; ++i) {
        summaryString += " - " + sortedDates[i].first + ": " + to_string(sortedDates[i].second) + " crimes\n";
    }
    summaryString += "\n";

    // 4. Time of Day Breakdown
    int morning = 0, afternoon = 0, evening = 0, night = 0;

    for (const pair<CrimeData, double>& result : results) {
        const string& time = result.first.time;
        int hour = 0;

        if (time.length() == 4) {
            hour = stoi(time.substr(0, 2));
        } else if (time.length() == 3) {
            hour = stoi(time.substr(0, 1));
        } else {
            continue; // skip invalid times
        }

        if (hour < 6) night++;
        else if (hour < 12) morning++;
        else if (hour < 18) afternoon++;
        else evening++;
    }

    summaryString += "Crimes by Time of Day:\n";
    summaryString += " - Night (12am-6am): " + to_string(night) + "\n";
    summaryString += " - Morning (6am-12pm): " + to_string(morning) + "\n";
    summaryString += " - Afternoon (12pm-6pm): " + to_string(morning) + "\n";
    summaryString += " - Evening (6pm-12am): " + to_string(evening) + "\n\n";

    vector<pair<string, int>> sortedAreas(areaCounts.begin(), areaCounts.end());
    sort(sortedAreas.begin(), sortedAreas.end(), comparer);

    summaryString += "Top 3 Areas:\n";
    for (int i = 0; i < sortedAreas.size() && i < 3; ++i) {
        summaryString += " - " + sortedAreas[i].first += ": " + to_string(sortedAreas[i].second) + " crimes\n";
    }

    summaryString += "\n";
    return summaryString;
}