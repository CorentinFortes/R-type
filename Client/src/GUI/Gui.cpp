#include "Gui.hpp"

Gui::Gui()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "r-type");
    this->_window->setFramerateLimit(60);
    this->_window->setActive(false);
}

Gui::~Gui()
{
}

std::unique_ptr<sf::RenderWindow> &Gui::getWindow()
{
    return this->_window;
}