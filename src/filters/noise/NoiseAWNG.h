#ifndef __C_NoiseAWNG__
#define __C_NoiseAWNG__

#include "../Filter.h"

class NoiseAWNG : public Filter
{
public:
    NoiseAWNG();
    virtual ~NoiseAWNG();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
