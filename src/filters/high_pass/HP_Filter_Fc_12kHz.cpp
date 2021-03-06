#include "HP_Filter_Fc_12kHz.h"

#define N	51
static float hp_51_taps_fc_12kHz_44800[N] = 
{
   -0.001018,  -0.000000,  +0.001306,  -0.000000,  -0.002073,  -0.000000,  +0.003426,  -0.000000,  
   -0.005491,  -0.000000,  +0.008434,  -0.000000,  -0.012503,  -0.000000,  +0.018103,  -0.000000,  
   -0.026000,  -0.000000,  +0.037851,  -0.000000,  -0.058012,  -0.000000,  +0.102575,  -0.000000,  
   -0.316844,  +0.499510,  -0.316844,  -0.000000,  +0.102575,  -0.000000,  -0.058012,  -0.000000,  
   +0.037851,  -0.000000,  -0.026000,  -0.000000,  +0.018103,  -0.000000,  -0.012503,  -0.000000,  
   +0.008434,  -0.000000,  -0.005491,  -0.000000,  +0.003426,  -0.000000,  -0.002073,  -0.000000,  
   +0.001306,  -0.000000,  -0.001018
};


HP_Filter_Fc_12kHz::HP_Filter_Fc_12kHz() : Filter_FIR(N, hp_51_taps_fc_12kHz_44800, "High-Pass (Fc=12kHz, FIR)")
{

}

HP_Filter_Fc_12kHz::~HP_Filter_Fc_12kHz()
{

}

