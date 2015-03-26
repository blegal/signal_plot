#include "Filter_Fc_12kHz.h"

#define N 51
static float h_fc_12kHz_44800[N] = 
{
  0.0010, -0.0000, -0.0013,  0.0000,  0.0021, -0.0000, -0.0034,  0.0000,  0.0055, -0.0000,
 -0.0084,  0.0000,  0.0125, -0.0000, -0.0181,  0.0000,  0.0260, -0.0000, -0.0379,  0.0000,
  0.0580, -0.0000, -0.1026,  0.0000,  0.3168,  0.4995,  0.3168,  0.0000, -0.1026, -0.0000,
  0.0580,  0.0000, -0.0379, -0.0000,  0.0260,  0.0000, -0.0181, -0.0000,  0.0125,  0.0000,
 -0.0084, -0.0000,  0.0055,  0.0000, -0.0034, -0.0000,  0.0021,  0.0000, -0.0013, -0.0000,
  0.0010
};


Filter_Fc_12kHz::Filter_Fc_12kHz() : Filter_FIR(N, h_fc_12kHz_44800, "FIR (Fc=12kHz)")
{

}

Filter_Fc_12kHz::~Filter_Fc_12kHz()
{

}
