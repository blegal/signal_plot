#ifndef __C_RAWSOUND__
#define __C_RAWSOUND__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iomanip>
#include <iostream>
#include <math.h>

class RawSound
{
private:
    short* buffer;
    unsigned int _length;
    unsigned int _channels;
    unsigned int _rate_per_second;

public:
    RawSound();

    RawSound(RawSound* _ptr);

    RawSound(sf::SoundBuffer* _sb);

    ~RawSound();

    short* data();

    unsigned int channels() const;

    unsigned int length() const;

    unsigned int sample_rate() const;

    void fill(RawSound* _ptr);

    void transform(unsigned int pchannels, unsigned int plength, unsigned int psample_rate);
};

#endif
