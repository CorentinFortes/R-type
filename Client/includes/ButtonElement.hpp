/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** ButtonElement
*/

#include "InetrfaceElement.hpp"

class ButtonElement : public InetrfaceElement
{
public:
    ButtonElement(
        size_t id,
        int x = 0,
        int y = 0,
        double height = 100,
        double width = 300,
        int rotation = 0,
        int originX = 0,
        int originY = 0,
        std::string text = "Press it")
    {
        _id = id;

        std::cout << "ButtonElement constructor" << width << std::endl;

        _buttonShape = sf::RectangleShape(sf::Vector2f(width, height));
        _buttonShape.setPosition(x, y);
        _buttonShape.setRotation(rotation);
        _buttonShape.setOrigin(originX, originY);
        _buttonShape.setFillColor(_defaultColor);

        _buttonText = sf::Text();
        _buttonText.setString(text);
        _buttonText.setFillColor(_textColor);

        _buttonText.setStyle(sf::Text::Bold);
        _buttonText.setOutlineColor(sf::Color::Black);

        // Center the text within the button
        sf::FloatRect textBounds = _buttonText.getLocalBounds();
        _buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        _buttonText.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void render(sf::RenderWindow &window) override
    {
        window.draw(_buttonShape);
        window.draw(_buttonText);
    }

    void setFont(const sf::Font &font)
    {
        _buttonText.setFont(font);
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window) override;
    bool isClicked() const;
    bool isHeld() const;

private:
    sf::Color _defaultColor = sf::Color(0, 128, 0); // Green
    sf::Color _hoverColor = sf::Color(0, 255, 0);   // Light Green
    sf::Color _clickColor = sf::Color(128, 0, 0);   // Red
    sf::Color _textColor = sf::Color::White;        // Default text color
    sf::Color _clickTextColor = sf::Color::Black;   // Text color when clicked

    sf::RectangleShape _buttonShape;
    sf::Text _buttonText;
    bool _isClickedState;
    bool _isHeldState;
};

void ButtonElement::handleEvent(sf::Event event, sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isMouseOver = _buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    if (_isHeldState)
    {
        _buttonShape.setFillColor(_clickColor);
        _buttonText.setFillColor(_clickTextColor);
    }
    else if (isMouseOver)
    {
        _buttonShape.setFillColor(_hoverColor);
        _buttonText.setFillColor(_textColor);
    }
    else
    {
        _buttonShape.setFillColor(_defaultColor);
        _buttonText.setFillColor(_textColor);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (isMouseOver)
            {
                _isHeldState = true;
                _buttonText.setString("Hold it");
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            _isHeldState = false;
            if (isMouseOver)
            {
                _isClickedState = true;
            }
            _buttonText.setString("Press it");
        }
    }
}

bool ButtonElement::isClicked() const
{
    return _isClickedState;
}

bool ButtonElement::isHeld() const
{
    return _isHeldState;
}