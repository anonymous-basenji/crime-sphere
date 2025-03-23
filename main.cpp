#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "FileProcessing.h"
#include "Frame.h"
#include "Helpers.h"

using namespace std;
using namespace sf;

int main() {

    // Create main frame for app
    RenderWindow window(VideoMode(1024, 768), "CrimeSphere - Crime Data Visualization");
    window.setFramerateLimit(60);

    // Create UI
    Frame frame(window);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        
        frame.drawFrame();
    }

    // Todo: Read and Process file to return info based on user selection
    // FileProcessing::ReadFile();

    /* ========= Print data for debugging ========= */
    Helpers helpers;
    // Helpers::PrintDate(fileProcessing);
    // helpers.PrintAreaName(fileProcessing);

    return 0;
}
