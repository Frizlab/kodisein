/*
 *  KScaleHandle.h
 *  kodisein
 */

#ifndef __KScaleHandle
#define __KScaleHandle

#include "KHandle.h"

class KScaleHandle : public KHandle
{
    INTROSPECTION
    
    public:
    
                                KScaleHandle 		() : KHandle () {}
                                KScaleHandle		( KHandle * p ) : KHandle (p) {}
                                
    virtual void		display 		( int mode );
};

#endif
