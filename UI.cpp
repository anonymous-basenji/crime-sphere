#include <iostream>
#include <SFML/Graphics.hpp>
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
    navBar.setFillColor(Color(52, 152, 219)); // bright blue background color
    window.draw(navBar);

    // Create the logo
    Text logo;
    logo.setFont(fontBold);
    logo.setString("CrimeSphere");
    logo.setCharacterSize(30);
    logo.setFillColor(Color::White);
    logo.setPosition(40.f, 8.f); // Positioned on the left side of the navigation bar
    window.draw(logo);

    // Create the first link
    Text link1;
    link1.setFont(fontRegular);
    link1.setString("Video");
    link1.setCharacterSize(20);
    link1.setFillColor(Color::White);
    link1.setPosition(window.getSize().x - 270.f, 12.f); // Right-aligned
    window.draw(link1);

    // Create the second link
    Text link2;
    link2.setFont(fontRegular);
    link2.setString("Documentation");
    link2.setCharacterSize(20);
    link2.setFillColor(Color::White);
    link2.setPosition(window.getSize().x - 180.f, 12.f); // Right-aligned
    window.draw(link2);
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

    drawButton(boxMargin + textPadding, boxPosY + textPadding + 115, 200, 50, "START EXPLORING");

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

void UI::drawMainSection() const {
    const float textPadding = 50;

    Text mainSectionText;
    mainSectionText.setFont(fontBold);
    mainSectionText.setString("Explore 2024 crime data across Los Angeles. Enter a location and set your radius to discover incidents happening nearby - fast, focused, and accurate.");
    mainSectionText.setCharacterSize(20);
    mainSectionText.setFillColor(Color(44, 62, 80));
    mainSectionText.setPosition(textPadding, 650);
    window.draw(mainSectionText);
}

void UI::drawMenu() const {
    // Get window size for centering
    Vector2u windowSize = window.getSize();
    const float leftMargin = 20.0f;

    // Create menu options
    Text option1Text;
    option1Text.setFont(fontRegular);
    option1Text.setString("1. Search by latitude and longitude");
    option1Text.setCharacterSize(16);
    option1Text.setFillColor(Color::White);
    option1Text.setPosition(leftMargin, 210);

    Text option2Text;
    option2Text.setFont(fontRegular);
    option2Text.setString("2. Search by crime type");
    option2Text.setCharacterSize(16);
    option2Text.setFillColor(Color::White);
    option2Text.setPosition(leftMargin, 240);

    // Draw menu options
    window.draw(option1Text);
    window.draw(option2Text);
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