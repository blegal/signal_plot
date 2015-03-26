#ifndef __C_Mono2Stereo_fx2__
#define __C_Mono2Stereo_fx2__

#include "../Filter.h"

class Mono2Stereo_fx2 : public Filter
{
public:
    Mono2Stereo_fx2();
    virtual ~Mono2Stereo_fx2();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
