#ifndef TRAINER_FEEDFORWARDNL_H
#define TRAINER_FEEDFORWARDNL_H

#include "Network/FeedForwardNL.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForwardNL_BP(FeedForwardNL* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
