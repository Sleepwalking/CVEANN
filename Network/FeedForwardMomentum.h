#ifndef FEEDFORWARDMOMENTUM_H
#define FEEDFORWARDMOMENTUM_H

#include "FeedForward.h"
#include "FeedForward_Fast.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(float*, dW);
    int dWSize;
} EndClass(MomentumLayer);

AutoClass
{
    ArrayType_Define(MomentumLayer, Layers);
} EndClass(FeedForwardMomentum);

extern void FeedForwardMomentum_Construct(FeedForwardMomentum* Dest, FeedForward* Src);
extern void FeedForwardMomentum_Construct_Fast(FeedForwardMomentum* Dest, FeedForward_Fast* Src);
extern void FeedForwardMomentum_Clear(FeedForwardMomentum* Dest);

#endif
