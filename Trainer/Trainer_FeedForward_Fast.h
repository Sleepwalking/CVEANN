#ifndef TRAINER_FEEDFORWARD_FAST_H
#define TRAINER_FEEDFORWARD_FAST_H

#include "Network/FeedForward_Fast.h"
#include "Trainer/Trainer_BPMomentum.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForward_Fast_BP(FeedForward_Fast* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
