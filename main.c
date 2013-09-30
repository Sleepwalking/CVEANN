#include <stdio.h>
#include "Network/Perceptron.h"
#include "Network/FeedForward3L.h"
#include "Network/FeedForward3L_Fast.h"
#include "Network/FeedForwardNL.h"
#include "Network/FeedForwardNL_Fast.h"
#include "Trainer/Trainer_Perceptron.h"
#include "Trainer/Trainer_FeedForward3L.h"
#include "Trainer/Trainer_FeedForward3L_Fast.h"
#include "Trainer/Trainer_FeedForwardNL.h"
#include "Trainer/Trainer_FeedForwardNL_Fast.h"
#include "Test/Formant.h"
#include "Activator.h"
/*
#define TriBP(symbol)\
    E += Trainer_FeedForward3L_Fast_BP(& ftest, Spectrum_##symbol##_E2, r##symbol, n);\
    E += Trainer_FeedForward3L_Fast_BP(& ftest, Spectrum_##symbol##_C3, r##symbol, n);\
    E += Trainer_FeedForward3L_Fast_BP(& ftest, Spectrum_##symbol##_G4, r##symbol, n)

*/
#define TriBP(symbol)\
    E += Trainer_FeedForwardNL_Fast_BP(& fnet, Spectrum_##symbol##_E2, r##symbol, n);\
    E += Trainer_FeedForwardNL_Fast_BP(& fnet, Spectrum_##symbol##_C3, r##symbol, n);\
    E += Trainer_FeedForwardNL_Fast_BP(& fnet, Spectrum_##symbol##_G4, r##symbol, n)

int main(void)
{
    int i;

    int Layers[] = {105, 150, 6};

    FeedForwardNL_Fast fnet;
    FeedForwardNL_Fast_Ctor(& fnet);
    FeedForwardNL_Fast_SetLayer(& fnet, Layers, 3);
    FeedForwardNL_Fast_RandomInit(& fnet, 0.5);

    float E;
    for(i = 0; i < 1000; i ++)
    {
        float n = (1.0f - (float)i / 1000) * 1;
        E = 0;
        TriBP(a);
        TriBP(i);
        TriBP(o);
        TriBP(e);
        TriBP(e_);
        TriBP(u);
        E += Trainer_FeedForwardNL_Fast_BP(& fnet, Spectrum_u_G3, ru, n);
        printf("%f\n", E / 2);
    }
    printf("%f\n", E / 2);

    for(i = 0; i < 105; i ++)
    {
        fnet.Layers[0].O[i] = Spectrum_pu_D3[i];
    }

    FeedForwardNL_Fast_UpdateState(& fnet);

    printf("%f, %f, %f, %f, %f, %f\n",
           fnet.Layers[fnet.Layers_Index].O[0],
           fnet.Layers[fnet.Layers_Index].O[1],
           fnet.Layers[fnet.Layers_Index].O[2],
           fnet.Layers[fnet.Layers_Index].O[3],
           fnet.Layers[fnet.Layers_Index].O[4],
           fnet.Layers[fnet.Layers_Index].O[5]);

    FeedForwardNL_Fast_Dtor(& fnet);
/*

    FeedForward3L_Fast ftest;
    FeedForward3L_Fast_Ctor(& ftest);
    FeedForward3L_Fast_SetLayer(& ftest, 105, 150, 6);
    FeedForward3L_Fast_RandomInit(& ftest, 0.4);

    float E;
    for(i = 0; i < 1000; i ++)
    {
        float n = (1.0f - (float)i / 1000) * 1;
        E = 0;
        TriBP(a);
        TriBP(i);
        TriBP(o);
        TriBP(e);
        TriBP(e_);
        TriBP(u);
        E += Trainer_FeedForward3L_Fast_BP(& ftest, Spectrum_u_G3, ru, n);
        printf("%f\n", E / 2);
    }
    printf("%f\n", E / 2);

    for(i = 0; i < 105; i ++)
    {
        ftest.X[i] = Spectrum_pu_E3[i];
    }
    FeedForward3L_Fast_UpdateState(& ftest);

    printf("%f, %f, %f, %f, %f, %f\n",
           ftest.O[0],
           ftest.O[1],
           ftest.O[2],
           ftest.O[3],
           ftest.O[4],
           ftest.O[5]);

    FeedForward3L_Fast_Dtor(& ftest);
    */
    printf("Hello World!\n");
    return 0;
}

