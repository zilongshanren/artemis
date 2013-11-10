#include "TrigLUT.h"

#include <math.h>

float TrigLUT::cos( float rad )
{
	lazy_init();
	return _cos[(int)(rad * radToIndex) & SIN_MASK];
}

float TrigLUT::sin( float rad )
{
	lazy_init();
	return _sin[(int)(rad * radToIndex) & SIN_MASK];
}

float TrigLUT::cosDeg( float deg )
{
	lazy_init();
	return _cos[(int)(deg * degToIndex) & SIN_MASK];
}

float TrigLUT::sinDeg( float deg )
{
	lazy_init();
	return _sin[(int)(deg * degToIndex) & SIN_MASK];
}

void TrigLUT::lazy_init()
{
	static bool initialized = false;
	if (!initialized)
	{
		RAD = (float)PI/180.0f;
		DEG = 180.0f/(float)PI;

		SIN_BITS = 12;
		SIN_MASK = ~(-1 << SIN_BITS);
		SIN_COUNT = SIN_MASK + 1;

		radFull = (float) (PI * 2.0f);
		degFull = (float) (360.0f);
		radToIndex = SIN_COUNT / radFull;
		degToIndex = SIN_COUNT / degFull;
		
		_sin.resize(SIN_COUNT);
		_cos.resize(SIN_COUNT);

		for (int i = 0; i < SIN_COUNT; ++i) 
		{
			_sin[i] = (float)::sin((i + 0.5f) / SIN_COUNT * radFull);
			_cos[i] = (float)::cos((i + 0.5f) / SIN_COUNT * radFull);
		}
		initialized = true;
	}
}

float TrigLUT::RAD		  = 0.0f;
float TrigLUT::DEG		  = 0.0f;
int TrigLUT::SIN_BITS	  = 0;
int TrigLUT::SIN_MASK  	  = 0;
int TrigLUT::SIN_COUNT    = 0;
float TrigLUT::radFull	  = 0.0f;
float TrigLUT::radToIndex = 0.0f;
float TrigLUT::degFull	  = 0.0f;
float TrigLUT::degToIndex = 0.0f;
std::vector<float> TrigLUT::_sin;
std::vector<float> TrigLUT::_cos;

const double TrigLUT::PI = 3.14159265358979323846264338327950288;

