/*
 *  KIconButton.h
 *  kodisein
 */

#ifndef __KIconButton
#define __KIconButton

#pragma warning(disable:4786)

#include "KButton.h"

enum { ICON_CROSS, ICON_ARROW_UP, ICON_ARROW_DOWN, ICON_ARROW_LEFT, ICON_ARROW_RIGHT, ICON_CLEAR,
        ICON_DOUBLE_DOWN, ICON_DOUBLE_UP, ICON_SINGLE_UP, ICON_SINGLE_DOWN, ICON_BOTTOM, ICON_TOP };

class KIconButton : public KButton
{
    INTROSPECTION

    protected:
    
    int			type;
    
    public:

                        KIconButton		( int );
                    
    virtual void	setType			( int t ) { type = t; }
    virtual int		getType			() const { return type; }
    virtual void	render			();    
};

#endif