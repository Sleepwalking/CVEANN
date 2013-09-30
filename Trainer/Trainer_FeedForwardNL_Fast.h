#ifndef TRAINER_FEEDFORWARDNL_FAST_H
#define TRAINER_FEEDFORWARDNL_FAST_H

#include "Network/FeedForwardNL_Fast.h"
#include "RUtil/RUtil.h"

extern float Trainer_FeedForwardNL_Fast_BP(FeedForwardNL_Fast* Dest, float* Input, float* ExpectedOutput, float Eit);

#endif
