#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "heap/CrimeHeap.h"
#include "FileProcessing.h"
#include "Frame.h"
#include "Helpers.h"

using namespace std;
using namespace sf;

int main() {

    // Create main frame for app
    RenderWindow window(VideoMode(1680, 600), "CrimeSphere - Crime Data Visualization");
    window.setFramerateLimit(60);

    // Create UI
    Frame frame(window);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Handle events in our frame
            frame.handleEvent(event);
        }

        // Draw current screen
        frame.drawFrame();
    }

    return 0;
}
