#include "Filter_FIR.h"

Filter_FIR::Filter_FIR(int _nbTaps, float* coeffs, std::string _name) :
    Filter( _name )
{
    nbTaps     = _nbTaps;
    ech_buffer = new float[nbTaps];
    coe_buffer = new float[nbTaps];
    for(int p=0; p<nbTaps; p++){
       coe_buffer[p] = coeffs[p];
    }
}

Filter_FIR::~Filter_FIR()
{
    delete ech_buffer;
    delete coe_buffer;
}

void Filter_FIR::filter_init() {
    for(int z=0; z<nbTaps; z++){
        ech_buffer[z] = 0.f;
    }
    ech_index = 0;
}

float Filter_FIR::p_filter(float y) {
    ech_buffer[ech_index] = y;
    float r = 0.0;
    for(int z=0; z<nbTaps; z++){
        int e_pos = (z + ech_index) % nbTaps;
        r += ech_buffer[e_pos] * coe_buffer[z];
    }
    ech_index = (ech_index + 1) % nbTaps;
    return r;
}

void Filter_FIR::p_filter_x86(short* A, short* B, int N, float* H, int L) {

    // ON FAIT LE CALCUL DE [0...N-fir_length]
    for(int z=0; z<N-L; z++){
        float y = 0.0;
        for(int t=0; t<nbTaps; t++){
            y += A[z+t] * H[t];
        }
        B[z] = y;
    }

    // ON FAIT LE FILL AVEC DES 0.0 DE [N-fir_length, N]
    for(int z=N-L; z<N; z++){
        B[z] = 0.0;
    }
}

#include <xmmintrin.h>

#define SSE_16S_LOAD(ptr)            (_mm_load_si128(ptr))
#define SSE_16S_uLOAD(ptr)           (_mm_loadu_si128(ptr))
#define SSE_16S_STORE(ptr,v)         (_mm_store_si128(ptr,v))
#define SSE_32F_SET1(ptr)            (_mm_load_ps1(ptr))
#define SSE_32F_ADD(a,b)             (_mm_add_ps(a,b))
#define SSE_32F_MUL(a,b)             (_mm_mul_ps(a,b))
#define SSE_S16b_UNPACK_HIGH(a)      (_mm_unpackhi_epi16(a,_mm_setzero_si128()))
#define SSE_S16b_UNPACK_LOW(a)       (_mm_unpacklo_epi16(a,_mm_setzero_si128()))
#define SSE_8S_PACK(hi,lo)           (_mm_packs_epi32(lo,hi))

void Filter_FIR::p_filter_sse(short* A, short* B, int N, float* H, int L) {

    // ON CALCULE LES TAILLES QUI VONT BIEN...
    int nEch_S_1 = (N-L);
    int nEch_S_8 = nEch_S_1/8;

    // ON FAIT LE CALCUL DE [0...N-fir_length]
    __m128i* i_ptr = (__m128i*)A;
    __m128i* o_ptr = (__m128i*)B;
    for(int z=0; z<nEch_S_8; z++){
        __m128 ylo = _mm_setzero_ps();
        __m128 yhi = _mm_setzero_ps();
        for(int t=0; t<nbTaps; t++){
            __m128i coe = SSE_32F_SET1(&H[t]);
            float *data = ((float*)i_ptr) + t;
            __m128i val = SSE_16S_uLOAD( (__m128i*)data );
            __m128i xlo = SSE_S16b_UNPACK_LOW (val);
            __m128i xhi = SSE_S16b_UNPACK_HIGH(val);
            xlo = _mm_srai_epi32(_mm_slli_epi32(xlo, 16), 16);
            xhi = _mm_srai_epi32(_mm_slli_epi32(xhi, 16), 16);
            ylo = SSE_32F_ADD(ylo, SSE_32F_MUL(_mm_cvtepi32_ps(xlo), coe));
            yhi = SSE_32F_ADD(yhi, SSE_32F_MUL(_mm_cvtepi32_ps(xhi), coe));
        }
        ylo = _mm_cvtps_epi32(ylo); // ON CONVERTIT EN ENTIER
        yhi = _mm_cvtps_epi32(yhi); // ON CONVERTIT EN ENTIER
        __m128 res = SSE_8S_PACK(yhi,ylo);
        SSE_16S_STORE(o_ptr,res);
         i_ptr++; o_ptr++;
    }

    // ON FAIT LE FILL AVEC DES 0.0 DE [N-fir_length, N]
    for(int z=8*nEch_S_8; z<nEch_S_1; z++){
        B[z] = 0.0;
    }
    for(int z=nEch_S_1; z<N; z++){
        B[z] = 0.0;
    }
}


void Filter_FIR::process(RawSound* _in, RawSound* _out) {
   startTimer();

    // ON ADAPATE LA SORTIE A LA TRANSFORMATION A REALISER
    _out->transform(
        _in->channels(),
        _in->length(),
        _in->sample_rate()
    );

    short* in  = _in->data();
    short* out = _out->data();
    int n      = _in->length();

    if( _in->channels() == 1 ){

        //
        // FILTAGE SUR 1 CANAL
        //
        p_filter_sse( in, out, n, coe_buffer, nbTaps );

    }else{

        // FILTAGE SUR 2 CANAUX
        filter_init();
        for (int i = 0; i < n; i+=2)
        {
            out[i] = p_filter( in[i] );
        }

        filter_init();
        for (int i = 1; i < n; i+=2)
        {
            out[i] = p_filter( in[i] );
        }

    }

   stopTimer();
}
