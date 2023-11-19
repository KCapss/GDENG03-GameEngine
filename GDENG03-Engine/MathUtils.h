#pragma once
#include "Matrix4x4.h"

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);
	static float* convertInto1D(Matrix4x4 mat);

};
