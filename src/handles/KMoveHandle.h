/*
 *  KMoveHandle.h
 *  kodisein
 */

#ifndef __KMoveHandle
#define __KMoveHandle

#include "KHandle.h"

class KMoveHandle : public KHandle
{
    INTROSPECTION
    
    public:
    
                                KMoveHandle 		() : KHandle () {}
                                KMoveHandle		( KHandle * h ) : KHandle(h) {}
                                
    virtual void		display 		( int );
};

#endif
