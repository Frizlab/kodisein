/*
 *  KRotationHandle.h
 *  kodisein
 */

#ifndef __KRotationHandle
#define __KRotationHandle

#include "KHandle.h"

class KRotationHandle : public KHandle
{
    INTROSPECTION
    
    public:
    
                                KRotationHandle 	() : KHandle () {}
                                KRotationHandle		( KHandle * p ) : KHandle (p) {}
                                
    virtual void		display 		( int mode );
};

#endif
