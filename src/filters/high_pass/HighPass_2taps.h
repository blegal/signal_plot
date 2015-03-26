#ifndef __C_HighPass_2taps__
#define __C_HighPass_2taps__

#include "../Filter.h"

class HighPass_2taps : public Filter
{
public:
    HighPass_2taps();
    virtual ~HighPass_2taps();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
