#ifndef LVQ_H
#define LVQ_H

#include "FeedForward.h"
#include "RUtil/RUtil.h"

AutoClass
{
    FeedForward BaseNet;
    ArrayType_Define(int, ClassList);
} EndClass(LVQ);

extern void LVQ_SetLayer(LVQ* Dest, int L1, int L2);
extern void LVQ_SetClass(LVQ* Dest, int From, int To, int L3Class);
extern int LVQ_GetWinnerIndex(LVQ* Src);
extern int LVQ_GetWinner(LVQ* Src);
extern void LVQ_RandomInit(LVQ* Dest, float Range);
extern void LVQ_SetInput(LVQ* Dest, float* Input);

#endif
