#include "MathUtils.h"
#include <stdlib.h>

float MathUtils::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}

float* MathUtils::convertInto1D(Matrix4x4 mat)
{
    float copy[16];
    for (int i = 0; i < 4; i++)
    {
	    for(int j = 0; j < 4; j++)
	    {
            copy[(i * 4) + j] = mat.m_mat[i][j];
	    }
    }

    return copy;
}
