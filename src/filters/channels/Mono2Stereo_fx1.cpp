#include "Mono2Stereo_fx1.h"

Mono2Stereo_fx1::Mono2Stereo_fx1() :
    Filter("Mono2Stereo fx1")
{

}

Mono2Stereo_fx1::~Mono2Stereo_fx1()
{

}

void Mono2Stereo_fx1::process(RawSound* _in, RawSound* _out){
    startTimer();

    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(
        2,
        2 * _in->length(),
        _in->sample_rate()
    );

    // ON VERIFIE QUE LE SIGNAL D'ENTREE EST BIEN MONO...
    if( _in->channels() == 2 )
    {
        short* in  = _in->data();
        short* out = _out->data();
        int n      = _in->length();
        for (int i = 0; i < n; i++)
        {
            out[i] = in[i];
        }
        return;
    }

    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();

    for (int i = 0; i < n; i++)
    {
        out[2*i  ] = in[i];
        out[2*i+1] = in[i];
    }

    stopTimer();
}
