#include "Neuron.h"
#define nNeuron_Verbose

_Constructor_ (Neuron)
{
    ArrayType_Init(Neuron*, Dest -> Input);
    ArrayType_Init(float, Dest -> Weight);
    Dest -> ActivationFunc = Activator_Sigmoid;
    Dest -> Type = NType_Neuron;
#ifdef Neuron_Verbose
    printf("Neuron %x constructed.\n", (int)Dest);
#endif
}

_Destructor_ (Neuron)
{
    ArrayType_Dtor(Neuron*, Dest -> Input);
    ArrayType_Dtor(float, Dest -> Weight);
#ifdef Neuron_Verbose
    printf("Neuron %x destructed.\n", (int)Dest);
#endif
}

int Neuron_ConnectFrom(Neuron* Dest, Neuron* From)
{
    int i;
    for(i = 1; i <= Dest -> Input_Index; i ++)
        if(Dest -> Input[i] == From)
            return i;
    ArrayType_Push(Neuron*, Dest -> Input, From);
    ArrayType_Push(float, Dest -> Weight, 0);
#ifdef Neuron_Verbose
    printf("Neuron %x connected to %x at index %d.\n", (int)From, (int)Dest, Dest -> Input_Index);
#endif
    return Dest -> Input_Index;
}

int Neuron_DisconnectFrom(Neuron* Dest, Neuron* From)
{
    int i;
    for(i = 1; i <= Dest -> Input_Index; i ++)
        if(Dest -> Input[i] == From)
        {
            ArrayType_Remove(Neuron*, Dest -> Input, i);
            ArrayType_Remove(float*, Dest -> Weight, i);
#ifdef Neuron_Verbose
            printf("Neuron %x disconnected to %x.\n", (int)From, (int)Dest);
#endif
            return 1;
        }
    return 0;
}

float Neuron_UpdateState(Neuron* Dest)
{
    int i;
    if(Dest -> Type != NType_Input)
    {
        Dest -> NetOutput = 0;
        for(i = 0; i <= Dest -> Input_Index; i ++)
        {
            Dest -> NetOutput += (Dest -> Input[i] -> Output) * (Dest -> Weight[i]);
        }
        Dest -> Output = Dest -> ActivationFunc(Dest -> NetOutput);
    }else
    {
        Dest -> NetOutput = Dest -> InputVal;
        Dest -> Output = Dest -> InputVal;
    }
#ifdef Neuron_Verbose
    printf("Neuron %x output: %f, net output: %f.\n", (int)Dest, Dest -> Output, Dest -> NetOutput);
#endif
    return Dest -> Output;
}
