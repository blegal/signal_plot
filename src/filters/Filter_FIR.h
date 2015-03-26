#ifndef __C_Filter_FIR__
#define __C_Filter_FIR__

#include "Filter.h"

class Filter_FIR : public Filter
{
public:
    Filter_FIR(int _nbTaps, float* coeffs, std::string _name);
    virtual ~Filter_FIR();
    virtual void process(RawSound *in, RawSound *out);

private:
	int    nbTaps;
	int    ech_index;
	float* ech_buffer;
	float* coe_buffer;

private:
	void  p_filter_x86(short* A, short* B, int N, float* H, int L);
	void  p_filter_sse(short* A, short* B, int N, float* H, int L);
	void  filter_init();
	float p_filter(float y);

};

#endif
