/*
 *  KMessagePanel.h
 *  kodisein
 */

#ifndef __KMessagePanel
#define __KMessagePanel

#pragma warning(disable:4786)

#include "KWindow.h"

class KMessagePanel : public KWindow
{
    public:
                        KMessagePanel 	( const string & title, const string & message );
    static void 	displayMessage	( const string & title, const string & message );
    void		close		();
};

#endif