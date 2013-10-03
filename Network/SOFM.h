#ifndef SOFM_H
#define SOFM_H

#include "FeedForward.h"
#include "RUtil/RUtil.h"

typedef struct
{
    FeedForward* BaseNet;
    int Width;
    int Height;
} SOFMDescriptor;

extern SOFMDescriptor SOFM_FromFeedForward(FeedForward* Base, int _Width, int _Height);

extern int SOFM_GetWinnerIndex(SOFMDescriptor Src);

#define SOFM_Index(Src, X, Y)\
    ((X) + (Y) * (Src).Width)

#define SOFM_X(Src, Index)\
    ((Index) % (Src).Width)

#define SOFM_Y(Src, Index)\
    ((Index) / (Src).Width)

#endif
