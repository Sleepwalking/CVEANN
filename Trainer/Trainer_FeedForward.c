#include "Trainer_FeedForward.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>
#include <string.h>
#include <math.h>

float Trainer_FeedForward_BP(FeedForward* Dest, float* Input, float* ExpectedOutput, float Eit)
{
    int i, j, k, MaxSize;
    FeedForward_SetInput(Dest, Input);
    FeedForward_UpdateState(Dest);

    MaxSize = - 999;
    for(i = 0; i < Dest -> Layers_Index; i ++)
        if(Dest -> Layers[i].NList_Index > MaxSize)
            MaxSize = Dest -> Layers[i].NList_Index;

    float* DeltaW = (float*)malloc(sizeof(float) * MaxSize + 4);
    float* DeltaF = (float*)malloc(sizeof(float) * MaxSize + 4);
    float* DeltaF2 = (float*)malloc(sizeof(float) * MaxSize + 4);

    for(i = Dest -> Layers_Index; i > 0; i --)
    {
        if(i == Dest -> Layers_Index)
        {
            //Toppest Layer
            for(j = 0; j <= Dest -> Layers[i].NList_Index; j ++)
            {
                DeltaF[j] = (ExpectedOutput[j] - Dest -> Layers[i].NList[j].Output)
                          * Dest -> Layers[i].NList[j].Output
                          * (1.0f - Dest -> Layers[i].NList[j].Output);
                DeltaW[j] = Eit * DeltaF[j];
            }
        }else
        {
            //Hidden Layer
            for(j = 0; j <= Dest -> Layers[i].NList_Index; j ++)
            {
                DeltaF[j] = 0;
                for(k = 0; k <= Dest -> Layers[i + 1].NList_Index; k ++)
                    DeltaF[j] += DeltaF2[k] * Dest -> Layers[i + 1].NList[k].Weight[j];
                DeltaW[j] = Eit * DeltaF[j]
                          * Dest -> Layers[i].NList[j].Output
                          * (1.0f - Dest -> Layers[i].NList[j].Output);
            }
        }
        for(j = 0; j <= Dest -> Layers[i].NList_Index; j ++)
        {
            /*
            if(__MomentumFactor != 0)
            {
                Boost_FloatMul(__Momentum -> Layers[i].dW[j], __Momentum -> Layers[i].dW[j], __MomentumFactor,  __Momentum -> Layers[i].dWSize + 1);
                Boost_FloatAddArr(DeltaW, DeltaW, __Momentum -> Layers[i].dW[j], __Momentum -> Layers[i].dWSize + 1);
                Boost_FloatCopy(__Momentum -> Layers[i].dW[i],  DeltaW, __Momentum -> Layers[i].dWSize + 1);
            }*/
            if(__MomentumFactor == 0)
            {
                for(k = 0; k <= Dest -> Layers[i - 1].NList_Index; k ++)
                    Dest -> Layers[i].NList[j].Weight[k] += DeltaW[j] * Dest -> Layers[i - 1].NList[k].Output;
            }else
            {
                Boost_FloatMul(__Momentum -> Layers[i].dW[j], __Momentum -> Layers[i].dW[j], __MomentumFactor,  __Momentum -> Layers[i].dWSize + 1);
                for(k = 0; k <= Dest -> Layers[i - 1].NList_Index; k ++)
                {
                    float wTmp = DeltaW[j] * Dest -> Layers[i - 1].NList[k].Output + __Momentum -> Layers[i].dW[j][k];
                    __Momentum -> Layers[i].dW[j][k] = wTmp;
                    Dest -> Layers[i].NList[j].Weight[k] += wTmp;
                }
            }
        }
        float* tmp = DeltaF;
        DeltaF = DeltaF2;
        DeltaF2 = tmp;
    }

    float E = 0;
    for(i = 0; i <= Dest -> Layers[Dest -> Layers_Index].NList_Index; i ++)
        E += pow(Dest -> Layers[Dest -> Layers_Index].NList[i].Output - ExpectedOutput[i], 2);

    free(DeltaF2);
    free(DeltaF);
    free(DeltaW);
    return E;
}
