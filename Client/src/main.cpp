#include <SFML/Graphics.hpp>
#include "GUI/Gui.hpp"
#include <memory>

int main()
{
    sf::Sprite spritePlayer;
    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("../assets/player.png");
    spritePlayer.setTexture(texturePlayer);

    std::unique_ptr<Gui> gui;
    gui = std::make_unique<Gui>();
    while (gui->getWindow())
    {
        sf::Event event;
        while (gui->getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gui->getWindow()->close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                gui->getWindow()->close();
        }

        gui->getWindow()->clear();
        gui->getWindow()->draw(spritePlayer);
        gui->getWindow()->display();
    }
    printf("%d", gui->test);
    return 0;
}
