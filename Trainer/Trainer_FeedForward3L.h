#ifndef TRAINER_FEEDFORWARD3L_H
#define TRAINER_FEEDFORWARD3L_H

#include "Network/FeedForward3L.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForward3L_BP(FeedForward3L* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
