#include "RawSound.h"

RawSound::RawSound(){
    buffer           = NULL;
    _length          = 0;
    _channels        = 0;
    _rate_per_second = 0;
}

RawSound::RawSound(RawSound* _ptr){
    buffer           = new short[_ptr->length()];
    _length          = _ptr->length();
    _channels        = _ptr->channels();
    _rate_per_second = _ptr->sample_rate();
}

RawSound::RawSound(sf::SoundBuffer* _sb){
    _length          = _sb->getSampleCount();
    _channels        = _sb->getChannelCount();
    _rate_per_second = _sb->getSampleRate();
    buffer           = new short[_length];

    short* dataS  = (short*)_sb->getSamples();
    for(int i=0; i<_length; i++){
        buffer[i] = dataS[i];
    }
}

RawSound::~RawSound(){
    if( buffer != NULL ){
        delete buffer;
    }
}

short* RawSound::data(){
    return buffer;
}

unsigned int RawSound::channels() const{
    return _channels;
}

unsigned int RawSound::length() const{
    return _length;
}

unsigned int RawSound::sample_rate() const{
    return _rate_per_second;
}

void RawSound::fill(RawSound* _ptr){
    if( buffer != NULL ){
        delete buffer;
    }
    _length          = _ptr->length();
    _channels        = _ptr->channels();
    _rate_per_second = _ptr->sample_rate();
    buffer           = new short[_length];

    short* dataS  = _ptr->data();
    for(int i=0; i<_length; i++){
        buffer[i] = dataS[i];
    }
}

void RawSound::transform(unsigned int pchannels, unsigned int plength, unsigned int psample_rate){
    if( (pchannels    == channels()   ) &&
        (plength      == length()     ) &&
        (psample_rate == sample_rate()) )
        return;

    if( buffer != NULL ){
        delete buffer;
    }
    _length          = plength;
    _channels        = pchannels;
    _rate_per_second = psample_rate;
    buffer           = new short[_length];
}
