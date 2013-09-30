#include "FeedForwardNL_Fast.h"
#include "Rand.h"
#include "Activator.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>

_Constructor_ (NeuronLayer_Fast)
{
    ArrayType_Init(float*, Dest -> W);
    ArrayType_Init(float, Dest -> O);
}

_Destructor_ (NeuronLayer_Fast)
{
    int i;
    for(i = 0; i <= Dest -> W_Index; i ++)
        free(Dest -> W[i]);
    ArrayType_Dtor(float*, Dest -> W);
    ArrayType_Dtor(float, Dest -> O);
}

_Constructor_ (FeedForwardNL_Fast)
{
    ArrayType_Init(NeuronLayer_Fast, Dest -> Layers);
}

_Destructor_ (FeedForwardNL_Fast)
{
    ArrayType_ObjDtor(NeuronLayer_Fast, Dest -> Layers);
    ArrayType_Dtor(NeuronLayer_Fast, Dest -> Layers);
}

void FeedForwardNL_Fast_SetLayer(FeedForwardNL_Fast* Dest, int* LayerSize, int LayerNum)
{
    int i, j;
    ArrayType_ObjDtor(NeuronLayer_Fast, Dest -> Layers);
    ArrayType_Resize(NeuronLayer_Fast, Dest -> Layers, LayerNum);
    Dest -> Layers_Index = LayerNum - 1;

    for(i = 0; i < LayerNum; i ++)
    {
        NeuronLayer_Fast_Ctor(Dest -> Layers + i);
        if(i == 0)
            ArrayType_Resize(float, Dest -> Layers[i].O, LayerSize[i]);
        else
        {
            ArrayType_Resize(float*, Dest -> Layers[i].W, LayerSize[i]);
            ArrayType_Resize(float, Dest -> Layers[i].O, LayerSize[i]);
            Dest -> Layers[i].W_Index = LayerSize[i] - 1;
            for(j = 0; j < LayerSize[i]; j ++)
                Dest -> Layers[i].W[j] = (float*)malloc(sizeof(float) * LayerSize[i - 1] + 4);
        }
        Dest -> Layers[i].O_Index = LayerSize[i] - 1;
    }
}

void FeedForwardNL_Fast_UpdateState(FeedForwardNL_Fast* Dest)
{
    int i, j;
    int TmpSize = - 999;
    float* Tmp;

    for(i = 0; i <= Dest -> Layers_Index; i ++)
        if(Dest -> Layers[i].O_Index > TmpSize)
            TmpSize = Dest -> Layers[i].O_Index + 1;
    Tmp = (float*)malloc(sizeof(float) * TmpSize);

    for(i = 1; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].W_Index; j ++)
        {
            Boost_FloatMulArr(Tmp, Dest -> Layers[i - 1].O, Dest -> Layers[i].W[j], Dest -> Layers[i - 1].O_Index + 1);
            Dest -> Layers[i].O[j] = Activator_Sigmoid(Boost_FloatSum(Tmp, Dest -> Layers[i - 1].O_Index + 1));
        }
    free(Tmp);
}

void FeedForwardNL_Fast_RandomInit(FeedForwardNL_Fast* Dest, float Range)
{
    int i, j, k;
    for(i = 1; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].W_Index; j ++)
            for(k = 0; k <= Dest -> Layers[i - 1].O_Index; k ++)
                Dest -> Layers[i].W[j][k] = Random() * Range - Range * 0.5;
}

int FeedForwardNL_Fast_FromFeedForwardNL(FeedForwardNL_Fast* Dest, FeedForwardNL* Src)
{
    int i, j;
    if(Src -> Layers_Index != Dest -> Layers_Index)
        return 0;
    for(i = 0; i <= Dest -> Layers_Index; i ++)
        if(Src -> Layers[i].NList_Index != Dest -> Layers[i].O_Index)
            return 0;

    for(i = 1; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].W_Index; j ++)
            Boost_FloatCopy(Dest -> Layers[i].W[j], Src -> Layers[i].NList[j].Weight, Dest -> Layers[i - 1].O_Index + 1);

    return 1;
}
