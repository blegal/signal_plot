#include "SoundSystem.h"


SoundSystem::SoundSystem( RawSound* buffer ) :
    liste(),
    _fName( "None" )
{
    SoundView* sv1   = new SoundView(buffer);
    sv1->setYOffset (   0 );
    liste.push_back( sv1 );

    SoundView* sv2   = new SoundView(buffer);
    sv2->setYOffset ( 256 );
    liste.push_back( sv2 );
}


void SoundSystem::update_ref(RawSound *buffer)
{
    liste.at(0)->update( buffer );
}


void SoundSystem::update_mod(RawSound *buffer)
{
    liste.at(1)->update( buffer );
}


void SoundSystem::zoom_in()
{
    for (unsigned i=0; i<liste.size(); i++)
        liste.at(i)->zoom_in();
}


void SoundSystem::zoom_out()
{
    for (unsigned i=0; i<liste.size(); i++)
        liste.at(i)->zoom_out();
}


void SoundSystem::slide_left()
{
    for (unsigned i=0; i<liste.size(); i++)
        liste.at(i)->slide_left();
}


void SoundSystem::slide_right()
{
    for (unsigned i=0; i<liste.size(); i++)
        liste.at(i)->slide_right();
}


void SoundSystem::update_fName(std::string _name)
{
    _fName = _name;
}


void SoundSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // nos particules n'utilisent pas de texture
    states.texture = NULL;

    for (unsigned i=0; i<liste.size(); i++)
        liste.at(i)->draw(target, states);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(0,    256)),
        sf::Vertex(sf::Vector2f(1280, 256))
    };
    target.draw(line, 2, sf::Lines);

    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
        exit( 1 );


{
    sf::Text t_filter_name;
    t_filter_name.setFont(font);
    t_filter_name.setCharacterSize(18);
    t_filter_name.setPosition(170.f, 150.f);
    t_filter_name.setColor(sf::Color::White);
    t_filter_name.setString(_fName);
    target.draw(t_filter_name);
}

    GL_Button simd("SIMD", 512.f, 16.f);
    simd.draw(target, states);

    GL_Button mcores("M-Cores", 640.f, 16.f);
    mcores.draw(target, states);

    GL_Button fixedp("Fixed-Point", 768.f, 16.f);
    fixedp.draw(target, states);

}
