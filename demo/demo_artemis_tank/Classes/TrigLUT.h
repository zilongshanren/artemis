#ifndef __TRIG_LUT_H__
#define __TRIG_LUT_H__

// C++
#include <vector>

class TrigLUT
{
public:
	static float cos(float f);
	static float sin(float f);
	static float cosDeg(float f);
	static float sinDeg(float f);

protected:
	static void lazy_init();

private:
	static float RAD;
	static float DEG;
	static int SIN_BITS;
	static int SIN_MASK;
	static int SIN_COUNT;
	static float radFull;
	static float radToIndex;
	static float degFull;
	static float degToIndex;
	static std::vector<float> _sin;
	static std::vector<float> _cos;

	static const double PI;
};


#endif // __TRIG_LUT_H__