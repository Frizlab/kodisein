/*
 *  KTwoDirectionHandle.h
 *  kodisein
 */

#ifndef __KTwoDirectionHandle
#define __KTwoDirectionHandle

#include "KHandle.h"

class KTwoDirectionHandle : public KHandle
{
    INTROSPECTION
    
    public:
    
                                KTwoDirectionHandle 	() : KHandle () {}
                                KTwoDirectionHandle	( KHandle * p ) : KHandle (p) {}
                                
    virtual void		display 		( int mode );
};

#endif
