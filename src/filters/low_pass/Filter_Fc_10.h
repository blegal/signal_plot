#ifndef __C_Filter_Fc_10__
#define __C_Filter_Fc_10__

#include "../Filter.h"

class Filter_Fc_10 : public Filter
{
public:
    Filter_Fc_10();
    virtual ~Filter_Fc_10();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
