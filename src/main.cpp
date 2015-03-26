
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "SoundSystem.h"
#include "./filters/noise/NoiseAWNG.h"
#include "./filters/FilterLibrary.h"

#include <iomanip>
#include <iostream>
#include <math.h>

#define abs(x) ((x<0?(-x):(x)))

////////////////////////////////////////////////////////////
/// Play a sound
///
////////////////////////////////////////////////////////////

void playS(RawSound* _buffer)
{
    sf::SoundBuffer buffer;
    buffer.loadFromSamples(
            _buffer->data(),
            _buffer->length (),
            _buffer->channels(),
            _buffer->sample_rate()
    );
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    sf::Sound sound(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << std::fixed << std::setprecision(2) << sound.getPlayingOffset().asSeconds() << " sec   ";
        std::cout << std::flush;
    }
}



void mono_2_stereo(RawSound *_in, RawSound *_out)
{
    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(2, 2*_in->length(), _in->sample_rate());

    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    for (int i = 0; i < n; i++)
    {
        out[2*i  ] = in[i];
    }

    int delay = (int)(0.020 * _in->sample_rate()); // 20ms delay
    for (int i = 0; i < delay; i++)
    {
        out[2*i+1] = 0;
    }
    for (int i = delay; i < n; i++)
    {
        out[2*i+1] = in[i-delay];
    }
}

void stereo_2_mono_fx_1(RawSound *_in, RawSound *_out)
{
    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(1, _in->length()/2, _in->sample_rate());
    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    for (int i = 0; i < n/2; i++)
    {
        out[i] = ((int)in[2*i] + (int)in[2*i+1])/2;
    }
}

//
//
//
void stereo_2_mono_fx_2(RawSound *_in, RawSound *_out)
{
    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(1, _in->length()/2, _in->sample_rate());
    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    for (int i = 0; i < n/2; i++)
    {
        out[i] = in[2*i] > in[2*i+1] ? in[2*i] : in[2*i+1];
    }
}

void ph_filter(short *in, short *out, int n)
{
    for (int i = 1; i < n; i++)
    {
        out[i-1] = in[i] - in[i-1];
    }out[n-1] = 0;
}


void lp_filter(short *in, short *out, int n)
{
    for (int i = 1; i < n; i++)
    {
        out[i-1] = ((int)in[i] + (int)in[i-1])/2;
    }out[n-1] = 0;
}


void enhance_filter(short *in, short *out, int n)
{
    int max = 0;
    for (int i = 0; i < n; i++){
        max = max > abs(in[i]) ? max : abs(in[i]);
    }
    double vScale = 32767.0 / (double)max;
    for (int i = 0; i < n; i++)
    {
        out[i] = ((double)in[i]) * vScale;
    }
}

void sin_filter(short *in, short *out, int n)
{
    for (int i = 0; i < n; i++)
    {
        out[i] = round(256.0 * sin( (i*50.0/22400.0)));
    }
}

void histogram(short *in, short *out, int n)
{
    int hist[65536];
    for (int i = 0; i < n; i++)
    {
        out[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        hist[ 32768 + in[i] ] += 1;
    }
    for (int i = 0; i < 65536; i++)
    {
        out[i] = 32767.0 * ((float)hist[ i ] / (float)n);
    }
}


int main(int argc, char* argv[])
{

    FilterLibrary library;
    int i_filter = 0;

    std::string filename = "./resources/canary.wav";
    if (argc == 2)
    {
        filename = argv[1];
    }

    sf::SoundBuffer buffer1;
    if (!buffer1.loadFromFile( filename ))
        return 1;

    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile( filename ))
        return 1;

    RawSound buff_1( &buffer1 );
    RawSound buff_2( &buffer2 );

    short* dataS  = (short*)buff_1.data();
    short* data2  = (short*)buff_2.data();
    int nbSamples = buff_1.length();


    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(1280, 512), "Particles");

    // on crée un système de 1000 particules
//    ParticleSystem particles(1000);
    SoundSystem particles( &buff_1 );
    particles.update_ref( &buff_1 );
    particles.update_mod( &buff_2 );
//    ph_filter(dataS, dataS, nbSamples);

    // on crée un chrono pour mesurer le temps écoulé
    sf::Clock clock;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                    playS( &buff_2 );
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                    playS( &buff_1 );
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
//                    particles.zoom_out();
                i_filter  = (i_filter == 0) ? i_filter : i_filter - 1;
                library.getFilter( i_filter )->process(&buff_1, &buff_2);
                particles.update_mod(&buff_2);
                particles.update_fName( library.getFilter( i_filter )->Name() );

                std::stringstream tStream;
                int pTime = library.getFilter( i_filter )->getProcTime();
                tStream << "Processing time = " << pTime << " ms";
                window.setTitle( tStream.str() );

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
//                    particles.zoom_in();
                i_filter  = (i_filter == (library.size()-1)) ? i_filter : i_filter + 1;
                library.getFilter( i_filter )->process(&buff_1, &buff_2);
                particles.update_mod(&buff_2);
                particles.update_fName( library.getFilter( i_filter )->Name() );

                std::stringstream tStream;
                int pTime = library.getFilter( i_filter )->getProcTime();
                tStream << "Processing time = " << pTime << " ms";
                window.setTitle( tStream.str() );

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                particles.slide_left();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                particles.slide_right();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                buff_1.fill( &buff_2 );
                particles.update_ref( &buff_1 );
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                return EXIT_SUCCESS;
            }
        }

        // on le dessine
        window.clear();
        window.draw(particles);
        window.display();

        sf::Time t2 = sf::milliseconds(30);
        sf::sleep( t2 );
    }

    // Play a music
    //playMusic();

    // Wait until the user presses 'enter' key
//    std::cout << "Press enter to exit..." << std::endl;
//    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
