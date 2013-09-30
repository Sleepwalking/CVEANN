#include "FeedForward3L.h"
#include "Rand.h"

_Constructor_ (FeedForward3L)
{
    ArrayType_Init(Neuron, Dest -> L1);
    ArrayType_Init(Neuron, Dest -> L2);
    ArrayType_Init(Neuron, Dest -> L3);
}

_Destructor_ (FeedForward3L)
{
    ArrayType_ObjDtor(Neuron, Dest -> L1);
    ArrayType_ObjDtor(Neuron, Dest -> L2);
    ArrayType_ObjDtor(Neuron, Dest -> L3);

    ArrayType_Dtor(Neuron, Dest -> L1);
    ArrayType_Dtor(Neuron, Dest -> L2);
    ArrayType_Dtor(Neuron, Dest -> L3);
}

void FeedForward3L_SetLayer(FeedForward3L* Dest, int L1, int L2, int L3)
{
    int i, j;

    ArrayType_ObjDtor(Neuron, Dest -> L1);
    ArrayType_ObjDtor(Neuron, Dest -> L2);
    ArrayType_ObjDtor(Neuron, Dest -> L3);

    Dest -> L1_Index = - 1;
    Dest -> L2_Index = - 1;
    Dest -> L3_Index = - 1;

    for(i = 0; i < L1; i ++)
    {
        ArrayType_PushNull(Neuron, Dest -> L1);
        Neuron_Ctor(Dest -> L1 + Dest -> L1_Index);
        Dest -> L1[Dest -> L1_Index].Type = NType_Input;
    }

    for(i = 0; i < L2; i ++)
    {
        ArrayType_PushNull(Neuron, Dest -> L2);
        Neuron_Ctor(Dest -> L2 + Dest -> L2_Index);
        Dest -> L2[Dest -> L2_Index].Type = NType_Neuron;
        for(j = 0; j <= Dest -> L1_Index; j ++)
            Neuron_ConnectFrom(Dest -> L2 + Dest -> L2_Index, Dest -> L1 + j);
    }

    for(i = 0; i < L3; i ++)
    {
        ArrayType_PushNull(Neuron, Dest -> L3);
        Neuron_Ctor(Dest -> L3 + Dest -> L3_Index);
        Dest -> L3[Dest -> L3_Index].Type = NType_Output;
        for(j = 0; j <= Dest -> L2_Index; j ++)
            Neuron_ConnectFrom(Dest -> L3 + Dest -> L3_Index, Dest -> L2 + j);
    }
}

void FeedForward3L_UpdateState(FeedForward3L* Dest)
{
    int i;
    for(i = 0; i <= Dest -> L1_Index; i ++)
        Neuron_UpdateState(Dest -> L1 + i);
    for(i = 0; i <= Dest -> L2_Index; i ++)
        Neuron_UpdateState(Dest -> L2 + i);
    for(i = 0; i <= Dest -> L3_Index; i ++)
        Neuron_UpdateState(Dest -> L3 + i);
}

void FeedForward3L_RandomInit(FeedForward3L* Dest, float Range)
{
    int i, j;
    for(i = 0; i <= Dest -> L2_Index; i ++)
        for(j = 0; j <= Dest -> L1_Index; j ++)
            Dest -> L2[i].Weight[j] = Random() * Range - Range * 0.5;
    for(i = 0; i <= Dest -> L3_Index; i ++)
        for(j = 0; j <= Dest -> L2_Index; j ++)
            Dest -> L3[i].Weight[j] = Random() * Range - Range * 0.5;
}
