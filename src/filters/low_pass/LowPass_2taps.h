#ifndef __C_LowPass_2taps__
#define __C_LowPass_2taps__

#include "../Filter.h"

class LowPass_2taps : public Filter
{
public:
    LowPass_2taps();
    virtual ~LowPass_2taps();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
