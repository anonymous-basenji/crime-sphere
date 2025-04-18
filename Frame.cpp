#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"

using namespace std;
using namespace sf;

Frame::Frame(RenderWindow& window)
    : window(window), ui(window), currentPage(HOME) {
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

void Frame::drawHomeScreen() const {
    ui.drawHero();
}

void Frame::drawSearchScreen() const {
    // ui.drawHero();
}

void Frame::drawResultsScreen() const {
    // ui.drawHero();
}

void Frame::switchPage(AppPage page) {
    currentPage = page;
}

bool Frame::handleEvent(Event event) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);

        // Handle events based on current page
        switch (currentPage) {
        case HOME:
            // Check if the START EXPLORING button was clicked
            if (mousePos.x >= 80 && mousePos.x <= 280 &&
                mousePos.y >= 195 && mousePos.y <= 245) {

                    switchPage(SEARCH);
                    return true;
                }
            break;

        case SEARCH:
            // Check if search button was clicked
            if (mousePos.x >= 80 && mousePos.x <= 280 &&
                mousePos.y >= 580 && mousePos.y <= 630) {

                switchPage(RESULTS);
                return true;
                }
            break;

        case RESULTS:
            // Check if back button was clicked
            if (mousePos.x >= 80 && mousePos.x <= 280 &&
                mousePos.y >= 600 && mousePos.y <= 650) {

                switchPage(SEARCH);
                return true;
                }
            break;
        }
    }

    return false;
}