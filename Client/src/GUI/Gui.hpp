#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Gui
{
private:
    std::unique_ptr<sf::RenderWindow> _window;

public:
    Gui();
    ~Gui();
    std::unique_ptr<sf::RenderWindow> &getWindow();
    int test = 0;
};
