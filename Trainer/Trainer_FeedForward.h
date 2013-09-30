#ifndef TRAINER_FEEDFORWARD_H
#define TRAINER_FEEDFORWARD_H

#include "Network/FeedForward.h"
#include "Trainer/Trainer_BPMomentum.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForward_BP(FeedForward* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
