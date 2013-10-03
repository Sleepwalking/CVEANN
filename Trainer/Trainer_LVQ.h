#ifndef TRAINER_LVQ_H
#define TRAINER_LVQ_H

#include "Network/FeedForward.h"
#include "Network/LVQ.h"

extern void Trainer_LVQ(LVQ* Dest, float* Input, int ExpectedOutput, float Eit);

#endif
