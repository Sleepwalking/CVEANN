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
    return FeedForward_MatchLayer(Src.BaseNet -> Layers + 1,
                                  Src.BaseNet -> Layers[0].O,
                                  Src.BaseNet -> Layers[0].O_Index + 1);
}
