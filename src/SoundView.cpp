#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "SoundView.h"

#define wSIGNAL 1024
#define wFFT    256

#define PI      M_PI    /* pi to machine precision, defined in math.h */
#define TWOPI   (2.0*PI)

/*
 FFT/IFFT routine. (see pages 507-508 of Numerical Recipes in C)
    
 Inputs:
    data[] : array of complex* data points of size 2*NFFT+1.
        data[0] is unused,
        * the n'th complex number x(n), for 0 <= n <= length(x)-1, is stored as:
            data[2*n+1] = real(x(n))
            data[2*n+2] = imag(x(n))
        if length(Nx) < NFFT, the remainder of the array must be padded with zeros

    nn : FFT order NFFT. This MUST be a power of 2 and >= length(x).
    isign:  if set to 1, 
                computes the forward FFT
            if set to -1, 
                computes Inverse FFT - in this case the output values have
                to be manually normalized by multiplying with 1/NFFT.
 Outputs:
    data[] : The FFT or IFFT results are stored in data, overwriting the input.
*/

void four1(double data[], int nn, int isign)
{
    int n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
            tempr = data[j];     data[j] = data[i];     data[i] = tempr;
            tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
        }
        m = n >> 1;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }

    mmax = 2;

    while (n > mmax) {
        istep = 2*mmax;
        theta = TWOPI/(isign*mmax);
        wtemp = sin(0.5*theta);
        wpr   = -2.0*wtemp*wtemp;
        wpi   = sin(theta);
        wr    = 1.0;
        wi    = 0.0;
        for (m = 1; m < mmax; m += 2) {
            for (i = m; i <= n; i += istep) {
                j =i + mmax;
                tempr      = wr*data[j]   - wi*data[j+1];
                tempi      = wr*data[j+1] + wi*data[j];
                data[j]    = data[i]   - tempr;
                data[j+1]  = data[i+1] - tempi;
                data[i]   += tempr;
                data[i+1] += tempi;
            }
            wr = (wtemp = wr)*wpr - wi*wpi + wr;
            wi = wi*wpr + wtemp*wpi + wi;
        }
        mmax = istep;
    }
}


void fft_process(short* data, double* freq, int Nx, int nb_Channels)
{
    int i;
    int NFFT;
    double *x;
    double *X;

    /* calculate NFFT as the next higher power of 2 >= Nx */
    NFFT = (int)pow(2.0, ceil(log((double)Nx)/log(2.0)));

    /* allocate memory for NFFT complex numbers (note the +1) */
    X = (double *) malloc((2*NFFT+1) * sizeof(double));

    /* Storing x(n) in a complex array to make it work with four1. 
    This is needed even though x(n) is purely real in this case. */
    for(i=0; i<Nx; i++)
    {
        X[2*i+1] = data[nb_Channels * i]; // GESTION DU MULTI-CHANNEL DANS LE SIGNAL D'ENTREE
        X[2*i+2] = 0.0;
    }
    /* pad the remainder of the array with zeros (0 + 0 j) */
    for(i=Nx; i<NFFT; i++)
    {
        X[2 * i + 1] = 0.0;
        X[2 * i + 2] = 0.0;
    }

    /* calculate FFT */
    four1(X, NFFT, 1);

    //
    // http://www.originlab.com/www/helponline/Origin/en/UserGuide/Algorithm_%28FFT1%29.html
    //
//    float dBMax = -200.0;
    float puissance = sqrt(32768.0 * 32768.0 / 4.0);
    for(i=0; i<NFFT; i++)
    {
        float magnitude = sqrt( (float)X[2*i+1] * (float)X[2*i+1] + (float)X[2*i+2] * (float)X[2*i+2] );
        float amplitude = 1.0f * magnitude / NFFT;  //10.0 * log10(modulec/(NFFT * NFFT));
        float dB        = 20.f * log10(amplitude / puissance); //10.0 * log10(modulec/(NFFT * NFFT));
        freq[i]         = dB + 100;
    }
}

SoundView::SoundView( RawSound* buffer ) :
        m_vertices(sf::Points, buffer->length()),
        hl1_vertices(sf::Lines,  512),
        hl2_vertices(sf::Points, 256),
        hr1_vertices(sf::Lines,  512),
        hr2_vertices(sf::Points, 256),

        fftl1_vertices(sf::Lines,  4096),
        fftl2_vertices(sf::Points, 2048),
        fftr1_vertices(sf::Lines,  4096),
        fftr2_vertices(sf::Points, 2048),
        
        m_zoom ( 1 ),
        m_start( 0 ),
        signal( buffer ),
        _fName( "None" )
{
    m_zoom = buffer->sample_rate() / wSIGNAL; // POUR AVOIR UNE SECONDE A L'ECRAN
}

SoundView::~SoundView( )
{

}

void SoundView::plot_fft(int pStart, int limit, int yOffset)
{
    short* ptr = signal.data();
    int nb_Channels = signal.channels();

    const int FFTsize = 4096;
    tabFFT = new double[FFTsize];

    for(int z=0; z<nb_Channels; z++){

        fft_process( &ptr[pStart + z], tabFFT, FFTsize, nb_Channels );

        // NORMALISATION DES VALEURS DE L'HISTOGRAMME
        float maxf = 0.0;
        for (std::size_t i = 0; i < FFTsize; ++i)
        {
            maxf = maxf > tabFFT[i] ? maxf : tabFFT[i];
        }

        sf::VertexArray* f1_vertices = ( z == 0 ) ? &fftl1_vertices: &fftr1_vertices;
        sf::VertexArray* f2_vertices = ( z == 0 ) ? &fftl2_vertices: &fftr2_vertices;
        sf::Color sColor             = ( z == 0 ) ? sf::Color::Red: sf::Color::Blue;
        float scaleH = 114.0 / maxf;
        float scaleW = ((float)wFFT/(float)(FFTsize/2));

        for (std::size_t i = 0; i < FFTsize/2; ++i)
        {
            float posX = wSIGNAL + i * scaleW;
            float prob = (scaleH * tabFFT[i]);
            float posY = (256 + yOffset) - prob;
            (*f1_vertices)[2*i  ].position = sf::Vector2f(posX, (256 + yOffset));
            (*f1_vertices)[2*i  ].color    = sColor;
            (*f1_vertices)[2*i  ].color.a  = static_cast<sf::Uint8>(64);
            (*f1_vertices)[2*i+1].position = sf::Vector2f(posX, posY);
            (*f1_vertices)[2*i+1].color    = sColor;
            (*f1_vertices)[2*i+1].color.a  = static_cast<sf::Uint8>(64);
            (*f2_vertices)[i    ].position = sf::Vector2f(posX, posY);
            (*f2_vertices)[i    ].color    = sColor;
            (*f2_vertices)[i    ].color.a  = static_cast<sf::Uint8>(255);
        }
    }

    delete tabFFT;
}

class TemporalHistogram
{
public:
    TemporalHistogram( RawSound* buffer, int start, int stop ){
        tabHistoL = new int[256];
        tabHistoR = new int[256];
        for (std::size_t i = 0; i < 256; i++)
        {
            tabHistoL[i] = 0;
            tabHistoR[i] = 0;
        }
        short* ptr = buffer->data();
        int nCh    = buffer->channels();

        for (std::size_t i = start; i < stop; i+=1)
        {
            int amp    = ((int)ptr[i]) + 32768;
            int pos    = (amp / 256);
            if( (nCh == 1) || ((i & 0x01) == 0) ){
                tabHistoL[pos] += 1;
            }else{
                tabHistoR[pos] += 1;
            }
        }

        maxf = 0.0;
        for (std::size_t i = 0; i < 256; ++i)
        {
            maxf = maxf > tabHistoL[i] ? maxf : tabHistoL[i];
            maxf = maxf > tabHistoR[i] ? maxf : tabHistoR[i];
        }

    }

    ~TemporalHistogram(){
        delete tabHistoL;
        delete tabHistoR;
    }

public:
    int* tabHistoL;
    int* tabHistoR;
    float maxf;
};

void SoundView::plot_histo(int pStart, int limit, int yOffset)
{
    short* ptr      = signal.data();
    int nb_Channels = signal.channels();

    TemporalHistogram histo(&signal, pStart, pStart+limit);

    float scaleH = 114.0 / histo.maxf;
    for (std::size_t i = 0; i < 256; ++i)
    {
        float prob = (scaleH * histo.tabHistoL[i]);
        float posY = (256 + yOffset) - prob;
        hl1_vertices[2*i  ].position = sf::Vector2f(wSIGNAL + i, (256 + yOffset));
        hl1_vertices[2*i  ].color    = sf::Color::Red;
        hl1_vertices[2*i  ].color.a  = static_cast<sf::Uint8>(128);
        hl1_vertices[2*i+1].position = sf::Vector2f(wSIGNAL + i, posY);
        hl1_vertices[2*i+1].color    = sf::Color::Red;
        hl1_vertices[2*i+1].color.a  = static_cast<sf::Uint8>(128);
        hl2_vertices[i    ].position = sf::Vector2f(wSIGNAL + i, posY);
        hl2_vertices[i    ].color    = sf::Color::Red;
        hl2_vertices[i    ].color.a  = static_cast<sf::Uint8>(255);
    }

    if( nb_Channels == 2 )
    for (std::size_t i = 0; i < 256; ++i)
    {
        float prob = (scaleH * histo.tabHistoR[i]);
        float posY = (256 + yOffset) - prob;
        hr1_vertices[2*i  ].position = sf::Vector2f(wSIGNAL + i, (256 + yOffset));
        hr1_vertices[2*i  ].color    = sf::Color::Blue;
        hr1_vertices[2*i  ].color.a  = static_cast<sf::Uint8>(128);
        hr1_vertices[2*i+1].position = sf::Vector2f(wSIGNAL + i, posY);
        hr1_vertices[2*i+1].color    = sf::Color::Blue;
        hr1_vertices[2*i+1].color.a  = static_cast<sf::Uint8>(128);
        hr2_vertices[i    ].position = sf::Vector2f(wSIGNAL + i, posY);
        hr2_vertices[i    ].color    = sf::Color::Blue;
        hr2_vertices[i    ].color.a  = static_cast<sf::Uint8>(255);
    }
}


void SoundView::update_plot(sf::VertexArray* m_vertices, RawSound *buffer, int yOffset)
    {
        unsigned int count       = buffer->length();
        unsigned int nb_Channels = buffer->channels();
        int pStart = nb_Channels * m_zoom * m_start;          // Premier point dans la waveform
        int pStop  = nb_Channels * m_zoom * (m_start + wSIGNAL); // Dernier point dans la waveform
//        printf("(DD) RawSound length = %d\n", buffer->length());
//        printf("(DD) [pStart, pStop] = [%d, %d]\n", pStart, pStop);

        if( pStop > count ){
            pStop  = count;
            pStart = pStop - (m_zoom * (m_start + wSIGNAL));
            pStart = (pStart < 0) ? 0 : pStart;
        }
//        printf("(DD) [pStart, pStop] = [%d, %d]\n", pStart, pStop);

        unsigned int limit  = pStop - pStart;   // Nombre de point a tracer

//        printf("(DD) [limit] = [%d]\n", limit);
        m_vertices->resize( limit );
        unsigned int xScale = m_zoom;
        int yMax = 0;

        short* ptr = buffer->data();

        plot_histo(pStart, limit, yOffset-128);
        plot_fft  (pStart, limit, yOffset);

        //
        // ON TRACE LE SIGNAL TEMPOREL
        //
        double yScale = 32667.0 / 128;
        for (std::size_t i = 0; i < limit; i++)
        {
            int posX = (i/xScale/nb_Channels);
            int posY = ((double)ptr[i+pStart])/yScale + 128 + yOffset;
            sf::Vector2f pos(posX, posY);
            (*m_vertices)[i].position = pos;

            if( (i%2 == 0) | (nb_Channels == 1) ){
                (*m_vertices)[i].color = sf::Color::Red;
            }else{
                (*m_vertices)[i].color = sf::Color::Blue;
            }
        }
    }



void SoundView::setYOffset(int _offset)
{
    yOffset = _offset;
}


void SoundView::update(RawSound *buffer)
{
    signal.fill( buffer );
    update_plot();
}


void SoundView::update_plot()
{
    update_plot(&m_vertices, &signal, yOffset);
}


void SoundView::zoom_in()
{
    if( m_zoom != 1 ){
       m_zoom -= 1;
    }
    update_plot();
}


void SoundView::zoom_out()
{
    m_zoom += 1;
    if( (signal.length()/(1024*m_zoom)) == 0 ){
        m_zoom -= 1;
    }
    update_plot();
}


void SoundView::slide_left()
{
    m_start -= 1024;
    if( m_start < 0 ){
        m_start = 0;
    }
    update_plot();
}


void SoundView::slide_right()
{
    m_start += 1024;
    unsigned int count  = signal.length();
    if( m_start > (signal.length()-1024) ){
        m_start = signal.length() - 1024;
    }
    update_plot();
}


void SoundView::update_fName(std::string _name)
{
    _fName = _name;
}


void SoundView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //
    // on dessine enfin le vertex array
    //
    for(int i = 1; i < 10; i++){
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(      0, yOffset + (256.0/10.0)*i)),
            sf::Vertex(sf::Vector2f(wSIGNAL, yOffset + (256.0/10.0)*i))
        };
        line[0].color.a = static_cast<sf::Uint8>(64);
        line[1].color.a = static_cast<sf::Uint8>(64);
        target.draw(line, 2, sf::Lines);
    }
    target.draw(m_vertices,  states);

    //
    // ON DESSINE LES HISTOGRAMMES
    //
    for(int i = 1; i < 10; i++){
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(wSIGNAL,      yOffset + (128.0/10.0)*i)),
            sf::Vertex(sf::Vector2f(wSIGNAL+wFFT, yOffset + (128.0/10.0)*i))
        };
        line[0].color.a = static_cast<sf::Uint8>(64);
        line[1].color.a = static_cast<sf::Uint8>(64);
        target.draw(line, 2, sf::Lines);
    }

    target.draw(hl1_vertices, states);
    target.draw(hl2_vertices, states);

    if( signal.channels() == 2 ){
        target.draw(hr1_vertices, states);
        target.draw(hr2_vertices, states);
    }

    //
    // ON DESSINE LES FFTs
    //
    for(int i = 1; i < 10; i++){
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(wSIGNAL,      yOffset + 128.0 + (128.0/10.0)*i)),
            sf::Vertex(sf::Vector2f(wSIGNAL+wFFT, yOffset + 128.0 + (128.0/10.0)*i))
        };
        line[0].color.a = static_cast<sf::Uint8>(64);
        line[1].color.a = static_cast<sf::Uint8>(64);
        target.draw(line, 2, sf::Lines);
    }

    target.draw(fftl1_vertices, states);
    target.draw(fftl2_vertices, states);

    if( signal.channels() == 2 ){
        target.draw(fftr1_vertices, states);
        target.draw(fftr2_vertices, states);
    }

    //
    // ON DESSINE LE CADRE DES DIFFERENTES VUES
    //
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(0,            yOffset + 128)),
        sf::Vertex(sf::Vector2f(wSIGNAL+wFFT, yOffset + 128)),
        sf::Vertex(sf::Vector2f(wSIGNAL, yOffset + 0)  ),
        sf::Vertex(sf::Vector2f(wSIGNAL, yOffset + 256))

    };
    target.draw(line, 4, sf::Lines);

    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
        exit( 1 );

    std::stringstream tStream;
    int ref_nb_samples  = signal.length();
    int ref_sample_rate = signal.sample_rate();
    int ref_channels    = signal.channels();
    tStream << "[SAMPLES=" << ref_nb_samples << ", S/R=" << ref_sample_rate << ", CHANNELS=" << ref_channels << "]";
    sf::Text infos;
    infos.setFont(font);
    infos.setCharacterSize(14);
    infos.setPosition(0.f, yOffset);
    infos.setColor(sf::Color::White);
    infos.setString( tStream.str() );
    target.draw(infos);
}
