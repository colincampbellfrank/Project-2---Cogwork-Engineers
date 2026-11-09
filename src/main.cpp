//
// Created by colin on 11/2/2026.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "DataPoint.h"
#include "bPlus.h"
#include "DataHeap.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

// SFML template https://www.sfml-dev.org/documentation/3.1.0/

int main() {
    ifstream file("../../resources/WHO-COVID-19-global-daily-data.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;

    //skip header
    getline(file, line);

    //allocate vector so process of loading everything is faster
    vector<DataPoint> data;
    data.reserve(583441);

    //read line by line, skipping country_code since redundant for us
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> row;

        while (ss.good()) {
            if (ss.peek() == '"') { //cells that contain a comma themselves will start with a quote, exception condition
                ss.get(); //get rid of start quote
                getline(ss, field, '"'); //read until end quote
                if (ss.peek() == ',') ss.get(); //get rid of comma following the quote
            } else {
                //all normal cells
                getline(ss, field, ',');
            }

            if (field.empty()) field = "0"; //correct for empty cells
            row.push_back(field);
        }
        DataPoint data_point=DataPoint(row[0], row[2], row[3], row[4], row[5], row[6], row[7]);
        data.push_back(data_point);
    }
    file.close();




    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Covid Data Search");

    const sf::Font font("../../resources/arial.ttf");


    // Create Title
    sf::Text title(font, "WHO COVID Data Search", 45);
    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(15, 10));

    sf::RectangleShape  title_box(sf::Vector2f(550, 50));
    title_box.setFillColor(sf::Color(211, 211, 211));
    title_box.setPosition({10.f, 10.f});


    // Create Results box
    sf::Text results_name(font, "Found Data:", 20);
    results_name.setFillColor(sf::Color::Black);
    results_name.setPosition(sf::Vector2f(15, 100));

    sf::RectangleShape  results_name_box(sf::Vector2f(120, 23));
    results_name_box.setFillColor(sf::Color(211, 211, 211));
    results_name_box.setPosition({10.f, 100.f});

    sf::RectangleShape  results_box(sf::Vector2f(400, 300));
    results_box.setFillColor(sf::Color(211, 211, 211));
    results_box.setPosition({10.f, 130.f});


    // Create Search filters box
    sf::Text search_name(font, "Search Filters:", 20);
    search_name.setFillColor(sf::Color::Black);
    search_name.setPosition(sf::Vector2f(485, 100));

    sf::RectangleShape  search_name_box(sf::Vector2f(140, 23));
    search_name_box.setFillColor(sf::Color(211, 211, 211));
    search_name_box.setPosition({480.f, 100.f});

    sf::RectangleShape  search_box(sf::Vector2f(250, 200));
    search_box.setFillColor(sf::Color(211, 211, 211));
    search_box.setPosition({480.f, 130.f});


    // Create timer boxes
    // Tree
    sf::Text bPlus_name(font, "B+ Tree Time:", 20);
    bPlus_name.setFillColor(sf::Color::Black);
    bPlus_name.setPosition(sf::Vector2f(485, 400));

    sf::RectangleShape  bPlus_name_box(sf::Vector2f(155, 23));
    bPlus_name_box.setFillColor(sf::Color(211, 211, 211));
    bPlus_name_box.setPosition({480.f, 400.f});

    sf::RectangleShape  bPlus_box(sf::Vector2f(80, 23));
    bPlus_box.setFillColor(sf::Color(211, 211, 211));
    bPlus_box.setPosition({650.f, 400.f});


    // Heap
    sf::Text heap_name(font, "Max Heap Time:", 20);
    heap_name.setFillColor(sf::Color::Black);
    heap_name.setPosition(sf::Vector2f(485, 440));

    sf::RectangleShape  heap_name_box(sf::Vector2f(155, 23));
    heap_name_box.setFillColor(sf::Color(211, 211, 211));
    heap_name_box.setPosition({480.f, 440.f});

    sf::RectangleShape  heap_box(sf::Vector2f(80, 23));
    heap_box.setFillColor(sf::Color(211, 211, 211));
    heap_box.setPosition({650.f, 440.f});


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear(sf::Color(93, 97, 102));

        // Draw all shapes and strings
        window.draw(title_box);
        window.draw(title);

        window.draw(results_name_box);
        window.draw(results_name);
        window.draw(results_box);

        window.draw(search_name_box);
        window.draw(search_name);
        window.draw(search_box);

        window.draw(bPlus_name_box);
        window.draw(bPlus_name);
        window.draw(bPlus_box);

        window.draw(heap_name_box);
        window.draw(heap_name);
        window.draw(heap_box);

        // Update the window
        window.display();
    }

    return 0;
}