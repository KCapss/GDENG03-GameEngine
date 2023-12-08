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

Vector3D MathUtils::convertQuateriontoEuler(double w, double x, double y, double z)
{
   
    Vector3D rotation;

    // roll (x-axis rotation)
    double sinr_cosp = 2.0f * (w * x + y * z);
    double cosr_cosp = 1.0f - 2.0f * (x * x + y * y);
	rotation.m_x = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = std::sqrt(1 + 2 * (w * y - x * z));
    double cosp = std::sqrt(1 - 2 * (w * y - x * z));
    rotation.m_y = 2.0f * std::atan2(sinp, cosp) - 3.14159f / 2.0f;

    // yaw (z-axis rotation)
    double siny_cosp = 2.0f * (w * z + x * y);
    double cosy_cosp = 1.0f - 2.0f * (y * y + z * z);
    rotation.m_z = std::atan2(siny_cosp, cosy_cosp);

    return rotation;
}
