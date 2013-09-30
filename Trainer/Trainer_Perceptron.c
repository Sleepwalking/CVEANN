#include "Trainer_Perceptron.h"
#include "Activator.h"

float Eval_Perceptron(Perceptron* Dest, float* Input)
{
    int i;
    Dest -> NetOutput = 0;
    for(i = 0; i <= Dest -> Input_Index; i ++)
        Dest -> NetOutput += Input[i] * Dest -> Weight[i];
    Dest -> Output = Dest -> ActivationFunc(Dest -> NetOutput);
    return Dest -> Output;
}

void Trainer_Perceptron_Hebb(Perceptron* Dest, float* Input, float Eit)
{
    int i;
    float r = Eval_Perceptron(Dest, Input);
    for(i = 0; i <= Dest -> Input_Index; i ++)
        Dest -> Weight[i] += Eit * r * Input[i];
}

void Trainer_Perceptron_Rosenblatt(Perceptron* Dest, float* Input, float ExpectedOutput, float Eit)
{
    int i;
    float r = ExpectedOutput - Eval_Perceptron(Dest, Input);
    for(i = 0; i <= Dest -> Input_Index; i ++)
        Dest -> Weight[i] += Eit * r * Input[i];
}

void Trainer_Perceptron_Delt(Perceptron* Dest, float* Input, float ExpectedOutput, float Eit)
{
    int i;
    Activator ADash;
    if(Dest -> ActivationFunc == Activator_Sigmoid)
        ADash = Activator_DSigmoid;
    if(Dest -> ActivationFunc == Activator_TanSigmoid)
        ADash = Activator_DTanSigmoid;
    float r = (ExpectedOutput - Eval_Perceptron(Dest, Input));
    r *= ADash(Dest -> NetOutput);
    for(i = 0; i <= Dest -> Input_Index; i ++)
        Dest -> Weight[i] += Eit * r * Input[i];
}

void Trainer_Perceptron_LMS(Perceptron* Dest, float* Input, float ExpectedOutput, float Eit)
{
    int i;
    Eval_Perceptron(Dest, Input);
    float r = ExpectedOutput - Dest -> NetOutput;
    for(i = 0; i <= Dest -> Input_Index; i ++)
        Dest -> Weight[i] += Eit * r * Input[i];
}
