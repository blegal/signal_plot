#include "Filter_Fc_2kHz.h"

#define N   51
static float h_fc_2kHz_44800[N] = 
{
    0.0003,   -0.0000,   -0.0003,   -0.0008,   -0.0015,   -0.0023,   -0.0033,   -0.0043,   -0.0053,   -0.0059,
   -0.0059,   -0.0051,   -0.0032,    0.0000,    0.0047,    0.0108,    0.0183,    0.0270,    0.0365,    0.0463,
    0.0559,    0.0647,    0.0723,    0.0781,    0.0818,    0.0830,    0.0818,    0.0781,    0.0723,    0.0647,
    0.0559,    0.0463,    0.0365,    0.0270,    0.0183,    0.0108,    0.0047,    0.0000,   -0.0032,   -0.0051,
   -0.0059,   -0.0059,   -0.0053,   -0.0043,   -0.0033,   -0.0023,   -0.0015,   -0.0008,   -0.0003,   -0.0000,
    0.0003
};


Filter_Fc_2kHz::Filter_Fc_2kHz() :
    Filter_FIR(N, h_fc_2kHz_44800, "FIR (Fc=2kHz)")
{

}

Filter_Fc_2kHz::~Filter_Fc_2kHz()
{

}

