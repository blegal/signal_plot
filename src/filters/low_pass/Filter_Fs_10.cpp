#include "Filter_Fs_10.h"

Filter_Fs_10::Filter_Fs_10() :
    Filter("Filter Fs/10")
{

}

Filter_Fs_10::~Filter_Fs_10()
{

}

#define N   45
float h[N] = 
{
  -1.839E-3,-2.657E-3,-1.437E-7, 3.154E-3, 2.595E-3,-4.159E-3,-1.540E-2, 
  -2.507E-2,-2.547E-2,-1.179E-2, 1.392E-2, 4.206E-2, 5.888E-2, 5.307E-2, 
   2.225E-2,-2.410E-2,-6.754E-2,-8.831E-2,-7.475E-2,-2.956E-2, 3.030E-2, 
   8.050E-2, 1.000E-1, 8.050E-2, 3.030E-2,-2.956E-2,-7.475E-2,-8.831E-2, 
  -6.754E-2,-2.410E-2, 2.225E-2, 5.307E-2, 5.888E-2, 4.206E-2, 1.392E-2, 
  -1.179E-2,-2.547E-2,-2.507E-2,-1.540E-2,-4.159E-3, 2.595E-3, 3.154E-3, 
  -1.437E-7,-2.657E-3,-1.839E-3
};

void Filter_Fs_10::process(RawSound* _in, RawSound* _out){
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
        for (int i = 0; i < n; i++)
        {
            int nb_taps = (i < N) ? (i+1) : N;
            float yn = 0.0;
            for(int z=0; z<nb_taps; z++){
                yn += (float)in[i-z] * h[z];
            }
            out[i] = yn;
        }

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

}
