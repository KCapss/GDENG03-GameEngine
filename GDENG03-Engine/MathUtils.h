#pragma once
#include "Matrix4x4.h"
#include "Vector3D.h"

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);
	static float* convertInto1D(Matrix4x4 mat);
	static Vector3D convertQuateriontoEuler(double w, double x, double y, double z);

};
