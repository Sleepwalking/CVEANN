#ifndef FEEDFORWARDNL_H
#define FEEDFORWARDNL_H

#include "Neuron/Neuron.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(Neuron, NList);
} EndClass(NeuronLayer);

AutoClass
{
    ArrayType_Define(NeuronLayer, Layers);
} EndClass(FeedForwardNL);

#define FeedForwardNL_LayerSize(Dest, Index)\
    ((Dest).Layers[Index].NList_Index)

extern void FeedForwardNL_SetLayer(FeedForwardNL* Dest, int* LayerSize, int LayerNum);
extern void FeedForwardNL_UpdateState(FeedForwardNL* Dest);
extern void FeedForwardNL_RandomInit(FeedForwardNL* Dest, float Range);

#endif
