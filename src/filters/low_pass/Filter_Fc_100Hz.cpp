#include "Filter_Fc_100Hz.h"

#define N 201
static float h_fc_100Hz_44800[N] =
{
   +0.000572,  +0.000577,  +0.000586,  +0.000598,  +0.000613,  +0.000632,  +0.000654,  +0.000680,  
   +0.000709,  +0.000742,  +0.000778,  +0.000819,  +0.000862,  +0.000910,  +0.000961,  +0.001016,  
   +0.001074,  +0.001136,  +0.001202,  +0.001271,  +0.001344,  +0.001421,  +0.001501,  +0.001584,  
   +0.001671,  +0.001761,  +0.001855,  +0.001951,  +0.002051,  +0.002154,  +0.002261,  +0.002370,  
   +0.002482,  +0.002596,  +0.002714,  +0.002834,  +0.002956,  +0.003081,  +0.003208,  +0.003337,  
   +0.003469,  +0.003602,  +0.003737,  +0.003873,  +0.004011,  +0.004151,  +0.004291,  +0.004433,  
   +0.004576,  +0.004719,  +0.004864,  +0.005008,  +0.005153,  +0.005299,  +0.005444,  +0.005589,  
   +0.005734,  +0.005878,  +0.006022,  +0.006166,  +0.006308,  +0.006449,  +0.006589,  +0.006728,  
   +0.006865,  +0.007000,  +0.007134,  +0.007266,  +0.007395,  +0.007522,  +0.007647,  +0.007769,  
   +0.007889,  +0.008006,  +0.008119,  +0.008230,  +0.008337,  +0.008441,  +0.008542,  +0.008639,  
   +0.008732,  +0.008822,  +0.008907,  +0.008989,  +0.009066,  +0.009139,  +0.009208,  +0.009272,  
   +0.009332,  +0.009388,  +0.009438,  +0.009485,  +0.009526,  +0.009563,  +0.009595,  +0.009622,  
   +0.009644,  +0.009661,  +0.009674,  +0.009681,  +0.009683,  +0.009681,  +0.009674,  +0.009661,  
   +0.009644,  +0.009622,  +0.009595,  +0.009563,  +0.009526,  +0.009485,  +0.009438,  +0.009388,  
   +0.009332,  +0.009272,  +0.009208,  +0.009139,  +0.009066,  +0.008989,  +0.008907,  +0.008822,  
   +0.008732,  +0.008639,  +0.008542,  +0.008441,  +0.008337,  +0.008230,  +0.008119,  +0.008006,  
   +0.007889,  +0.007769,  +0.007647,  +0.007522,  +0.007395,  +0.007266,  +0.007134,  +0.007000,  
   +0.006865,  +0.006728,  +0.006589,  +0.006449,  +0.006308,  +0.006166,  +0.006022,  +0.005878,  
   +0.005734,  +0.005589,  +0.005444,  +0.005299,  +0.005153,  +0.005008,  +0.004864,  +0.004719,  
   +0.004576,  +0.004433,  +0.004291,  +0.004151,  +0.004011,  +0.003873,  +0.003737,  +0.003602,  
   +0.003469,  +0.003337,  +0.003208,  +0.003081,  +0.002956,  +0.002834,  +0.002714,  +0.002596,  
   +0.002482,  +0.002370,  +0.002261,  +0.002154,  +0.002051,  +0.001951,  +0.001855,  +0.001761,  
   +0.001671,  +0.001584,  +0.001501,  +0.001421,  +0.001344,  +0.001271,  +0.001202,  +0.001136,  
   +0.001074,  +0.001016,  +0.000961,  +0.000910,  +0.000862,  +0.000819,  +0.000778,  +0.000742,  
   +0.000709,  +0.000680,  +0.000654,  +0.000632,  +0.000613,  +0.000598,  +0.000586,  +0.000577,  
   +0.000572
};


Filter_Fc_100Hz::Filter_Fc_100Hz() :
    Filter_FIR(N, h_fc_100Hz_44800, "FIR (Fc=100Hz)")
{

}


Filter_Fc_100Hz::~Filter_Fc_100Hz()
{

}

