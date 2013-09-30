#include "FeedForwardNL.h"
#include "Rand.h"

_Constructor_ (NeuronLayer)
{
    ArrayType_Init(Neuron, Dest -> NList);
}

_Destructor_ (NeuronLayer)
{
    ArrayType_ObjDtor(Neuron, Dest -> NList);
    ArrayType_Dtor(Neuron, Dest -> NList);
}

_Constructor_ (FeedForwardNL)
{
    ArrayType_Init(NeuronLayer, Dest -> Layers);
}

_Destructor_ (FeedForwardNL)
{
    ArrayType_ObjDtor(NeuronLayer, Dest -> Layers);
    ArrayType_Dtor(NeuronLayer, Dest -> Layers);
}

void FeedForwardNL_SetLayer(FeedForwardNL* Dest, int* LayerSize, int LayerNum)
{
    int i, j, k;
    ArrayType_ObjDtor(NeuronLayer, Dest -> Layers);
    Dest -> Layers_Index = - 1;
    for(i = 0; i < LayerNum; i ++)
    {
        ArrayType_PushNull(NeuronLayer, Dest -> Layers);
        NeuronLayer_Ctor(Dest -> Layers + i);

        ArrayType_Resize(Neuron, Dest -> Layers[i].NList, LayerSize[i]);
        Dest -> Layers[i].NList_Index = LayerSize[i] - 1;
        for(j = 0; j < LayerSize[i]; j ++)
        {
            Neuron_Ctor(Dest -> Layers[i].NList + j);
            if(i == 0)
                Dest -> Layers[i].NList[j].Type = NType_Input;
            else
            {
                if(i == LayerNum - 1)
                    Dest -> Layers[i].NList[j].Type = NType_Output;
                for(k = 0; k < LayerSize[i - 1]; k ++)
                    Neuron_ConnectFrom(Dest -> Layers[i].NList + j, Dest -> Layers[i - 1].NList + k);
            }
        }
    }
}

void FeedForwardNL_UpdateState(FeedForwardNL* Dest)
{
    int i, j;
    for(i = 0; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].NList_Index; j ++)
            Neuron_UpdateState(Dest -> Layers[i].NList + j);
}

void FeedForwardNL_RandomInit(FeedForwardNL* Dest, float Range)
{
    int i, j, k;
    for(i = 1; i <= Dest -> Layers_Index; i ++)
        for(j = 0; j <= Dest -> Layers[i].NList_Index; j ++)
            for(k = 0; k <= Dest -> Layers[i - 1].NList_Index; k ++)
                Dest -> Layers[i].NList[j].Weight[k] = Random() * Range - Range * 0.5;
}
