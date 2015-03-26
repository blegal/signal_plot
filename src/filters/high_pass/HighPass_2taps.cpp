#include "HighPass_2taps.h"

HighPass_2taps::HighPass_2taps() :
    Filter("HighPass 2taps")
{

}

HighPass_2taps::~HighPass_2taps()
{

}

void HighPass_2taps::process(RawSound* _in, RawSound* _out){
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
            out[i-1] = in[i-1] - in[i];
        }
        out[n-1] = 0;

    }else{

        for (int i = 2; i < n; i+=2)
        {
            out[i-2] = in[i-2] - in[i  ];
            out[i-1] = in[i-1] - in[i+1];
        }
        out[n-2] = 0;
        out[n-1] = 0;

    }

    stopTimer();
}
