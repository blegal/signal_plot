#ifndef __C_Equalization__
#define __C_Equalization__

#include "Filter.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iomanip>
#include <iostream>
#include <math.h>

class FilterLibrary
{
public:
    FilterLibrary();
    virtual ~FilterLibrary();

    virtual Filter* getFilter(int i);
    virtual int size();

private:
    vector<Filter*> *liste;
};

#endif

