#ifndef __C_Modulation_1kHz__
#define __C_Modulation_1kHz__

#include "../Filter.h"

class Modulation_1kHz : public Filter
{
public:
    Modulation_1kHz();
    virtual ~Modulation_1kHz();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
