/*
 *  KToggleButton.h
 *  kodisein
 */

#ifndef __KToggleButton
#define __KToggleButton

#pragma warning(disable:4786)

#include "KButton.h"

class KToggleButton : public KButton
{
    INTROSPECTION
    
    public:

                        KToggleButton		();

    virtual void	setPicked		( bool );
    virtual void	render			();    
};

#endif