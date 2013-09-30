#ifndef FEEDFORWARD_H
#define FEEDFORWARD_H

#include "Neuron/Neuron.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(Neuron, NList);
} EndClass(NeuronLayer);

AutoClass
{
    ArrayType_Define(NeuronLayer, Layers);
} EndClass(FeedForward);

#define FeedForward_LayerSize(Dest, Index)\
    ((Dest).Layers[Index].NList_Index)

extern void FeedForward_SetLayer(FeedForward* Dest, int* LayerSize, int LayerNum);
extern void FeedForward_UpdateState(FeedForward* Dest);
extern void FeedForward_RandomInit(FeedForward* Dest, float Range);
extern void FeedForward_SetInput(FeedForward* Dest, float* Input);

#endif
