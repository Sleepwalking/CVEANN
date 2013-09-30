#ifndef NEURON_H
#define NEURON_H

#include "Activator.h"
#include "RUtil/RUtil.h"

typedef enum
{
    NType_Neuron = 0,
    NType_Input = 1,
    NType_Output = 2
} NeuronType;

typedef struct Neuron Neuron;
struct Neuron
{
    ArrayType_Define(float, Weight);
    ArrayType_Define(Neuron*, Input);

    float Output;
    float NetOutput;
    Activator ActivationFunc;

    NeuronType Type;
    float InputVal;
};

extern void Neuron_Ctor(Neuron* Dest);
extern void Neuron_Dtor(Neuron* Dest);

/* "Dest" here means the Neuron to be operated on. */
extern int Neuron_ConnectFrom(Neuron* Dest, Neuron* From);
extern int Neuron_DisconnectFrom(Neuron* Dest, Neuron* From);
extern float Neuron_UpdateState(Neuron* Dest);

#endif
