#include "Stereo2Mono_fx2.h"

Stereo2Mono_fx2::Stereo2Mono_fx2() :
    Filter("Mono2Stereo fx2")
{

}

Stereo2Mono_fx2::~Stereo2Mono_fx2()
{

}

void Stereo2Mono_fx2::process(RawSound* _in, RawSound* _out){
    startTimer();

    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(
        _in->channels(),
        _in->length(),
        _in->sample_rate()
    );

    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    if( _in->channels() == 1 ){

        for (int i = 1; i < n; i++)
        {
            out[i-1] = ((int)in[i-1] + (int)in[i]) >> 1;
        }
        out[n-1] = 0;

    }else{

        for (int i = 2; i < n; i+=2)
        {
            out[i-2] = ((int)in[i-2] + (int)in[i  ]) >> 1;
            out[i-1] = ((int)in[i-1] + (int)in[i+1]) >> 1;
        }
        out[n-2] = 0;
        out[n-1] = 0;

    }

    stopTimer();
}
