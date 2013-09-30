#ifndef FEEDFORWARD3L_H
#define FEEDFORWARD3L_H

#include "Neuron/Neuron.h"
#include "RUtil/RUtil.h"

AutoClass
{
    ArrayType_Define(Neuron, L1);
    ArrayType_Define(Neuron, L2);
    ArrayType_Define(Neuron, L3);
} EndClass(FeedForward3L);

extern void FeedForward3L_SetLayer(FeedForward3L* Dest, int L1, int L2, int L3);
extern void FeedForward3L_UpdateState(FeedForward3L* Dest);
extern void FeedForward3L_RandomInit(FeedForward3L* Dest, float Range);

#endif
