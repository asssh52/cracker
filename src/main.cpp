#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../hpp/hack.hpp"

#define DELETE_KEY 13

int main(int argc, const char* argv[])
{
    //if (argc == 2) crackProgramm(argv[1]);
    //else printf("usage:\"./main \'file\'\"\n");

    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");

    sf::Font font;
    printf("%d\n", font.loadFromFile("./misc/movistar.ttf"));
    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    //text.setString("Hello world");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         // inside the main loop, between window.clear() and window.display()
//
//
//         window.clear();
//         window.draw(text);
//         window.display();
//     }

    sf::Event event;
    sf::String userInput;

    text.setPosition(60,300);

    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\n'){
                    userInput += event.text.unicode;
                    text.setString(userInput);
                }

                if (event.text.unicode == '\b'){
                    userInput.clear();
                    text.setString(userInput);
                }

                if (event.text.unicode == '\n'){
                    std::string str = userInput.toAnsiString();
                    const char* fileName = str.c_str();

                    printf("%s\n", fileName);
                    int err = crackProgramm(fileName);

                    printf("err:%d\n", err);

                    userInput.clear();
                    text.setString("meow");
                }
            }
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}

