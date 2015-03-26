#include "Filter.h"

Filter::Filter() : timer()
{
    name = "template";
}


Filter::Filter(std::string _name) : timer()
{
    name = _name;
}


Filter::~Filter()
{

}


char* Filter::cstr_Name()
{
	return (char*)name.c_str();
}


std::string Filter::Name()
{
	return name;
}


int Filter::getProcTime()
{
	return timer.get_time_ms();
}


void Filter::startTimer()
{
	return timer.start();
}


void Filter::stopTimer()
{
	return timer.stop();
}
