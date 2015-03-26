#ifndef __C_Denoise_Gaussian__
#define __C_Denoise_Gaussian__

#include "../Filter.h"

class Denoise_Gaussian : public Filter
{
public:
    Denoise_Gaussian();
    virtual ~Denoise_Gaussian();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
