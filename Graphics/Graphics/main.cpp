#include <SFML/Graphics.hpp>
#include "Snowman.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "Graph.h"
#include "Utils.h"
#include "chrono"
#include "dfs.h"
#include "bfs.h"

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

    cout << endl << "--- DFS ---" << endl;
    DFS dfs(g.adjList);
    vector<Node*> dfs_result = dfs.traverse(g.adjList.begin()->first);

    cout << endl << "--- BFS ---" << endl;
    BFS bfs(g.adjList);

    /*using Duration = std::chrono::duration<double>;
    Duration cooldown_timer = */

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
            break;

        case STABLE :
            searching_start = now;
            state = SEARCHING;
            break;

        case SEARCHING :

            if (dfs_result.size() > 0) {
                if (get_delta_time(searching_start, now) <= 1000) {
                    Node* temp = dfs_result.front();
                    dfs_result.erase(dfs_result.begin());
                    temp->setColor(sf::Color::Blue);
                    searching_start = now;
                }
            }
            break;
        }

       
        //updates drawable objects
        window.clear();
        window.draw(g);
        window.display();

        last_frame = now;//updates last frame before frame iteration
    }
}
