#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

#include "Frame.h"
#include "FileProcessing.h"

Frame::Frame(RenderWindow& window) : window(window) {
    // Load Fonts
    if (!fontRegular.loadFromFile("font/OpenSans-Regular.ttf"))
        cerr << "Failed to load font!" << endl;
    if (!fontBold.loadFromFile("font/OpenSans-Bold.ttf"))
        cerr << "Failed to load font!" << endl;
}

void Frame::drawFrame() {

    window.clear(Color(50, 50, 80));

    drawHeader();
    drawMenu();

    window.display();window.clear(Color(50, 50, 80));

    drawHeader();
    drawMenu();

    window.display();

    // cout << "**************************************" << endl;
    // cout << "*        Welcome to CrimeSphere!     *" << endl;
    // cout << "**************************************" << endl << endl;
    //
    // cout << "Prepare to explore the world of crime data!" << endl << endl;
    //
    // cout << "✨ What would you like to do today? ✨" << endl << endl;
    //
    // cout << "1. 🔍 Search by latitude and longitude." << endl;
    // cout << "2. 💼 Search by crime type." << endl;
    //
    // cout << "--------------------------------------" << endl;
    // cout << "Enter your choice and let's get started!" << endl;
    //
    // int searchOption;
    // cin >> searchOption;
    //
    // switch (searchOption) {
    //     case 1:
    //     {
    //         double latitude, longitude;
    //
    //         cout << "🌍 Please enter the latitude of the location you're searching for:" << endl;
    //
    //         if (cin >> latitude) {
    //             int radius;
    //             cout << "📍 Now, please enter the longitude for your search:" << endl;
    //             cin >> longitude;
    //
    //             // Todo: Add validation for correct longitude and latitude format
    //
    //             // Todo: make this into a function
    //             cout << "🔎 Almost there! Now, enter a search radius between 1 and 5 miles:" << endl;
    //
    //             if (cin >> radius) {
    //                 FileProcessing::addSearchParameters(latitude, longitude, radius);
    //
    //                 // Start - Debug
    //                 cout << "Stored: Latitude " << latitude
    //                      << ", Longitude " << longitude
    //                      << ", Radius " << radius << endl;
    //                 // End - Debug
    //
    //                 // Todo: make this into a function
    //                 cout << "🚀 Ready to dive into the world of algorithms? Choose your path!" << endl;
    //                 cout << "1. K-D Tree Algorithm - Efficiently handle large datasets in multidimensional spaces!" << endl;
    //                 cout << "2. Dijkstra's Algorithm - Find the shortest path like a pro!" << endl;
    //
    //                 int algorithm;
    //                 if (cin >> algorithm) {
    //                     if (algorithm == 1) {
    //                         // Todo: Call K-D Tree algorithm
    //
    //                         // Start Debug
    //                         cout <<  "You selected: " << algorithm << endl;
    //                         // End Debug
    //                         break;
    //                     } else if (algorithm == 2) {
    //                         // Todo: Call Dijkstra's algorithm
    //
    //                         // Start Debug
    //                         cout <<  "You selected: " << algorithm << endl;
    //                         // End Debug
    //                         break;
    //                     } else {
    //                         cout << "Oops! That's not a valid option. Please choose either 1 or 2 to continue." << endl;
    //                         cin.clear();
    //                         // Source: ChatGPT to discard invalid or leftover input from the buffer
    //                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //                     }
    //                 }
    //             }
    //         }
    //         break;
    //     }
    //     case 2:
    //     {
    //         int crimeTypeOption;
    //         string crimeType;
    //         bool validSelection = false;
    //
    //         while (!validSelection) {
    //             cout << "Select the crime type you'd like to search for from the list below:" << endl;
    //             cout << "1. Vehicle - Stolen" << endl;
    //             cout << "2. Bike - Stolen" << endl;
    //             cout << "3. Burglary" << endl;
    //             cout << "4. Burglary From Vehicle" << endl;
    //             cout << "5. Pimping" << endl;
    //             cout << "6. Shoplifting" << endl;
    //             cout << "7. Pandering" << endl;
    //             cout << "8. Vandalism" << endl;
    //             cout << "9. Robbery" << endl;
    //             cout << "10. Other Miscellaneous Crime" << endl;
    //
    //             if (cin >> crimeTypeOption) {
    //                 if (crimeTypeOption >= 1 && crimeTypeOption <= 10) {
    //                     switch (crimeTypeOption) {
    //                         case 1: crimeType = "Vehicle - Stolen"; break;
    //                         case 2: crimeType = "Bike - Stolen"; break;
    //                         case 3: crimeType = "Burglary"; break;
    //                         case 4: crimeType = "Burglary From Vehicle"; break;
    //                         case 5: crimeType = "Pimping"; break;
    //                         case 6: crimeType = "Shoplifting"; break;
    //                         case 7: crimeType = "Pandering"; break;
    //                         case 8: crimeType = "Vandalism"; break;
    //                         case 9: crimeType = "Robbery"; break;
    //                         case 10: crimeType = "Other Miscellaneous Crime"; break;
    //                     }
    //
    //                     int radius = 0;
    //                     cout << "🔎 Almost there! Now, enter a search radius between 1 and 5 miles:" << endl;
    //
    //                     if (cin >> radius) {
    //                         if (radius >= 1 && radius <= 5) {
    //                             FileProcessing::addCrimeTypeParameters(crimeType, radius);
    //
    //                             // Start - Debug
    //                             cout << "Stored: Type " << crimeType
    //                                  << ", Radius " << radius << endl;
    //                             // End - Debug
    //
    //                             validSelection = true; // Only set true when everything is valid
    //
    //                             cout << "🚀 Ready to dive into the world of algorithms? Choose your path!" << endl;
    //                             cout << "1. K-D Tree Algorithm - Efficiently handle large datasets in multidimensional spaces!" << endl;
    //                             cout << "2. Dijkstra's Algorithm - Find the shortest path like a pro!" << endl;
    //
    //                             int algorithm;
    //                             if (cin >> algorithm) {
    //                                 if (algorithm == 1) {
    //                                     // Todo: Call K-D Tree algorithm
    //
    //                                     // Start Debug
    //                                     cout <<  "You selected: " << algorithm << endl;
    //                                     // End Debug
    //                                     break;
    //                                 } else if (algorithm == 2) {
    //                                     // Todo: Call Dijkstra's algorithm
    //
    //                                     // Start Debug
    //                                     cout <<  "You selected: " << algorithm << endl;
    //                                     // End Debug
    //                                     break;
    //                                 } else {
    //                                     cout << "Invalid option. Please select either 1 or 2." << endl;
    //                                     cin.clear();
    //                                     // Source: ChatGPT to discard invalid or leftover input from the buffer
    //                                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //                                 }
    //                             }
    //                         } else {
    //                             cout << "Invalid radius. Please enter a number between 1 and 5." << endl;
    //                             cin.clear();
    //                             // Source: ChatGPT to discard invalid or leftover input from the buffer
    //                             cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //                         }
    //                     } else {
    //                         cout << "Invalid input for radius. Please try again." << endl;
    //                         cin.clear();
    //                         // Source: ChatGPT to discard invalid or leftover input from the buffer
    //                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //                     }
    //                 } else {
    //                     cout << "Invalid selection. Please enter a number between 1 and 10." << endl;
    //                 }
    //             } else {
    //                 cout << "Invalid input. Please enter a number." << endl;
    //                 cin.clear();
    //                 // Source: ChatGPT to discard invalid or leftover input from the buffer
    //                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //             }
    //         }
    //         // Todo: fix validation to only ask for radius if wrong number is added and not type
    //         break;
    //     }
    //     default:
    //         cout << "Invalid option selected!" << endl;
    //         break;
    // }
}

void Frame::drawHeader() {

    Text title;
    title.setFont(fontBold);
    title.setString("Welcome to CrimeSphere!");
    title.setCharacterSize(30);
    title.setFillColor(Color::White);
    centerText(title, 50);
    window.draw(title);

    Text subtitle;
    subtitle.setFont(fontRegular);
    subtitle.setString("Prepare to explore the world of crime data!");
    subtitle.setCharacterSize(20);
    subtitle.setFillColor(Color::White);
    centerText(subtitle, 100);
    window.draw(subtitle);

    Text subtitleQ;
    subtitleQ.setFont(fontRegular);
    subtitleQ.setString("What would you like to do today?");
    subtitleQ.setCharacterSize(18);
    subtitleQ.setFillColor(Color::White);

    const float leftMargin = 20.0f;
    subtitleQ.setPosition(leftMargin, 180);
    window.draw(subtitleQ);
}

void Frame::drawMenu() {
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

/* ======= Helpers - To be moved to Helpers.cpp ======= */
void Frame::centerText(Text& text, const float yPosition) const {
    // Get window size for centering
    const Vector2u windowSize = window.getSize();
    const float windowWidth = static_cast<float>(windowSize.x);

    // Center the text dynamically
    FloatRect titleBounds = text.getLocalBounds();
    text.setOrigin(titleBounds.width / 2, 0);
    text.setPosition(windowWidth / 2, yPosition);
}
