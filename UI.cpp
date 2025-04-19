#include <iostream>
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

    // Load hero image
    if (!heroTexture.loadFromFile("images/hero-cropped.jpg"))
        cerr << "Failed to load hero image!" << endl;
}

void UI::drawTopNav() const {

    // Create navigation bar
    RectangleShape navBar(Vector2f(window.getSize().x, 50.f));
    navBar.setFillColor(Color(250, 250, 250));
    window.draw(navBar);

    // Create the logo
    Text logo;
    logo.setFont(fontBold);
    logo.setString("CrimeSphere");
    logo.setCharacterSize(30);
    logo.setFillColor(Color(44, 62, 80));;
    logo.setPosition(40.f, 8.f); // Positioned on the left side of the navigation bar
    window.draw(logo);

    // Create the first link
    Text link1;
    link1.setFont(fontRegular);
    link1.setString("Video");
    link1.setCharacterSize(20);
    link1.setFillColor(Color(44, 62, 80));
    link1.setPosition(window.getSize().x - 270.f, 12.f); // Right-aligned
    window.draw(link1);

    // Create the second link
    Text link2;
    link2.setFont(fontRegular);
    link2.setString("Documentation");
    link2.setCharacterSize(20);
    link2.setFillColor(Color(44, 62, 80));
    link2.setPosition(window.getSize().x - 180.f, 12.f); // Right-aligned
    window.draw(link2);
}

void UI::drawHeroBar(const string& textString) const {
    float windowWidth = static_cast<float>(window.getSize().x);
    RectangleShape titleBar(Vector2f(windowWidth, 150));
    titleBar.setFillColor(Color(52, 152, 219));
    titleBar.setPosition(0, 80);

    window.draw(titleBar);

    // Add subtitle text
    Text subtitle;
    subtitle.setFont(fontBold);
    subtitle.setString(textString);
    subtitle.setCharacterSize(30);
    subtitle.setFillColor(Color::White);
    subtitle.setPosition(50, 130);
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
    heroSprite.setPosition(0, 50);

    // Add a semi-transparent overlay for better text readability
    RectangleShape overlay(Vector2f(windowWidth, heroTexture.getSize().y * scale));
    overlay.setPosition(0, 50);
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
    float boxPosY = 50 + (heroHeight - boxHeight) / 2;

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

    // Text subtitleQ;
    // subtitleQ.setFont(fontRegular);
    // subtitleQ.setString("What would you like to do today?");
    // subtitleQ.setCharacterSize(18);
    // subtitleQ.setFillColor(Color::White);
    //
    // const float leftMargin = 20.0f;
    // subtitleQ.setPosition(leftMargin, 180);
    // window.draw(subtitleQ);
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
    mainSectionText.setString("Explore 2024 crime data across Los Angeles. Enter a location and set your radius to discover incidents happening nearby - fast, focused, and accurate.");
    mainSectionText.setCharacterSize(20);
    mainSectionText.setFillColor(Color(44, 62, 80));
    mainSectionText.setPosition(textPadding, 300);
    window.draw(mainSectionText);

    drawMenu(latitudeText, latitudeSelected, longitudeText, longitudeSelected, radiusText, radiusSelected,
        algorithmText, algorithmSelected);
}

void UI::drawMenu(const string& latitudeText, const bool& latitudeSelected, const string& longitudeText,
    const bool& longitudeSelected, const string& radiusText, const bool& radiusSelected,
    const string& algorithmText, const bool& algorithmSelected) const {
    const float textPadding = 50;

    // Create menu options
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

    drawTextField(1140, 380, 300, 40, "e.g., KD Tree",
        algorithmText, algorithmSelected);

    drawButton(textPadding, 460, 200, 50, "SEARCH");
}

void UI::drawResults(const vector<CrimeData>& results) const {
    const float textPadding = 50;

    // Add back button
    Text back;
    back.setFont(fontBold);
    back.setString("Back to Search");
    back.setCharacterSize(16);
    back.setFillColor(Color(52, 152, 219));
    back.setPosition(textPadding, 260);
    window.draw(back);

    drawResultsTable(results);
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

/* ======= Helpers - To be moved to Helpers.cpp ======= */
void UI::centerText(Text& text, const float yPosition) const {
    // Get window size for centering
    const Vector2u windowSize = window.getSize();
    const float windowWidth = static_cast<float>(windowSize.x);

    // Center the text dynamically
    FloatRect titleBounds = text.getLocalBounds();
    text.setOrigin(titleBounds.width / 2, 0);
    text.setPosition(windowWidth / 2, yPosition);
}

void UI::drawResultsTable(const vector<CrimeData>& results) const {

    // Constants for table layout
    const float tableX = 50.f;
    const float tableY = 330.f;
    const float rowHeight = 40.f;
    const float colWidth[] = {150.f, 150.f, 250.f, 250.f, 250.f};
    const int numCols = 5;

    // Create fake data if there are no results
    vector<CrimeData> displayData;
    if (results.empty()) {
        // Sample fake data
        CrimeData sample1;
        sample1.date = "04/15/2024";
        sample1.time = "14:35";
        sample1.areaName = "Downtown";
        sample1.category = "Theft";
        sample1.latitude = 34.052235;
        sample1.longitude = -118.243683;

        CrimeData sample2;
        sample2.date = "04/16/2024";
        sample2.time = "19:42";
        sample2.areaName = "Hollywood";
        sample2.category = "Vandalism";
        sample2.latitude = 34.092809;
        sample2.longitude = -118.328661;

        CrimeData sample3;
        sample3.date = "04/17/2024";
        sample3.time = "23:15";
        sample3.areaName = "Venice Beach";
        sample3.category = "Assault";
        sample3.latitude = 33.985047;
        sample3.longitude = -118.469116;

        CrimeData sample4;
        sample4.date = "04/18/2024";
        sample4.time = "08:27";
        sample4.areaName = "Silver Lake";
        sample4.category = "Burglary";
        sample4.latitude = 34.089958;
        sample4.longitude = -118.267254;

        CrimeData sample5;
        sample5.date = "04/18/2024";
        sample5.time = "11:03";
        sample5.areaName = "Echo Park";
        sample5.category = "Auto Theft";
        sample5.latitude = 34.072231;
        sample5.longitude = -118.259939;

        displayData.push_back(sample1);
        displayData.push_back(sample2);
        displayData.push_back(sample3);
        displayData.push_back(sample4);
        displayData.push_back(sample5);
    } else {
        displayData = results;
    }

    const int maxRows = 10;
    // const int rowCount = min(maxRows, static_cast<int>(results.size()));
    const int rowCount = min(maxRows, static_cast<int>(displayData.size()));

    // Results count
    Text resultCount;
    resultCount.setFont(fontRegular);

    // Add this condition to show different text for fake data
    if (results.empty()) {
        resultCount.setString("Showing 5 sample records (no search results found)");
    } else {
        resultCount.setString("Found " + to_string(results.size()) + " results" +
                          (results.size() > maxRows ? " (showing first " + to_string(maxRows) + ")" : ""));
    }

    resultCount.setCharacterSize(14);
    resultCount.setFillColor(Color(100, 100, 100));
    resultCount.setPosition(50, 300);
    window.draw(resultCount);

    // Table headers
    const string headers[] = {"Date", "Time", "Area", "Crime Type", "Location"};

    // Draw table headers
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
        // const CrimeData& data = results[row];
        const CrimeData& data = displayData[row];
        float y = tableY + (row + 1) * rowHeight;

        // Row background (alternating colors for readability)
        RectangleShape rowBg(Vector2f(colWidth[0] + colWidth[1] + colWidth[2] + colWidth[3] + colWidth[4], rowHeight));
        rowBg.setPosition(tableX, y);
        rowBg.setFillColor(row % 2 == 0 ? Color(240, 240, 240) : Color(255, 255, 255));
        window.draw(rowBg);

        // Cell values
        string cellValues[] = {
            data.date,
            data.time,
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