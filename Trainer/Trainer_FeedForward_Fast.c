#include "Trainer_FeedForward_Fast.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>
#include <string.h>
#include <math.h>

float Trainer_FeedForward_Fast_BP(FeedForward_Fast* Dest, float* Input, float* ExpectedOutput, float Eit)
{
    int i, j, MaxSize;
    FeedForward_Fast_SetInput(Dest, Input);
    FeedForward_Fast_UpdateState(Dest);

    MaxSize = - 999;
    for(i = 0; i < Dest -> Layers_Index; i ++)
        if(Dest -> Layers[i].O_Index > MaxSize)
            MaxSize = Dest -> Layers[i].O_Index + 1;

    float* DeltaW = (float*)malloc(sizeof(float) * MaxSize);
    float* DeltaF = (float*)malloc(sizeof(float) * MaxSize);
    float* DeltaF2 = (float*)malloc(sizeof(float) * MaxSize);
    float* Tmp = (float*)malloc(sizeof(float) * MaxSize);

    for(i = Dest -> Layers_Index; i > 0; i --)
    {
        if(i == Dest -> Layers_Index)
        {
            //Toppest Layer

            /* Over Optimized
            int CircSize = Dest -> Layers[i].O_Index + 1;
            Boost_FloatSubArr(DeltaF, Dest -> Layers[i].O, ExpectedOutput, CircSize);
            Boost_FloatSub(Tmp, Dest -> Layers[i].O, 1, CircSize);
            Boost_FloatMulArr(DeltaF, DeltaF, Tmp, CircSize);
            Boost_FloatMulArr(DeltaF, DeltaF, Dest -> Layers[i].O, CircSize);
            Boost_FloatMul(DeltaW, DeltaF, Eit, CircSize);
            */

            for(j = 0; j <= Dest -> Layers[i].O_Index; j ++)
            {
                DeltaF[j] = (ExpectedOutput[j] - Dest -> Layers[i].O[j])
                          * Dest -> Layers[i].O[j]
                          * (1.0f - Dest -> Layers[i].O[j]);
                DeltaW[j] = Eit * DeltaF[j];
            }
        }else
        {
            //Hidden Layer

            int CircSize = Dest -> Layers[i].O_Index + 1;
            Boost_FloatSet(DeltaF, 0, CircSize);

            for(j = 0; j <= Dest -> Layers[i + 1].O_Index; j ++)
            {
                Boost_FloatMul(Tmp, Dest -> Layers[i + 1].W[j], DeltaF2[j], CircSize);
                Boost_FloatAddArr(DeltaF, DeltaF, Tmp, CircSize);
            }

            /* Over Optimized
            Boost_FloatSub(Tmp, Dest -> Layers[i].O, 1, CircSize);
            Boost_FloatMulArr(DeltaW, Tmp, Dest -> Layers[i].O, CircSize);
            Boost_FloatMulArr(DeltaW, DeltaW, DeltaF, CircSize);
            Boost_FloatMul(DeltaW, DeltaW, - Eit, CircSize);
            */

            for(j = 0; j <= Dest -> Layers[i].O_Index; j ++)
            {
                DeltaW[j] = Eit * DeltaF[j]
                          * Dest -> Layers[i].O[j]
                          * (1.0f - Dest -> Layers[i].O[j]);
            }
        }
        for(j = 0; j <= Dest -> Layers[i].O_Index; j ++)
        {
            Boost_FloatMul(Tmp, Dest -> Layers[i - 1].O, DeltaW[j], Dest -> Layers[i - 1].O_Index + 1);
            if(__MomentumFactor != 0)
            {
                Boost_FloatMul(__Momentum -> Layers[i].dW[j], __Momentum -> Layers[i].dW[j], __MomentumFactor,  __Momentum -> Layers[i].dWSize + 1);
                Boost_FloatAddArr(Tmp, Tmp, __Momentum -> Layers[i].dW[j], __Momentum -> Layers[i].dWSize + 1);
                Boost_FloatCopy(__Momentum -> Layers[i].dW[j], Tmp, __Momentum -> Layers[i].dWSize + 1);
            }
            Boost_FloatAddArr(Dest -> Layers[i].W[j], Dest -> Layers[i].W[j], Tmp, Dest -> Layers[i - 1].O_Index + 1);
        }
        float* tmp = DeltaF;
        DeltaF = DeltaF2;
        DeltaF2 = tmp;
    }

    float E = 0;
    for(i = 0; i <= Dest -> Layers[Dest -> Layers_Index].O_Index; i ++)
        E += pow(Dest -> Layers[Dest -> Layers_Index].O[i] - ExpectedOutput[i], 2);

    free(DeltaF2);
    free(DeltaF);
    free(DeltaW);
    free(Tmp);
    return E;
}
