#ifndef FEEDFORWARD3L_FAST_H
#define FEEDFORWARD3L_FAST_H
//Faster but less flexible version of FeedForward3L.

#include "FeedForward3L.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(float*, V); //Hidden Layer Weight
    ArrayType_Define(float*, W); //Output Layer Weight
    ArrayType_Define(float, X);  //Input Layer
    ArrayType_Define(float, Y);  //Hidden Layer Output
    ArrayType_Define(float, O);  //Output Layer Output
} EndClass(FeedForward3L_Fast);

extern void FeedForward3L_Fast_SetLayer(FeedForward3L_Fast* Dest, int L1, int L2, int L3);
extern void FeedForward3L_Fast_UpdateState(FeedForward3L_Fast* Dest);
extern void FeedForward3L_Fast_RandomInit(FeedForward3L_Fast* Dest, float Range);
extern int FeedForward3L_Fast_FromFeedForward3L(FeedForward3L_Fast* Dest, FeedForward3L* Src);

#endif
