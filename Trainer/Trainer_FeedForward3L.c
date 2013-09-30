#include "Trainer_FeedForward3L.h"
#include <malloc.h>
#include <string.h>
#include <math.h>

float Trainer_FeedForward3L_BP(FeedForward3L* Dest, float* Input, float* ExpectedOutput, float Eit)
{
    int i, j;
    float* DeltaW = (float*)malloc(sizeof(float) * (Dest -> L3_Index + 1)); //Change of Hidden Layer -> Output Layer
    float* DeltaV = (float*)malloc(sizeof(float) * (Dest -> L2_Index + 1)); //Change of Input Layer -> Hidden Layer
    float* Delta = (float*)malloc(sizeof(float) * (Dest -> L2_Index + 1)); //Learning para of Hidden Layer -> Output Layer
    for(i = 0; i <= Dest -> L1_Index; i ++)
        Dest -> L1[i].InputVal = Input[i];
    FeedForward3L_UpdateState(Dest);

    for(i = 0; i <= Dest -> L3_Index; i ++)
    {
        Delta[i] = (ExpectedOutput[i] - Dest -> L3[i].Output) * Dest -> L3[i].Output * (1.0f - Dest -> L3[i].Output);
        DeltaW[i] = Eit * Delta[i];
    }
    memset(DeltaV, 0, sizeof(float) * (Dest -> L2_Index + 1));

    for(i = 0; i <= Dest -> L3_Index; i ++)
        for(j = 0; j <= Dest -> L3[i].Weight_Index; j ++)
            Dest -> L3[i].Weight[j] += DeltaW[i] * Dest -> L3[i].Input[j] -> Output;

    for(i = 1; i <= Dest -> L2_Index; i ++)
    {
        DeltaV[i] = 0;
        for(j = 0; j <= Dest -> L3_Index; j ++)
            DeltaV[i] += Delta[j] * Dest -> L3[j].Weight[i];
        DeltaV[i] *= Eit * Dest -> L2[i].Output * (1.0f - Dest -> L2[i].Output);
    }

    for(i = 1; i <= Dest -> L2_Index; i ++)
        for(j = 0; j <= Dest -> L2[i].Weight_Index; j ++)
            Dest -> L2[i].Weight[j] += DeltaV[i] * Dest -> L2[i].Input[j] -> Output;

    float E = 0;
    for(i = 0; i <= Dest -> L3_Index; i ++)
        E += pow(Dest -> L3[i].Output - ExpectedOutput[i], 2);

    free(Delta);
    free(DeltaW);
    free(DeltaV);
    return E;
}
