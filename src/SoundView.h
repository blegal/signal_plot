#ifndef __C_SOUNDVIEW__
#define __C_SOUNDVIEW__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "RawSound.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

class SoundView
{
public:
    SoundView( RawSound* buffer );
    ~SoundView();

    void setYOffset(int _offset);

    void update(RawSound *buffer);

    void update_plot();

    void update_plot(sf::VertexArray* m_vertices, RawSound *buffer, int yOffset);

    void zoom_in();

    void zoom_out();

    void slide_left();

    void slide_right();

    void update_fName(std::string _name);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    void plot_histo(int pStart, int limit, int yOffset);
    void plot_fft  (int pStart, int limit, int yOffset);

private:
    RawSound signal;
    sf::VertexArray m_vertices;

    // HISTOGRAM CHANNEL 1
    sf::VertexArray hl1_vertices;
    sf::VertexArray hl2_vertices;

    // HISTOGRAM CHANNEL 2
    sf::VertexArray hr1_vertices;
    sf::VertexArray hr2_vertices;

    // HISTOGRAM CHANNEL 1
    sf::VertexArray fftl1_vertices;
    sf::VertexArray fftl2_vertices;

    // HISTOGRAM CHANNEL 2
    sf::VertexArray fftr1_vertices;
    sf::VertexArray fftr2_vertices;

    std::string _fName;
    int m_zoom;
    int m_start;
    int yOffset;

    double* tabFFT;

};

#endif
