#include <stdio.h>
#include "Network/Perceptron.h"
#include "Network/FeedForward.h"
#include "Network/FeedForward_Fast.h"
#include "Network/FeedForwardMomentum.h"
#include "Trainer/Trainer_Perceptron.h"
#include "Trainer/Trainer_FeedForward.h"
#include "Trainer/Trainer_FeedForward_Fast.h"
#include "Test/Formant.h"
#include "Activator.h"

#define TriBP(symbol)\
    E = 0;\
    E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_##symbol##_E2, r##symbol, n);\
    E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_##symbol##_C3, r##symbol, n);\
    E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_##symbol##_G4, r##symbol, n);\
    Max = E > Max ? E : Max

int main(void)
{
    int i;

    int Layers[] = {105, 150, 6};

    FeedForward_Fast fnet;
    FeedForward_Fast_Ctor(& fnet);
    FeedForward_Fast_SetLayer(& fnet, Layers, 3);
    FeedForward_Fast_RandomInit(& fnet, 0.5);

    FeedForwardMomentum fm;
    FeedForwardMomentum_Ctor(& fm);
    FeedForwardMomentum_Construct_Fast(& fm, & fnet);
    FeedForwardMomentum_Clear(& fm);

    Trainer_SetBPMomentum(& fm);
    Trainer_SetBPMomentumFactor(0.2);

    float E;
    for(i = 0; i < 1000; i ++)
    {
        float n = (1.0f - (float)i / 1000) * 1;
        float Max = 0;
        E = 0;
        TriBP(a);
        TriBP(i);
        TriBP(o);
        TriBP(e);
        TriBP(e_);
        TriBP(u);
        E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_u_G3, ru, n);
        Max = E > Max ? E : Max;
        printf("%f\n", Max / 2);
        if(Max / 2 < 0.1)
            break;
    }
    printf("i = %d\n", i);

    FeedForward_Fast_SetInput(& fnet, Spectrum_pu_D3);
    FeedForward_Fast_UpdateState(& fnet);

    printf("%f, %f, %f, %f, %f, %f\n",
           fnet.Layers[fnet.Layers_Index].O[0],
           fnet.Layers[fnet.Layers_Index].O[1],
           fnet.Layers[fnet.Layers_Index].O[2],
           fnet.Layers[fnet.Layers_Index].O[3],
           fnet.Layers[fnet.Layers_Index].O[4],
           fnet.Layers[fnet.Layers_Index].O[5]);

    FeedForwardMomentum_Dtor(& fm);
    FeedForward_Fast_Dtor(& fnet);

    printf("Hello World!\n");
    return 0;
}

