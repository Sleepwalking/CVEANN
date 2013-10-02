#ifndef TRAINER_SOFM_H
#define TRAINER_SOFM_H

#include "Network/SOFM.h"
#include "RUtil/RUtil.h"

extern void Trainer_Organize(float* Dest, int Length);
extern void Trainer_SOFM(SOFMDescriptor Dest, float* Input, float Eit, float Radius);

#endif
