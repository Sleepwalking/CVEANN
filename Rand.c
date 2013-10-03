#include "Rand.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include "CVEDSP/IntrinUtil/Calculation.h"
#include <stdlib.h>

float Random()
{
    return (float)(rand() % 200000) / 100000.0f - 1.0f;
}

int IntRandom(int Range)
{
    return rand() % Range - Range / 2;
}

void Organize(float* Dest, int Length)
{
    float Sum;
    float* Tmp = (float*)malloc(sizeof(float) * Length);
    Boost_FloatMulArr(Tmp, Dest, Dest, Length);
    Sum = Boost_FloatSum(Tmp, Length);
    Sum = Boost_Sqr(Sum);
    Boost_FloatDiv(Dest, Dest, Sum, Length);
    free(Tmp);
}
