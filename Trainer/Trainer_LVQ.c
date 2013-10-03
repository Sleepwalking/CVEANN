#include "Trainer_LVQ.h"
#include "Trainer_FeedForward.h"
#include "Rand.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include <malloc.h>

void Trainer_LVQ(LVQ* Dest, float* Input, int ExpectedOutput, float Eit)
{
    int Winner;
    LVQ_SetInput(Dest, Input);
    Winner = Trainer_FFMatchWinner(& Dest -> BaseNet);
    int LayerSize = Dest -> BaseNet.Layers[0].O_Index;
    float* Tmp = (float*)malloc(sizeof(float) * (LayerSize + 1));

    printf("Winner: %d\n", Winner);

    Boost_FloatCopy(Tmp, Dest -> BaseNet.Layers[1].W[Winner], LayerSize + 1);
    Boost_FloatSubArr(Tmp, Dest -> BaseNet.Layers[0].O, Tmp, LayerSize + 1);
    if(Dest -> ClassList[Winner] == ExpectedOutput)
    {
        // w + n(x - w)
        Boost_FloatMul(Tmp, Tmp, Eit, LayerSize + 1);
    }else
    {
        // w - n(x - w)
        Boost_FloatMul(Tmp, Tmp, - Eit, LayerSize + 1);
    }
    Boost_FloatAddArr(Dest -> BaseNet.Layers[1].W[Winner], Dest -> BaseNet.Layers[1].W[Winner], Tmp, LayerSize + 1);

    free(Tmp);
}
