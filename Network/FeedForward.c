#include "FeedForward.h"
#include "Rand.h"
#include "Activator.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>

_Constructor_ (NeuronLayer)
{
    ArrayType_Init(float*, Dest -> W);
    ArrayType_Init(float, Dest -> O);
}

_Destructor_ (NeuronLayer)
{
    int i;
    for(i = 0; i <= Dest -> W_Index; i ++)
        free(Dest -> W[i]);
    ArrayType_Dtor(float*, Dest -> W);
    ArrayType_Dtor(float, Dest -> O);
}

_Constructor_ (FeedForward)
{
    ArrayType_Init(NeuronLayer, Dest -> Layers);
}

_Destructor_ (FeedForward)
{
    ArrayType_ObjDtor(NeuronLayer, Dest -> Layers);
    ArrayType_Dtor(NeuronLayer, Dest -> Layers);
}

void FeedForward_SetLayer(FeedForward* Dest, int* LayerSize, int LayerNum)
{
    int i, j;
    ArrayType_ObjDtor(NeuronLayer, Dest -> Layers);
    ArrayType_Resize(NeuronLayer, Dest -> Layers, LayerNum);
    Dest -> Layers_Index = LayerNum - 1;

    for(i = 0; i < LayerNum; i ++)
    {
        NeuronLayer_Ctor(Dest -> Layers + i);
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

void FeedForward_UpdateState(FeedForward* Dest)
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
            //Dest -> Layers[i].O[j] = Boost_FloatSum(Tmp, Dest -> Layers[i - 1].O_Index + 1);
        }
    free(Tmp);
}

void FeedForward_RandomInit(FeedForward* Dest, float Range)
{
    int i, j, k;
    for(i = 1; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].W_Index; j ++)
            for(k = 0; k <= Dest -> Layers[i - 1].O_Index; k ++)
                Dest -> Layers[i].W[j][k] = Random() * Range;
}

void FeedForward_SetInput(FeedForward* Dest, float* Input)
{
    Boost_FloatCopy(Dest -> Layers[0].O, Input, Dest -> Layers[0].O_Index + 1);
}
