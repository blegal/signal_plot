#include "FilterLibrary.h"

#include "./effects/Equalization.h"
#include "Copy.h"
#include "./noise/Denoise_3taps.h"
#include "./noise/Denoise_Gaussian.h"

#include "./low_pass/LowPass_2taps.h"

#include "./high_pass/HighPass_2taps.h"

#include "./low_pass/Filter_Fc_100Hz.h"
#include "./low_pass/Filter_Fc_500Hz.h"
#include "./low_pass/Filter_Fc_2kHz.h"
#include "./low_pass/Filter_Fc_8kHz.h"
#include "./low_pass/Filter_Fc_12kHz.h"

#include "./high_pass/HP_Filter_Fc_100Hz.h"
#include "./high_pass/HP_Filter_Fc_500Hz.h"
#include "./high_pass/HP_Filter_Fc_2kHz.h"
#include "./high_pass/HP_Filter_Fc_8kHz.h"
#include "./high_pass/HP_Filter_Fc_12kHz.h"

#include "./band_pass/Filter_Fp_1500Hz_2500Hz.h"

#include "./band_stop/Filter_Fs_1500Hz_2500Hz.h"

#include "./noise/NoiseAWNG.h"
#include "./channels/Mono2Stereo_fx1.h"
#include "./channels/Mono2Stereo_fx2.h"
#include "./channels/Stereo2Mono_fx1.h"
#include "./channels/Stereo2Mono_fx2.h"
#include "./effects/Echo_500ms.h"
#include "./effects/BassBooster.h"

#include "./effects/Modulation_1kHz.h"
#include "./effects/Modulation_1kHz_lut.h"

FilterLibrary::FilterLibrary()
{
    liste = new vector<Filter*>();
    liste->push_back( new Copy()             );
    liste->push_back( new NoiseAWNG()        );
    liste->push_back( new Modulation_1kHz()  );
    liste->push_back( new Modulation_1kHz_lut()  );
    liste->push_back( new Denoise_3taps()    );
    liste->push_back( new Denoise_Gaussian() );
    liste->push_back( new fEqualization()    );
    liste->push_back( new LowPass_2taps()    );
    liste->push_back( new HighPass_2taps()   );
//    liste->push_back( new Filter_Fs_10()     );

    liste->push_back( new Filter_Fc_100Hz()  );
    liste->push_back( new Filter_Fc_500Hz()  );
    liste->push_back( new Filter_Fc_2kHz()   );
    liste->push_back( new Filter_Fc_8kHz()   );
    liste->push_back( new Filter_Fc_12kHz()   );

    liste->push_back( new HP_Filter_Fc_100Hz() );
    liste->push_back( new HP_Filter_Fc_500Hz() );
    liste->push_back( new HP_Filter_Fc_2kHz() );
    liste->push_back( new HP_Filter_Fc_8kHz() );
    liste->push_back( new HP_Filter_Fc_12kHz() );

    liste->push_back( new Filter_Fp_1500Hz_2500Hz() );
    liste->push_back( new Filter_Fs_1500Hz_2500Hz() );

    liste->push_back( new Mono2Stereo_fx1()  );
    liste->push_back( new Mono2Stereo_fx2()  );
    liste->push_back( new Stereo2Mono_fx1()  );
    liste->push_back( new Stereo2Mono_fx2()  );
    liste->push_back( new Echo_500ms()       );
    liste->push_back( new BassBooster()       );

}

FilterLibrary::~FilterLibrary()
{
    while ( !liste->empty() )
    {
        Filter* f = liste->at( liste->size() -1 );
        liste->pop_back();
        delete f;
    }
    delete liste;
}

Filter* FilterLibrary::getFilter(int i)
{
//    printf("(DD) Asking for a processing filter (%d/%d)\n", i, size());
    if( i < 0 ){
        i = 0;
    }else if( i >= size() ){
        i = i % size();
    }
    return liste->at( i );
}

int FilterLibrary::size()
{
    return liste->size();
}

