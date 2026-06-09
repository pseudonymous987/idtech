#include <SFML/Graphics.hpp>
#include "Snowman.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "Graph.h"
#include "Utils.h"
#include "chrono"
#include "dfs.h"

using namespace std;

float get_delta_time(std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> start, std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    //Maine



    /*std::string s;
    std::cin >> s;*/

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    const int WIDTH = 1920;
    const int HEIGHT = 1080;

	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "SFML Window", sf::Style::Default, sf::State::Windowed, settings);

    Graph g(WIDTH, HEIGHT);
    g.createRandomGraph(15, WIDTH, HEIGHT);

    g.print();

    DFS dfs(g.adjList);
    dfs.traverse(g.adjList.begin()->first);

    auto start = std::chrono::steady_clock::now();
    auto last_frame = start;
    auto now = start;

    int step_speed = 1;
    auto searching_start = now;

    enum States {
        BALANCING,
        STABLE,
        SEARCHING
    };

    States state = BALANCING;

    while (window.isOpen()) { 
        while (const std::optional event = window.pollEvent()) { // sfml key and event handling
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        //current time and time from last frame
        now = std::chrono::steady_clock::now();
        float delta_time = get_delta_time(last_frame, now);

        //state machine
        switch (state) {
        case BALANCING : 
            if (get_delta_time(start, now) <= 15000) { //ammount of time graph spends balancing, in ms
                g.update(delta_time * 0.1); //rate of updates per frame
            } else {
                state = STABLE;
            }
        case STABLE :
            searching_start = now;
            state = SEARCHING;
        case SEARCHING :

            if () {

            }
            
        }

       
        //updates drawable objects
        window.clear();
        window.draw(g);
        window.display();

        last_frame = now;//updates last frame before frame iteration
    }
}
