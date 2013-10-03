#include "LVQ.h"
#include "Rand.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"

_Constructor_ (LVQ)
{
    FeedForward_Ctor(& Dest -> BaseNet);
    ArrayType_Init(int, Dest -> ClassList);
}

_Destructor_ (LVQ)
{
    FeedForward_Dtor(& Dest -> BaseNet);
    ArrayType_Dtor(int, Dest -> ClassList);
}

void LVQ_SetLayer(LVQ* Dest, int L1, int L2)
{
    int LayerSize [] = {L1, L2};
    ArrayType_Resize(int, Dest -> ClassList, L2);
    Dest -> ClassList_Index = L2 - 1;
    FeedForward_SetLayer(& Dest -> BaseNet, LayerSize, 2);
}

void LVQ_SetClass(LVQ* Dest, int From, int To, int L3Class)
{
    int i;
    for(i = From; i <= To; i ++)
        Dest -> ClassList[i] = L3Class;
}

int LVQ_GetWinnerIndex(LVQ* Src)
{
    return FeedForward_MatchLayer(Src -> BaseNet.Layers + 1,
                                  Src -> BaseNet.Layers[0].O,
                                  Src -> BaseNet.Layers[0].O_Index + 1);
}

int LVQ_GetWinner(LVQ* Src)
{
    return Src -> ClassList[LVQ_GetWinnerIndex(Src)];
}

void LVQ_RandomInit(LVQ* Dest, float Range)
{
    FeedForward_RandomInit(& Dest -> BaseNet, Range);
}

void LVQ_SetInput(LVQ* Dest, float* Input)
{
    Boost_FloatCopy(Dest -> BaseNet.Layers[0].O, Input, Dest -> BaseNet.Layers[0].O_Index + 1);
}
