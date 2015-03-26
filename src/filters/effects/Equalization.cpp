#include "Equalization.h"

fEqualization::fEqualization() :
    Filter("Equalization")
{

}

fEqualization::~fEqualization()
{

}

void fEqualization::process(RawSound* _in, RawSound* _out){
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

        // FILTAGE SUR 1 CANAL
        int max = 0;
        for (int i = 0; i < n; i++){
            max = max > abs(in[i]) ? max : abs(in[i]);
        }
        double vScale = 32767.0 / (double)max;
        for (int i = 0; i < n; i++)
        {
            out[i] = ((double)in[i]) * vScale;
        }

    }else{

        // FILTAGE SUR 2 CANAUX
        int max[2] = {0, 0};
        for (int i = 0; i < n; i+=2){
            max[0] = max[0] > abs(in[i]) ? max[0] : abs(in[i]);
            max[1] = max[1] > abs(in[i]) ? max[1] : abs(in[i]);
        }
        double vScale_1 = 32767.0 / (double)max[0];
        double vScale_2 = 32767.0 / (double)max[1];
        for (int i = 0; i < n; i+=2)
        {
            out[i  ] = ((double)in[i  ]) * vScale_1;
            out[i+1] = ((double)in[i+1]) * vScale_2;
        }
    }

    stopTimer();
}
