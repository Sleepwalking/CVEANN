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
#include "Rand.h"

//E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_##symbol##_E2, r##symbol, n);
#define TriBP(symbol)\
    E = 0;\
    E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_##symbol##_C3, r##symbol, n);\
    E += Trainer_FeedForward_Fast_BP(& fnet, Spectrum_##symbol##_G4, r##symbol, n);\
    Max = E > Max ? E : Max

int main(void)
{
    int i;

    int Layers[] = {105, 6};

    FeedForward_Fast fnet;
    FeedForward_Fast_Ctor(& fnet);
    FeedForward_Fast_SetLayer(& fnet, Layers, 2);
    FeedForward_Fast_RandomInit(& fnet, 0.5);

    FeedForwardMomentum fm;
    FeedForwardMomentum_Ctor(& fm);
    FeedForwardMomentum_Construct_Fast(& fm, & fnet);
    FeedForwardMomentum_Clear(& fm);

    float E;
    float n = 0.2;
    int x;
    FeedForward_Fast_RandomInit(& fnet, 0.5);
    for(x = 0; x < 10; x ++)
    {
        float Max = 0;
        FeedForward_Fast_RandomInit(& fnet, x * 0.1 + 0.1);
        //n = x * 0.1 + 0.1;
        n = 0.2;
        for(i = 0; i < 3000; i ++)
        {
            Max = 0;
            E = 0;
            TriBP(i);
            TriBP(u);
            TriBP(a);
            TriBP(e_);
            TriBP(o);
            TriBP(e);
            Max = E > Max ? E : Max;
        }

        printf("W = %f, E = %f\n", x * 0.1 + 0.1, Max / 2);
        FeedForward_Fast_SetInput(& fnet, Spectrum_pu_E3);
        FeedForward_Fast_UpdateState(& fnet);

        printf("\t\t\t%f, %f, %f, %f, %f, %f\n",
               fnet.Layers[fnet.Layers_Index].O[0],
               fnet.Layers[fnet.Layers_Index].O[1],
               fnet.Layers[fnet.Layers_Index].O[2],
               fnet.Layers[fnet.Layers_Index].O[3],
               fnet.Layers[fnet.Layers_Index].O[4],
               fnet.Layers[fnet.Layers_Index].O[5]);
    }


    FeedForwardMomentum_Dtor(& fm);
    FeedForward_Fast_Dtor(& fnet);

    printf("Hello World!\n");
    return 0;
}

