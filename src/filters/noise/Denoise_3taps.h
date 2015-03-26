#ifndef __C_Denoise_3taps__
#define __C_Denoise_3taps__

#include "../Filter.h"

class Denoise_3taps : public Filter
{
public:
    Denoise_3taps();
    virtual ~Denoise_3taps();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
