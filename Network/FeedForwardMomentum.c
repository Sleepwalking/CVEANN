#include "FeedForwardMomentum.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>

_Constructor_ (MomentumLayer)
{
    ArrayType_Init(float*, Dest -> dW);
}

_Destructor_ (MomentumLayer)
{
    int i;
    for(i = 0; i <= Dest -> dW_Index; i ++)
        free(Dest -> dW[i]);
    ArrayType_Dtor(float*, Dest -> dW);
}

_Constructor_ (FeedForwardMomentum)
{
    ArrayType_Init(MomentumLayer, Dest -> Layers);
}

_Destructor_ (FeedForwardMomentum)
{
    ArrayType_ObjDtor(MomentumLayer, Dest -> Layers);
    ArrayType_Dtor(MomentumLayer, Dest -> Layers);
}

void FeedForwardMomentum_Construct(FeedForwardMomentum* Dest, FeedForward* Src)
{
    int i, j;
    ArrayType_ObjDtor(MomentumLayer, Dest -> Layers);
    ArrayType_Resize(MomentumLayer, Dest -> Layers, Src -> Layers_Index + 1);
    Dest -> Layers_Index = Src -> Layers_Index;

    for(i = 0; i <= Src -> Layers_Index; i ++)
    {
        MomentumLayer_Ctor(Dest -> Layers + i);
        //The first layer is empty.
        if(i > 0)
        {
            ArrayType_Resize(float*, Dest -> Layers[i].dW, Src -> Layers[i].NList_Index + 1);
            Dest -> Layers[i].dW_Index = Src -> Layers[i].NList_Index;
            Dest -> Layers[i].dWSize = Src -> Layers[i - 1].NList_Index;
            for(j = 0; j <= Dest -> Layers[i].dW_Index; j ++)
                Dest -> Layers[i].dW[j] = (float*)malloc(sizeof(float) * Src -> Layers[i - 1].NList_Index + 4);
        }
    }
}

void FeedForwardMomentum_Construct_Fast(FeedForwardMomentum* Dest, FeedForward_Fast* Src)
{
    int i, j;
    ArrayType_ObjDtor(MomentumLayer, Dest -> Layers);
    ArrayType_Resize(MomentumLayer, Dest -> Layers, Src -> Layers_Index + 1);
    Dest -> Layers_Index = Src -> Layers_Index;

    for(i = 0; i <= Src -> Layers_Index; i ++)
    {
        MomentumLayer_Ctor(Dest -> Layers + i);
        //The first layer is empty.
        if(i > 0)
        {
            ArrayType_Resize(float*, Dest -> Layers[i].dW, Src -> Layers[i].W_Index + 1);
            Dest -> Layers[i].dW_Index = Src -> Layers[i].W_Index;
            Dest -> Layers[i].dWSize = Src -> Layers[i - 1].W_Index;
            for(j = 0; j <= Dest -> Layers[i].dW_Index; j ++)
                Dest -> Layers[i].dW[j] = (float*)malloc(sizeof(float) * Src -> Layers[i - 1].W_Index + 4);
        }
    }
}

void FeedForwardMomentum_Clear(FeedForwardMomentum* Dest)
{
    int i, j;
    for(i = 1; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].dW_Index; j ++)
            Boost_FloatSet(Dest -> Layers[i].dW[j], 0, Dest -> Layers[i].dWSize + 1);
}
