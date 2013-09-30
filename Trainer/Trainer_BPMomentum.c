#include "Trainer_BPMomentum.h"

FeedForwardMomentum* __Momentum;
float __MomentumFactor = 0;

void Trainer_SetBPMomentum(FeedForwardMomentum* Dest)
{
    __Momentum = Dest;
}

void Trainer_SetBPMomentumFactor(float Factor)
{
    __MomentumFactor = Factor;
}
