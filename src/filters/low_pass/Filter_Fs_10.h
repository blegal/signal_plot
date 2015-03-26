#ifndef __C_Filter_Fs_10__
#define __C_Filter_Fs_10__

#include "../Filter.h"

class Filter_Fs_10 : public Filter
{
public:
    Filter_Fs_10();
    virtual ~Filter_Fs_10();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
