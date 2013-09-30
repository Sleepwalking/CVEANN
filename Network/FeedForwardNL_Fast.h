#ifndef FEEDFORWARDNL_FAST_H
#define FEEDFORWARDNL_FAST_H
//Faster but less flexible version of FeedForwardNL.

#include "FeedForwardNL.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(float*, W);
    ArrayType_Define(float, O);
} EndClass(NeuronLayer_Fast);

AutoClass
{
    ArrayType_Define(NeuronLayer_Fast, Layers);
} EndClass(FeedForwardNL_Fast);

extern void FeedForwardNL_Fast_SetLayer(FeedForwardNL_Fast* Dest, int* LayerSize, int LayerNum);
extern void FeedForwardNL_Fast_UpdateState(FeedForwardNL_Fast* Dest);
extern void FeedForwardNL_Fast_RandomInit(FeedForwardNL_Fast* Dest, float Range);
extern int FeedForwardNL_Fast_FromFeedForwardNL(FeedForwardNL_Fast* Dest, FeedForwardNL* Src);

#endif
