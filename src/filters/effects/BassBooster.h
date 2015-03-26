#ifndef __C_BassBooster__
#define __C_BassBooster__

#include "../Filter_FIR.h"

class BassBooster : public Filter_FIR
{
public:
    BassBooster();
    virtual ~BassBooster();

    virtual void process(RawSound *in, RawSound *out);

};

#endif
