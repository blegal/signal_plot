#include "Mono2Stereo_fx2.h"

Mono2Stereo_fx2::Mono2Stereo_fx2() :
    Filter("Mono2Stereo fx2")
{

}

Mono2Stereo_fx2::~Mono2Stereo_fx2(){
}

void Mono2Stereo_fx2::process(RawSound* _in, RawSound* _out){
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

    // ON RECOPIE UN CANAL
    for (int i = 0; i < n; i++)
    {
        out[2*i] = in[i];
    }

    // ON DECALE LE SECOND CANAL DE 20ms
    int delay = (int)(0.020 * _in->sample_rate()); // 20ms delay
    for (int i = 0; i < delay; i++)
    {
        out[2*i+1] = 0;
    }
    for (int i = delay; i < n; i++)
    {
        out[2*i+1] = in[i-delay];
    }

    stopTimer();
}
