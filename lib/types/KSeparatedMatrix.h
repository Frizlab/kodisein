/*
 *  KSeparatedMatrix.h
 *  kodisein
 */

#ifndef __KSeparatedMatrix
#define __KSeparatedMatrix

#pragma warning(disable:4786)

#include "KMatrix.h"

class KSeparatedMatrix : public KMatrix
{
    INTROSPECTION
    
    protected:
    
    GLfloat			scl[3];
    GLfloat			rot[3];

    public:
    
                                KSeparatedMatrix 	();
                                KSeparatedMatrix 	( const KSeparatedMatrix & object );
                                
    virtual void		operator=		( const KSeparatedMatrix & );
    virtual void		operator=		( const KMatrix & );
    virtual void		reset			();
    
    virtual void		scale			( const GLfloat x, 
                                                          const GLfloat y, 
                                                          const GLfloat z);
    virtual void		rotate			( const GLfloat x,
                                                          const GLfloat y,
                                                          const GLfloat z = 0.0 );
                                                          
    virtual void		setSX			( const GLfloat x );
    virtual void		setSY			( const GLfloat y );
    virtual void		setSZ			( const GLfloat z );
    virtual void		setRX			( const GLfloat x );
    virtual void		setRY			( const GLfloat y );
    virtual void		setRZ			( const GLfloat z );
    virtual GLfloat		getSX			( ) const { return scl[X]; }
    virtual GLfloat		getSY			( ) const { return scl[Y]; }
    virtual GLfloat		getSZ			( ) const { return scl[Z]; }
    virtual GLfloat		getRX			( ) const { return rot[X]; }
    virtual GLfloat		getRY			( ) const { return rot[Y]; }
    virtual GLfloat		getRZ			( ) const { return rot[Z]; }
};

#endif