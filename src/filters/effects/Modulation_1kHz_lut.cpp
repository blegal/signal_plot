#include "Modulation_1kHz_lut.h"

Modulation_1kHz_lut::Modulation_1kHz_lut() :
    Filter("Modulation (1kHz/LUT)")
{
    short fm = 1000; /* Frequence de modulation */
    int freq = 44100;
    lut = new float[1000];
    for (int t = 0; t < 1000; t++){
        lut[t] = cos(6.2832 * t * fm / freq);
//        printf("[%3d] = %f\n", t, lut[t]);
    }
}

Modulation_1kHz_lut::~Modulation_1kHz_lut()
{
    delete lut;
}

void Modulation_1kHz_lut::process(RawSound* _in, RawSound* _out){
    startTimer();

    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(
        _in->channels(),
        _in->length(),
        _in->sample_rate()
    );

    short fm   = 1000; /* Frequence de modulation */
    short t    = 0 ;
    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    int freq   = _in->sample_rate();

    if( _in->channels() == 1 ){
        for (int i = 0; i < n; i++){
            out[i]      = round( ((float)in[i]) * lut[t]);
            t = ( (t+1) >= fm ) ? 0 : (t+1);
        }
    }else{
        // FILTAGE SUR 2 CANAUX
        for (int i = 0; i < n; i+=2)
        {
            out[i  ] = (lut[t] * in[i  ]);
            out[i+1] = (lut[t] * in[i+1]);
            t = ( (t+1) >= fm ) ? 0 : (t+1);
        }
    }

    stopTimer();
}
