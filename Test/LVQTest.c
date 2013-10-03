#include "LVQTest.h"
#include <stdio.h>
#include "Network/FeedForward.h"
#include "Network/FeedForwardMomentum.h"
#include "Network/LVQ.h"
#include "Trainer/Trainer_FeedForward.h"
#include "Trainer/Trainer_LVQ.h"
#include "AFormant.h"
#include "Activator.h"
#include "Rand.h"

void Test_LVQTest()
{
    int i;

    LVQ LNet;
    LVQ_Ctor(& LNet);

    LVQ_SetLayer(& LNet, 8, 20);
    LVQ_SetClass(& LNet, 0, 6, 0);
    LVQ_SetClass(& LNet, 7, 13, 1);
    LVQ_SetClass(& LNet, 14, 19, 2);

    LVQ_RandomInit(& LNet, 0);

    float a [] = {0.1, 0.5, 0.5, 0.3, 0.2, 0.1, 0.1, 0.1};
    float b [] = {0.1, 0.2, 0.5, 0.4, 0.2, 0.1, 0.1, 0.1};
    float c [] = {0.1, 0.1, 0.2, 0.4, 0.5, 0.3, 0.2, 0.1};
    float d [] = {0.1, 0.1, 0.1, 0.3, 0.6, 0.2, 0.1, 0.1};
    float e [] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.3, 0.5, 0.4};
    float f [] = {0.1, 0.1, 0.1, 0.1, 0.2, 0.4, 0.6, 0.3};

    float g [] = {0.1, 0.2, 0.0, 0.2, 0.1, 0.2, 0.8, 0.2};

    float n = 0.3;
    for(i = 0; i < 100; i ++)
    {
        printf("Round %d\n", i);
        Trainer_LVQ(& LNet, a, 1, n);
        Trainer_LVQ(& LNet, b, 1, n);
        Trainer_LVQ(& LNet, c, 0, n);
        Trainer_LVQ(& LNet, d, 0, n);
        Trainer_LVQ(& LNet, e, 2, n);
        Trainer_LVQ(& LNet, f, 2, n);
    }

    LVQ_SetInput(& LNet, c);
    int Winner = LVQ_GetWinner(& LNet);

    printf("%d\n", Winner);


    LVQ_SetInput(& LNet, g);
    Winner = LVQ_GetWinner(& LNet);

    printf("%d\n", Winner);


    LVQ_Dtor(& LNet);
}
