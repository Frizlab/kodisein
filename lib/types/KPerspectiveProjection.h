/*
 *  KPerspectiveProjection.h
 *  kodisein
 */

#ifndef __KPerspectiveProjection
#define __KPerspectiveProjection

#pragma warning(disable:4786)

#include "KProjection.h"

// --------------------------------------------------------------------------------------------------------
class KPerspectiveProjection : public KProjection
{
    INTROSPECTION
    
    public:
                                KPerspectiveProjection 	( GLfloat = 60.0, GLfloat = 0.1, GLfloat = 300.0 );
                                KPerspectiveProjection  ( const KProjection & );
                        
    virtual KProjection *	copy			() const;
    virtual void 		apply			();

    virtual void		focusOn			( const KVector & );
    virtual void 		rotate			( const GLfloat, const GLfloat, const GLfloat );

    virtual void		reset			();
    
    virtual KVector 		getLookAtPosition	() const;
    virtual void		setEyeDistance		( GLfloat );

    virtual string		getXML 			( int = 0 ) const;
    virtual void		setXML			( string & );
};

#endif

