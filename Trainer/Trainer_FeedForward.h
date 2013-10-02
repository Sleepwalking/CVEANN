#ifndef TRAINER_FEEDFORWARD_FAST_H
#define TRAINER_FEEDFORWARD_FAST_H

#include "Trainer/Trainer_BPMomentum.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForward_BP(FeedForward* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
