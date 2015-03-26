#ifndef __C_Modulation_1kHz_lut__
#define __C_Modulation_1kHz_lut__

#include "../Filter.h"

class Modulation_1kHz_lut : public Filter
{
public:
    Modulation_1kHz_lut();
    virtual ~Modulation_1kHz_lut();

    virtual void process(RawSound *in, RawSound *out);

private:
        float* lut;

};
#endif
