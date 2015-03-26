#ifndef __C_Stereo2Mono_fx1__
#define __C_Stereo2Mono_fx1__

#include "../Filter.h"

class Stereo2Mono_fx1 : public Filter
{
public:
    Stereo2Mono_fx1();
    virtual ~Stereo2Mono_fx1();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
