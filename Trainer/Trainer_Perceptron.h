#ifndef TRAINER_PERCEPTRON_H
#define TRAINER_PERCEPTRON_H

#include "Network/Perceptron.h"
#include "RUtil/RUtil.h"

extern void Trainer_Perceptron_Hebb(Perceptron* Dest, float* Input, float Eit);
extern void Trainer_Perceptron_Rosenblatt(Perceptron* Dest, float* Input, float ExpectedOutput, float Eit);
extern void Trainer_Perceptron_Delt(Perceptron* Dest, float* Input, float ExpectedOutput, float Eit);
extern void Trainer_Perceptron_LMS(Perceptron* Dest, float* Input, float ExpectedOutput, float Eit);

#endif
