#ifndef __C_fEqualization__
#define __C_fEqualization__

#include "../Filter.h"

class fEqualization : public Filter
{
public:
    fEqualization();
    virtual ~fEqualization();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
