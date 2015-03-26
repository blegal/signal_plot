#ifndef __C_Echo_500ms__
#define __C_Echo_500ms__

#include "../Filter.h"

class Echo_500ms : public Filter
{
public:
    Echo_500ms();
    virtual ~Echo_500ms();

    virtual void process(RawSound *in, RawSound *out);
};

#endif
