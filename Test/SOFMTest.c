#include "SOFMTest.h"
#include <stdio.h>
#include "Network/FeedForward.h"
#include "Network/FeedForwardMomentum.h"
#include "Network/SOFM.h"
#include "Trainer/Trainer_FeedForward.h"
#include "Trainer/Trainer_SOFM.h"
#include "AFormant.h"
#include "Activator.h"
#include "Rand.h"

void Test_SOFMTest()
{
    int i;
    int Layers[] = {105, 100};
    FeedForward FNet;
    FeedForward_Ctor(& FNet);
    FeedForward_SetLayer(& FNet, Layers, 2);
    FeedForward_RandomInit(& FNet, 0);

    SOFMDescriptor SNet = SOFM_FromFeedForward(& FNet, 10, 10);
    /*
    float a [] = {0.1, 0.5, 0.5, 0.3, 0.2, 0.1, 0.1, 0.1};
    float b [] = {0.1, 0.2, 0.5, 0.4, 0.2, 0.1, 0.1, 0.1};
    float c [] = {0.1, 0.1, 0.2, 0.4, 0.5, 0.3, 0.2, 0.1};
    float d [] = {0.1, 0.1, 0.1, 0.3, 0.6, 0.2, 0.1, 0.1};
    float e [] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.3, 0.5, 0.4};
    float f [] = {0.1, 0.1, 0.1, 0.1, 0.2, 0.4, 0.6, 0.3};*/

    float r = 6;
    for(i = 0; i < 1000; i ++)
    {
        float n = 0.5 - (float)i / 2000;

        Trainer_SOFM(SNet, Spectrum_a_C3, n, r);
        Trainer_SOFM(SNet, Spectrum_pa_G3, n, r);
        Trainer_SOFM(SNet, Spectrum_o_C3, n, r);
        Trainer_SOFM(SNet, Spectrum_e_C3, n, r);
        Trainer_SOFM(SNet, Spectrum_pe_F3, n, r);
        Trainer_SOFM(SNet, Spectrum_e__C3, n, r);
        Trainer_SOFM(SNet, Spectrum_i_C3, n, r);
        Trainer_SOFM(SNet, Spectrum_pi_F3, n, r);
        Trainer_SOFM(SNet, Spectrum_u_C3, n, r);
        /*
        Trainer_SOFM(SNet, a, n, r);
        Trainer_SOFM(SNet, b, n, r);
        Trainer_SOFM(SNet, c, n, r);
        Trainer_SOFM(SNet, d, n, r);
        Trainer_SOFM(SNet, e, n, r);
        Trainer_SOFM(SNet, f, n, r);*/
        printf("%f\n", n);
    }

    FeedForward_SetInput(& FNet, Spectrum_pu_E3);
    i = SOFM_GetWinnerIndex(SNet);
    printf("x = %d, y = %d\n", SOFM_X(SNet, i), SOFM_Y(SNet, i));

    FeedForward_Dtor(& FNet);
}

/*
Trainer_SOFM(SNet, Spectrum_a_C3, n, 3.5);
Trainer_SOFM(SNet, Spectrum_o_C3, n, 3.5);
Trainer_SOFM(SNet, Spectrum_e_C3, n, 3.5);
Trainer_SOFM(SNet, Spectrum_e__C3, n, 3.5);
Trainer_SOFM(SNet, Spectrum_i_C3, n, 3.5);
Trainer_SOFM(SNet, Spectrum_u_C3, n, 3.5);*/
