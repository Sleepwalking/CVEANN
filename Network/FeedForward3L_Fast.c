#include "FeedForward3L_Fast.h"
#include "Rand.h"
#include "Activator.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>

_Constructor_ (FeedForward3L_Fast)
{
    ArrayType_Init(float*, Dest -> V);
    ArrayType_Init(float*, Dest -> W);
    ArrayType_Init(float, Dest -> X);
    ArrayType_Init(float, Dest -> Y);
    ArrayType_Init(float, Dest -> O);
}

_Destructor_ (FeedForward3L_Fast)
{
    int i;
    for(i = 0; i <= Dest -> V_Index; i ++)
        free(Dest -> V[i]);
    for(i = 0; i <= Dest -> W_Index; i ++)
        free(Dest -> W[i]);
    ArrayType_Dtor(float*, Dest -> V);
    ArrayType_Dtor(float*, Dest -> W);
    ArrayType_Dtor(float, Dest -> X);
    ArrayType_Dtor(float, Dest -> Y);
    ArrayType_Dtor(float, Dest -> O);
}

void FeedForward3L_Fast_SetLayer(FeedForward3L_Fast *Dest, int L1, int L2, int L3)
{
    int i;
    for(i = 0; i <= Dest -> V_Index; i ++)
        free(Dest -> V[i]);
    for(i = 0; i <= Dest -> W_Index; i ++)
        free(Dest -> W[i]);

    ArrayType_Resize(float*, Dest -> V, L2);
    ArrayType_Resize(float*, Dest -> W, L3);
    ArrayType_Resize(float, Dest -> X, L1);
    ArrayType_Resize(float, Dest -> Y, L2);
    ArrayType_Resize(float, Dest -> O, L3);

    Dest -> V_Index = L2 - 1;
    Dest -> W_Index = L3 - 1;
    Dest -> X_Index = L1 - 1;
    Dest -> Y_Index = L2 - 1;
    Dest -> O_Index = L3 - 1;

    for(i = 0; i < L2; i ++)
        Dest -> V[i] = (float*)malloc(sizeof(float) * L1);

    for(i = 0; i < L3; i ++)
        Dest -> W[i] = (float*)malloc(sizeof(float) * L2);
}

void FeedForward3L_Fast_RandomInit(FeedForward3L_Fast *Dest, float Range)
{
    int i, j;
    for(i = 0; i <= Dest -> V_Index; i ++)
        for(j = 0; j <= Dest -> X_Index; j ++)
            Dest -> V[i][j] = Random() * Range - Range * 0.5;
    for(i = 0; i <= Dest -> W_Index; i ++)
        for(j = 0; j <= Dest -> Y_Index; j ++)
            Dest -> W[i][j] = Random() * Range - Range * 0.5;
}

void FeedForward3L_Fast_UpdateState(FeedForward3L_Fast *Dest)
{
    int i;
    int TmpSize = Dest -> V_Index > Dest -> W_Index ? Dest -> V_Index + 1: Dest -> W_Index + 1;
    float* Tmp = (float*)malloc(sizeof(float) * TmpSize);
    for(i = 0; i <= Dest -> V_Index; i ++)
    {
        Boost_FloatMulArr(Tmp, Dest -> V[i], Dest -> X, Dest -> X_Index + 1);
        Dest -> Y[i] = Activator_Sigmoid(Boost_FloatSum(Tmp, Dest -> X_Index + 1));
    }
    for(i = 0; i <= Dest -> W_Index; i ++)
    {
        Boost_FloatMulArr(Tmp, Dest -> W[i], Dest -> Y, Dest -> Y_Index + 1);
        Dest -> O[i] = Activator_Sigmoid(Boost_FloatSum(Tmp, Dest -> Y_Index + 1));
    }
    free(Tmp);
}
int FeedForward3L_Fast_FromFeedForward3L(FeedForward3L_Fast* Dest, FeedForward3L* Src)
{
    int i;
    if(Src -> L1_Index != Dest -> X_Index || Src -> L2_Index != Dest -> Y_Index || Src -> L3_Index != Dest -> O_Index)
        return 0;
    for(i = 0; i <= Dest -> Y_Index; i ++)
        Boost_FloatCopy(Dest -> V[i], Src -> L2[i].Weight, Dest -> X_Index + 1);
    for(i = 0; i <= Dest -> O_Index; i ++)
        Boost_FloatCopy(Dest -> W[i], Src -> L3[i].Weight, Dest -> Y_Index + 1);
    return 1;
}
