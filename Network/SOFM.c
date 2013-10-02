#include "SOFM.h"

SOFMDescriptor SOFM_FromFeedForward(FeedForward* Base, int _Width, int _Height)
{
    SOFMDescriptor Ret;
    Ret.BaseNet = Base;
    Ret.Width = _Width;
    Ret.Height = _Height;
    return Ret;
}

int SOFM_GetWinnerIndex(SOFMDescriptor Src)
{
    int i;
    int Record = - 1;
    float Max = - 999;
    for(i = 0; i <= Src.BaseNet -> Layers[1].O_Index; i ++)
        if(Src.BaseNet -> Layers[1].O[i] > Max)
        {
           Max = Src.BaseNet -> Layers[1].O[i];
           Record = i;
        }
    return Record;
}

int SOFM_UpdateState(SOFMDescriptor Dest)
{
    FeedForward_UpdateState(Dest.BaseNet);
    return SOFM_GetWinnerIndex(Dest);
}
