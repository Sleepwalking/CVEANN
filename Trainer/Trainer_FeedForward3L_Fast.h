#ifndef TRAINER_FEEDFORWARD3L_FAST_H
#define TRAINER_FEEDFORWARD3L_FAST_H

#include "Network/FeedForward3L_Fast.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForward3L_Fast_BP(FeedForward3L_Fast* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
