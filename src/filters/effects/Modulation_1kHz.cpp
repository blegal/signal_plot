#include "Modulation_1kHz.h"

Modulation_1kHz::Modulation_1kHz() :
    Filter("Modulation (1kHz)")
{

}

Modulation_1kHz::~Modulation_1kHz()
{

}

void Modulation_1kHz::process(RawSound* _in, RawSound* _out){
    startTimer();

    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(
        _in->channels(),
        _in->length(),
        _in->sample_rate()
    );
    short fm = 1000; /* Frequence de modulation */
    short t  = 0 ;

    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    int freq   = _in->sample_rate();

    if( _in->channels() == 1 ){
        for (int i = 0; i < n; i++){
            float value = ((float)in[i] * cos(6.2832 * t * fm / freq));
            out[i]      = (short)value;
            t = ( (t+1) >= freq ) ? 0 : (t+1);
        }
    }else{
        // FILTAGE SUR 2 CANAUX
        for (int i = 0; i < n; i+=2)
        {
            float coeff = cos(6.2832 * t * fm / freq);
            out[i  ] = (coeff * in[i  ]);
            out[i+1] = (coeff * in[i+1]);
            t = ( (t+1) >= freq ) ? 0 : (t+1);
        }
    }

    stopTimer();
}
