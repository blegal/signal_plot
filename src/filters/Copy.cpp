#include "Copy.h"

Copy::Copy() :
    Filter("Copy")
{

}

Copy::~Copy()
{

}

void Copy::process(RawSound* _in, RawSound* _out){
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
    for (int i = 0; i < n; i++)
    {
        out[i-1] = ((int)in[i] + rand()%511);
    }

    stopTimer();
}
