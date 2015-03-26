#ifndef __C_Copy__
#define __C_Copy__

#include "Filter.h"

class Copy : public Filter
{
public:
    Copy();
    virtual ~Copy();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
