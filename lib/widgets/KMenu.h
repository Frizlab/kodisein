/*
 *  KMenu.h
 *  kodisein
 */

#ifndef __KMenu
#define __KMenu

#pragma warning(disable:4786)

#define KDL_MENU_DEFAULT_ITEM_HEIGHT		25

#include "KWidgetArray.h"
#include "KKeyRecorder.h"

class KMenu : public KWidgetArray
{   
    INTROSPECTION
        
    public:
    
    static KKeyRecorder	shortcut_recorder;
    static bool		show_shortcuts;

                        KMenu 			();

    virtual void	close 			();
    
    virtual string	getXML 			( int = 0 ) const;
    virtual void	setXML			( string & );
};

#endif