/*
 *  KIconButton.cpp
 *  kodisein
 */

#include "KIconButton.h"
#include "KColor.h"
#include "KTools.h"
#include "KButtonSymbols.h"

KDL_CLASS_INTROSPECTION_1 (KIconButton, KButton)

// --------------------------------------------------------------------------------------------------------
KIconButton::KIconButton ( int t ) : KButton ()
{
    size.w	= 14;
    size.h	= 14;
    type	= t;
}

// --------------------------------------------------------------------------------------------------------
void KIconButton::render ()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);

    if (getFGColor()) getFGColor()->glColor();
    
    KWidget::render();
    
    KPosition iconPos(1, -size.h);
    switch (type)
    {
        case ICON_CROSS: 	kDisplayXPMIcon (KDS_BUTTONICON_CROSS,		iconPos); break;
        case ICON_ARROW_UP: 	kDisplayXPMIcon (KDS_BUTTONICON_ARROW_UP,	iconPos); break;
        case ICON_ARROW_DOWN: 	kDisplayXPMIcon (KDS_BUTTONICON_ARROW_DOWN,	iconPos); break;
        case ICON_ARROW_LEFT: 	kDisplayXPMIcon (KDS_BUTTONICON_ARROW_LEFT,	iconPos); break;
        case ICON_ARROW_RIGHT: 	kDisplayXPMIcon (KDS_BUTTONICON_ARROW_RIGHT,	iconPos); break;
        case ICON_SINGLE_UP: 	kDisplayXPMIcon (KDS_BUTTONICON_UP,		iconPos); break;
        case ICON_SINGLE_DOWN: 	kDisplayXPMIcon (KDS_BUTTONICON_DOWN,		iconPos); break;
        case ICON_DOUBLE_UP: 	kDisplayXPMIcon (KDS_BUTTONICON_DOUBLE_UP,	iconPos); break;
        case ICON_DOUBLE_DOWN: 	kDisplayXPMIcon (KDS_BUTTONICON_DOUBLE_DOWN,	iconPos); break;
        case ICON_TOP: 		kDisplayXPMIcon (KDS_BUTTONICON_TOP,		iconPos); break;
        case ICON_BOTTOM: 	kDisplayXPMIcon (KDS_BUTTONICON_BOTTOM,		iconPos); break;
        case ICON_CLEAR: 	kDisplayXPMIcon (KDS_BUTTONICON_CLEAR,		iconPos); break;
        default: break;
    };

    glPopAttrib();
}

