#include "Denoise_Gaussian.h"

Denoise_Gaussian::Denoise_Gaussian() :
    Filter("Denoise Gaussian")
{

}

Denoise_Gaussian::~Denoise_Gaussian(){
}

void Denoise_Gaussian::process(RawSound* _in, RawSound* _out){
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
        out[0]   = 0;
        for (int i = 1; i < n-1; i++)
        {
            out[i-1] = (((int)in[i-1] + (int)in[i] + (int)in[i+1]) / 3.0);
        }
        out[n-1] = 0;
    }else{
        // FILTAGE SUR 2 CANAUX
        for (int i = 2; i < n; i+=2)
        {
            out[i-2] = (((int)in[i-2] + (int)in[i  ] + (int)in[i+2]) / 3.0);
            out[i-3] = (((int)in[i-1] + (int)in[i+1] + (int)in[i+3]) / 3.0);
        }
        out[n-2] = 0;
        out[n-1] = 0;
    }

    stopTimer();
}
