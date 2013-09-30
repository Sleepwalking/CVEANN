#include "Trainer_FeedForward3L_Fast.h"
#include "IntrinUtil/FloatArray.h"
#include <malloc.h>
#include <string.h>
#include <math.h>

float Trainer_FeedForward3L_Fast_BP(FeedForward3L_Fast* Dest, float* Input, float* ExpectedOutput, float Eit)
{
    int i;
    float* DeltaW = (float*)malloc(sizeof(float) * (Dest -> W_Index + 1)); //Change of Hidden Layer -> Output Layer
    float* DeltaV = (float*)malloc(sizeof(float) * (Dest -> V_Index + 1)); //Change of Input Layer -> Hidden Layer
    float* Delta = (float*)malloc(sizeof(float) * (Dest -> W_Index + 1)); //Learning para of Hidden Layer -> Output Layer
    float* VTemp = (float*)malloc(sizeof(float) * (Dest -> V_Index + 1));

    Boost_FloatCopy(Dest -> X, Input, Dest -> X_Index + 1);
    FeedForward3L_Fast_UpdateState(Dest);

    Boost_FloatSubArr(Delta, Dest -> O, ExpectedOutput, Dest -> W_Index + 1);
    Boost_FloatSub(DeltaW, Dest -> O, 1.0f, Dest -> W_Index + 1);
    Boost_FloatMulArr(Delta, Delta, DeltaW, Dest -> W_Index + 1);
    Boost_FloatMulArr(Delta, Delta, Dest -> O, Dest -> W_Index + 1);
    Boost_FloatMul(DeltaW, Delta, Eit, Dest -> W_Index + 1);

    Boost_FloatSet(DeltaV, 0, Dest -> V_Index + 1);

    for(i = 0; i <= Dest -> W_Index; i ++)
    {
        Boost_FloatMul(DeltaV, Dest -> Y, DeltaW[i], Dest -> V_Index + 1);
        Boost_FloatAddArr(Dest -> W[i], Dest -> W[i], DeltaV, Dest -> V_Index + 1);
    }

    Boost_FloatSet(DeltaV, 0, Dest -> V_Index + 1);
    for(i = 0; i <= Dest -> W_Index; i ++)
    {
        Boost_FloatMul(VTemp, Dest -> W[i], Delta[i], Dest -> V_Index + 1);
        Boost_FloatAddArr(DeltaV, DeltaV, VTemp, Dest -> V_Index + 1);
    }

    for(i = 1; i <= Dest -> V_Index; i ++)
    {
        DeltaV[i] *= Eit * Dest -> Y[i] * (1.0f - Dest -> Y[i]);
    }

    for(i = 1; i <= Dest -> V_Index; i ++)
    {
        Boost_FloatMul(VTemp, Dest -> X, DeltaV[i], Dest -> X_Index + 1);
        Boost_FloatAddArr(Dest -> V[i], Dest -> V[i], VTemp, Dest -> X_Index + 1);
    }

    float E = 0;
    for(i = 0; i <= Dest -> W_Index; i ++)
        E += pow(Dest -> O[i] - ExpectedOutput[i], 2);

    free(Delta);
    free(DeltaW);
    free(DeltaV);
    free(VTemp);
    return E;
}
