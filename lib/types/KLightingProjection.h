/*
 *  KLightingProjection.h
 *  kodisein
 */

#ifndef __KLightingProjection
#define __KLightingProjection

#pragma warning(disable:4786)

#include "KPerspectiveProjection.h"

// --------------------------------------------------------------------------------------------------------
class KLightingProjection : public KPerspectiveProjection
{
    INTROSPECTION
    
    protected:
    
    public:
                                KLightingProjection 	( GLfloat = 60.0, GLfloat = 0.1, GLfloat = 300.0 );
                                KLightingProjection 	( const KProjection & );
                        
    virtual KProjection *	copy			() const;
    virtual void 		apply			();
};

#endif

