/*
 *  KMatrix.h
 *  kodisein
 */

#ifndef __KMatrix
#define __KMatrix

#pragma warning(disable:4786)

#include "KVector.h"
#include "KNotificationObject.h"

class KMatrix : public KObject
{
    INTROSPECTION
    
    protected:
    
    GLmat			matrix;

    public:
    
                                KMatrix		();
                                KMatrix		( const KMatrix & );
                                KMatrix		( const GLfloat * );
                                KMatrix		( const KVector &, const KVector &, const KVector & );
    virtual		       ~KMatrix		() {}
                                    
    virtual void		transform	( const KMatrix & );
    virtual void		scale		( const GLfloat, const GLfloat, const GLfloat = 1.0 );
    virtual void		rotate		( const GLfloat, const GLfloat, const GLfloat = 0.0 );
    virtual void		reset		();
    
    inline  void		translate	( const GLfloat, const GLfloat, const GLfloat = 0.0 );
    inline  void		translate	( const KVector & );
    
            void		invert		();
                                                          
            void		setTX		( const GLfloat x ) { matrix[TX] = x; }
            void		setTY		( const GLfloat y ) { matrix[TY] = y; }
            void		setTZ		( const GLfloat z ) { matrix[TZ] = z; }
            GLfloat		getTX		() const { return matrix[TX]; }
            GLfloat		getTY		() const { return matrix[TY]; }
            GLfloat		getTZ		() const { return matrix[TZ]; }
            GLfloat		getDepthValue	() const;
            
    inline  virtual void	setPosition	( const KPosition & );
    inline  virtual void	setPosition	( const GLfloat, const GLfloat, const GLfloat = 0.0 );
    inline  virtual void	setPosition	( const KVector & );
    inline  KVector		getPosition	() const;
    inline  KVector		getXVector	() const;
    inline  KVector		getYVector	() const;
    inline  KVector		getZVector	() const;

    virtual void		operator=	( const KMatrix & );
            void		operator*=	( const KMatrix & );
            KMatrix		operator*	( const KMatrix & ) const;
            KVector		operator*	( const KVector & ) const;
            GLfloat 		operator[]	(int i) const { return matrix[i]; }
            
            void		glMultMatrix	() const { glMultMatrixf(matrix); }
            KMatrix		getInverse	() const { KMatrix i(*this); i.invert(); return i; }
};

// --------------------------------------------------------------------------------------------------------
void KMatrix::translate ( const KVector & v ) 
{
    translate(v.vector[X], v.vector[Y], v.vector[Z]);
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::translate ( const GLfloat x, const GLfloat y, const GLfloat z )
{
    matrix[12] += matrix[0]*x+matrix[4]*y+matrix[8]*z;
    matrix[13] += matrix[1]*x+matrix[5]*y+matrix[9]*z;
    matrix[14] += matrix[2]*x+matrix[6]*y+matrix[10]*z;
    matrix[15] += matrix[3]*x+matrix[7]*y+matrix[11]*z;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setPosition ( const KPosition & pos  ) 
{
    matrix[TX] = pos.x; matrix[TY] = pos.y;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setPosition ( const GLfloat x, const GLfloat y, const GLfloat z ) 
{
    matrix[TX] = x; matrix[TY] = y; matrix[TZ] = z;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setPosition ( const KVector & p ) 
{
    matrix[TX] = p.vector[X]; matrix[TY] = p.vector[Y]; matrix[TZ] = p.vector[Z];
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getPosition () const
{
    return KVector(matrix[TX], matrix[TY], matrix[TZ]);
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getXVector () const
{
    return KVector(matrix[0], matrix[1], matrix[2]);
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getYVector () const
{
    return KVector(matrix[4], matrix[5], matrix[6]);
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getZVector () const
{
    return KVector(matrix[8], matrix[9], matrix[10]);
}

#endif