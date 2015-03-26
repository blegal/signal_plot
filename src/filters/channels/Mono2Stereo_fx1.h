#ifndef __C_Mono2Stereo_fx1__
#define __C_Mono2Stereo_fx1__

#include "../Filter.h"

class Mono2Stereo_fx1 : public Filter
{
public:
    Mono2Stereo_fx1();
    virtual ~Mono2Stereo_fx1();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
