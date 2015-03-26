#ifndef __C_FILTER__
#define __C_FILTER__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iomanip>
#include <iostream>
#include <math.h>

#include "../RawSound.h"
#include "../CTimer/CTimer.h"

using namespace std;

class Filter
{
private:
    std::string name;
    CTimer timer;
public:
    Filter();
    Filter(std::string _name);
    virtual ~Filter();

	char* cstr_Name();
	std::string Name();
    virtual void process(RawSound *in, RawSound *out) = 0;

    int getProcTime();

protected:
	void startTimer();
	void stopTimer();
};

#endif