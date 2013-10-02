#include "Trainer_SOFM.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include "CVEDSP/IntrinUtil/Calculation.h"
#include <malloc.h>

void Trainer_Organize(float* Dest, int Length)
{
    float Sum;
    float* Tmp = (float*)malloc(sizeof(float) * Length);
    Boost_FloatMulArr(Tmp, Dest, Dest, Length);
    Sum = Boost_FloatSum(Tmp, Length);
    Sum = Boost_Sqr(Sum);
    Boost_FloatDiv(Dest, Dest, Sum, Length);
    free(Tmp);
}

float Trainer_Distance(float X1, float Y1, float X2, float Y2)
{
    return Boost_Sqr((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
}

void Trainer_SOFM(SOFMDescriptor Dest, float* Input, float Eit, float Radius)
{
    int i;
    int Winner, Winner_X, Winner_Y, i_X, i_Y;
    Boost_FloatCopy(Dest.BaseNet -> Layers[0].O, Input, Dest.BaseNet -> Layers[0].O_Index + 1);
    Trainer_Organize(Dest.BaseNet -> Layers[0].O, Dest.BaseNet -> Layers[0].O_Index + 1);
    Winner = SOFM_UpdateState(Dest);
    Winner_X = SOFM_X(Dest, Winner);
    Winner_Y = SOFM_Y(Dest, Winner);
    printf("Winner: x = %d, y = %d.\n", Winner_X, Winner_Y);
    NeuronLayer* Layer = Dest.BaseNet -> Layers + 1;

    int LayerSize = Dest.BaseNet -> Layers[0].O_Index;
    float* Tmp = (float*)malloc(sizeof(float) * (LayerSize + 1));
    for(i = 0; i <= Layer -> W_Index; i ++)
    {
        float Dist;
        i_X = SOFM_X(Dest, i);
        i_Y = SOFM_Y(Dest, i);
        Dist = Trainer_Distance(Winner_X, Winner_Y, i_X, i_Y);
        if(Dist < Radius)
        {
            float dW = Eit * Radius / (Dist + 1);
            Boost_FloatCopy(Tmp, Layer -> W[i], LayerSize + 1);
            Trainer_Organize(Tmp, LayerSize + 1);
            Boost_FloatSubArr(Tmp, Dest.BaseNet -> Layers[0].O, Tmp, LayerSize + 1);
            Boost_FloatMul(Tmp, Tmp, dW, LayerSize + 1);
            Boost_FloatAddArr(Layer -> W[i], Layer -> W[i], Tmp, LayerSize + 1);
        }
    }
    free(Tmp);
}
