/*
 *  KOrthographicProjection.h
 *  kodisein
 */

#ifndef __KOrthographicProjection
#define __KOrthographicProjection

#pragma warning(disable:4786)

#include "KProjection.h"

// --------------------------------------------------------------------------------------------------------
class KOrthographicProjection : public KProjection
{
    INTROSPECTION
    
    public:
                                KOrthographicProjection ( GLfloat = -1.0, GLfloat = 1.0 );
                                KOrthographicProjection ( const KProjection & );
                        
    virtual KProjection *	copy			() const;
    virtual void		apply			();
};

#endif
