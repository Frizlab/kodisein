/*
 *  KParticle.h
 *  kodisein
 */

#ifndef __KParticle
#define __KParticle

#include "KMatrix.h"

class KParticle : public KMatrix
{
    INTROSPECTION
    
    protected:
    
    int		birth_time;
    
    public:
    
                KParticle 	();
    int		getAge 		( int now ) { return (now - birth_time); }
};

#endif
