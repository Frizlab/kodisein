/*
 *  KOneDirectionHandle.h
 *  kodisein
 */

#ifndef __KOneDirectionHandle
#define __KOneDirectionHandle

#include "KHandle.h"

class KOneDirectionHandle : public KHandle
{
    INTROSPECTION
    
    public:
    
                                KOneDirectionHandle 	() : KHandle () {}
                                KOneDirectionHandle	( KHandle * p ) : KHandle (p) {}
                                
    virtual void		display 		( int mode );
};

#endif
