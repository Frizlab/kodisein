/*
 *  KSelectable.h
 *  kodisein
 */

#ifndef __KSelectable
#define __KSelectable

#include "KPickable.h"

// --------------------------------------------------------------------------------------------------------

class KSelectable : public KPickable
{
    INTROSPECTION
    
    protected:
    
    bool 				selected;
        
    public:
    
                                        KSelectable		();
                                        
    virtual void			setSelected		( bool s ) { selected = s; }
    virtual bool			isSelected		() const   { return selected; }
    
    virtual bool			isCutCopyPasteable	() const   { return true; }
    virtual string			getPasteBufferString	() const   { return ""; }
};

#endif


