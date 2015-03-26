#include "GL_Button.h"

GL_Button::GL_Button( std::string _text, int _x, int _y ) :
    text(), textRec(), font()
{
    texte  = _text;
    enable = false;
    posX   = _x;
    posY   = _y;

    if (!font.loadFromFile("resources/sansation.ttf"))
        exit( 1 );

    text.setFont(font);
    text.setCharacterSize(14);
    text.setPosition(posX, posY);
    text.setColor(sf::Color::Red);
    text.setString( _text );

    sf::FloatRect textBounds = text.getLocalBounds() ;
    textRec.setSize(sf::Vector2f(textBounds.width + 16.0, textBounds.height + 16.0)) ;
    textRec.setPosition(posX - 8.f, posY - 4.f) ;
    textRec.setFillColor   (sf::Color::White) ;
    textRec.setOutlineColor(sf::Color::Red);
    textRec.setOutlineThickness(1);
//    setText( texte );
}

void GL_Button::setEnable(bool _e)
{
    enable = _e;
}


bool GL_Button::isEnable()
{
    return enable;
}

void GL_Button::setText( std::string _text )
{

}

void GL_Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(textRec);
    target.draw(text);
}
