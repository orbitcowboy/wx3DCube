#ifndef __CUBEDLGApp_h__
#define __CUBEDLGApp_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#else
#include <wx/wxprec.h>
#endif

class CubeDlgApp : public wxApp
{
    public:
        bool OnInit();
        int OnExit();
};

#endif // __CUBEDLGApp_h__
