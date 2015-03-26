#include "Echo_500ms.h"

Echo_500ms::Echo_500ms() :
    Filter("Echo 500ms")
{

}

Echo_500ms::~Echo_500ms()
{

}

void Echo_500ms::process(RawSound* _in, RawSound* _out)
{
    startTimer();

    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(
        _in->channels(),
        _in->length(),
        _in->sample_rate()
    );

    // ON DECALE LE SECOND CANAL DE 20ms
    int delay  = (int)(0.500 * _in->sample_rate()); // 20ms delay
    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();

    if( _in->channels() == 1 )
    {

        for (int i = 0; i < delay; i++)
        {
            out[i] = (0.8f * in[i]);
        }
        for (int i = delay; i < n; i++)
        {
            out[i] = (0.8f * in[i] + 0.2f * in[i-delay]);
        }

    }else{

        for (int i = 0; i < 2*delay; i+=2)
        {
            out[i  ] = (0.8f * in[i  ]);
            out[i+1] = (0.8f * in[i+1]);
        }
        for (int i = 2*delay; i < n; i+=2)
        {
            out[i  ] = (0.8f * in[i  ] + 0.2f * in[i-delay  ]);
            out[i+1] = (0.8f * in[i+1] + 0.2f * in[i-delay+1]);
        }
    }

    stopTimer();
}
