#include <SFML/Graphics.hpp>
#include "Snowman.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "Graph.h"
#include "Utils.h"
#include "chrono"


float get_delta_time(std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> start, std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    //Maine



    /*std::string s;
    std::cin >> s;*/

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML Window", sf::Style::Default, sf::State::Windowed, settings);

    Graph g;
    g.createRandomGraph(25, 1920, 1080);

    auto start = std::chrono::steady_clock::now();
    auto last_frame = start;
    auto now = start;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        now = std::chrono::steady_clock::now();

        float delta_time = get_delta_time(last_frame, now);

        if (get_delta_time(start, now) <= 5000) {
            g.update(delta_time / 250);
        }

        //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;


        window.clear();
        window.draw(g);
        window.display();

        last_frame = now;
    }
}
