#ifndef __C_Stereo2Mono_fx2__
#define __C_Stereo2Mono_fx2__

#include "../Filter.h"

class Stereo2Mono_fx2 : public Filter
{
public:
    Stereo2Mono_fx2();
    virtual ~Stereo2Mono_fx2();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
