#include "NoiseAWNG.h"

NoiseAWNG::NoiseAWNG() :
    Filter("NoiseAWNG")
{

}

NoiseAWNG::~NoiseAWNG(){
}

void NoiseAWNG::process(RawSound* _in, RawSound* _out){
    startTimer();

    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();
    for (int i = 0; i < n; i++)
    {
        if( rand()%2 ){
            out[i-1] = ((int)in[i] + rand()%511);
        }else{
            out[i-1] = ((int)in[i] - rand()%511);
        }
    }

    stopTimer();
}
