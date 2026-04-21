#include <SFML/Graphics.hpp>
#include "Snowman.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "Graph.h"
#include "Utils.h"

int main() {
    //Maine



    /*std::string s;
    std::cin >> s;*/

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML Window", sf::Style::Default, sf::State::Windowed, settings);

    Graph g;
    g.createRandomGraph(25, 1920, 1080);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        Time::Update();
        g.update();

        window.clear();
        window.draw(g);
        window.display();
    }
}

//next time, use the brute force method for installing libraries and spare yourself a lot of time and nightmares. (not in the forseeable future!!!)
