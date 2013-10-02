#ifndef FEEDFORWARD_FAST_H
#define FEEDFORWARD_FAST_H
//Faster but less flexible version of FeedForward.

#include "FeedForward.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(float*, W);
    ArrayType_Define(float, O);
} EndClass(NeuronLayer);

AutoClass
{
    ArrayType_Define(NeuronLayer, Layers);
} EndClass(FeedForward);

extern void FeedForward_SetLayer(FeedForward* Dest, int* LayerSize, int LayerNum);
extern void FeedForward_UpdateState(FeedForward* Dest);
extern void FeedForward_RandomInit(FeedForward* Dest, float Range);
extern void FeedForward_SetInput(FeedForward* Dest, float* Input);

#endif
