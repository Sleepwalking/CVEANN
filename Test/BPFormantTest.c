#include "BPFormantTest.h"
#include <stdio.h>
#include "Network/FeedForward.h"
#include "Network/FeedForwardMomentum.h"
#include "Trainer/Trainer_FeedForward.h"
#include "AFormant.h"
#include "Activator.h"
#include "Rand.h"

//E += Trainer_FeedForward_BP(& fnet, Spectrum_##symbol##_E2, r##symbol, n);
#define TriBP(symbol)\
    E = 0;\
    E += Trainer_FeedForward_BP(& fnet, Spectrum_##symbol##_C3, r##symbol, n);\
    E += Trainer_FeedForward_BP(& fnet, Spectrum_##symbol##_G4, r##symbol, n);\
    Max = E > Max ? E : Max

void Test_BPFormantTest()
{
    int i;
    int Layers[] = {105, 130, 6};

    FeedForward fnet;
    FeedForward_Ctor(& fnet);
    FeedForward_SetLayer(& fnet, Layers, 3);
    FeedForward_RandomInit(& fnet, 0.5);

    FeedForwardMomentum fm;
    FeedForwardMomentum_Ctor(& fm);
    FeedForwardMomentum_Construct(& fm, & fnet);
    FeedForwardMomentum_Clear(& fm);

    Trainer_SetBPMomentum(& fm);
    Trainer_SetBPMomentumFactor(0.5);

    float E;
    float n = 0.2;
    int x = 4;
    //FeedForward_Fast_RandomInit(& fnet, 0.5);
    //for(x = 0; x < 10; x ++)
    {
        float Max = 0;
        FeedForward_RandomInit(& fnet, x * 0.1 + 0.1);
        //n = x * 0.1 + 0.1;
        for(i = 0; i < 10000; i ++)
        {
            Max = 0;
            E = 0;
            TriBP(i);
            TriBP(u);
            E += Trainer_FeedForward_BP(& fnet, Spectrum_u_G3, ru, n);
            TriBP(a);
            TriBP(e_);
            TriBP(o);
            TriBP(e);
            Max = E > Max ? E : Max;
            printf("%f\n", Max / 2);
        }

        printf("W = %f, E = %f\n", x * 0.1 + 0.1, Max / 2);
        FeedForward_SetInput(& fnet, Spectrum_pu_E3);
        FeedForward_UpdateState(& fnet);

        printf("\t\t\t%f, %f, %f, %f, %f, %f\n",
               fnet.Layers[fnet.Layers_Index].O[0],
               fnet.Layers[fnet.Layers_Index].O[1],
               fnet.Layers[fnet.Layers_Index].O[2],
               fnet.Layers[fnet.Layers_Index].O[3],
               fnet.Layers[fnet.Layers_Index].O[4],
               fnet.Layers[fnet.Layers_Index].O[5]);
    }


    FeedForwardMomentum_Dtor(& fm);
    FeedForward_Dtor(& fnet);
}
