#ifndef FEEDFORWARD_FAST_H
#define FEEDFORWARD_FAST_H
//Faster but less flexible version of FeedForward.

#include "FeedForward.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(float*, W);
    ArrayType_Define(float, O);
} EndClass(NeuronLayer_Fast);

AutoClass
{
    ArrayType_Define(NeuronLayer_Fast, Layers);
} EndClass(FeedForward_Fast);

extern void FeedForward_Fast_SetLayer(FeedForward_Fast* Dest, int* LayerSize, int LayerNum);
extern void FeedForward_Fast_UpdateState(FeedForward_Fast* Dest);
extern void FeedForward_Fast_RandomInit(FeedForward_Fast* Dest, float Range);
extern void FeedForward_Fast_SetInput(FeedForward_Fast* Dest, float* Input);

extern int FeedForward_Fast_FromFeedForward(FeedForward_Fast* Dest, FeedForward* Src);

#endif
