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
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(24); // in pixels, not points!

    sf::RenderTexture image;
    sf::Texture texture;
    texture.loadFromFile("background.png");
    sf::Sprite sprite(texture);


    sf::Text help;
    help.setFont(font);
    help.setCharacterSize(24);
    help.setFillColor(sf::Color::White);

    sf::Event event;
    sf::String userInput;

    text.setPosition(60, 300);
    help.setPosition(60, 200);

    sf::String helpString = "Enter filename to continue.";
    help.setString(helpString);

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
                    if      (err == 1) text.setString("Wrong file link.");
                    else if (err == 2) text.setString("This file is not supported.");
                    else if (err == 0) text.setString("Success.");
                }
            }
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.draw(help);
        window.display();
    }

    return 0;
}

