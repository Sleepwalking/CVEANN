#include "Activator.h"
#include <math.h>
#include <malloc.h>
#define E 2.718281828459
#define SIG_TABLE_MAXIMUM 50.0f
#define SIG_TABLE_SIZE 100000.0f
float* SigmoidTable = 0;
float SigmoidStretch = 1;

float Activator_SigmoidBase(float Input);
void Sigmoid_Init()
{
    int i;
    float factor = SIG_TABLE_MAXIMUM / SIG_TABLE_SIZE;
    if(SigmoidTable == 0)
    {
        SigmoidTable = (float*)malloc(SIG_TABLE_SIZE * sizeof(float));
        for(i = 0;i < SIG_TABLE_SIZE;i ++)
            SigmoidTable[i] = Activator_SigmoidBase(i * factor - 0.5 * SIG_TABLE_MAXIMUM);
    }
}

void Sigmoid_Exit()
{
    if(SigmoidTable != 0)
    {
        free(SigmoidTable);
    }
}

float Activator_Step(float Input)
{
    if(Input > 0)
        return 1;
    else
        return 0;
}

float Activator_Sgn(float Input)
{
    if(Input > 0)
        return 1;
    else
        return - 1;
}

float Activator_SigmoidBase(float Input)
{
    return 1.0f / (1.0f + pow(E, - Input));
}

float Activator_Sigmoid(float Input)
{
    float val;
    int index;
    Input /= SigmoidStretch;
    if(Input < - SIG_TABLE_MAXIMUM / 2 || Input > SIG_TABLE_MAXIMUM / 2)
        return Activator_SigmoidBase(Input);
    val = Input * SIG_TABLE_SIZE / SIG_TABLE_MAXIMUM + SIG_TABLE_SIZE / 2;
    index = (int)val;
    return
        SigmoidTable[index] * (1 - val + index) +
        SigmoidTable[index + 1] * (val - index);
}

float Activator_TanSigmoid(float Input)
{
    Input /= SigmoidStretch;
    return 2.0f / (1.0f + pow(E, - Input)) - 1.0f;
}

float Activator_DSigmoid(float Input)
{
    return Activator_Sigmoid(Input) * (1.0f - Activator_Sigmoid(Input));
}

float Activator_DTanSigmoid(float Input)
{
    return Activator_Sigmoid(Input) * (1.0f - Activator_Sigmoid(Input)) * 2.0f;
}

void Activator_SetSigmoidStretch(float Ratio)
{
    SigmoidStretch = Ratio;
}
