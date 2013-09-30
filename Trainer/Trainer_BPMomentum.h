#ifndef TRAINER_BPMOMENTUM_H
#define TRAINER_BPMOMENTUM_H

#include "Network/FeedForwardMomentum.h"

extern FeedForwardMomentum* __Momentum;
extern float __MomentumFactor;

extern void Trainer_SetBPMomentum(FeedForwardMomentum* Dest);
extern void Trainer_SetBPMomentumFactor(float Factor);

#endif
