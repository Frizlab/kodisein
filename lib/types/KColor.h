/*
 *  KColor.h
 *  kodisein
 */

#ifndef __KColor
#define __KColor

#pragma warning(disable:4786)

#include "KIntrospection.h"

#include <SDL_opengl.h>

enum {	R, G, B, A};

class KColor
{
    INTROSPECTION
    
    protected:
    
    GLfloat		values[4];

    public:
    
                        KColor 		();
                        KColor 		( const KColor & object );
                        KColor 		( GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0 );
                        
    void		setValues	( const GLfloat r, const GLfloat g, const GLfloat b,
                                            const GLfloat a = 1.0 );
    const GLfloat *	getValues	() const { return values; }
    void		setValues4fv	( const GLfloat * v );
    void		setRed		( const GLfloat r ) { values[R] = r; }
    void		setGreen	( const GLfloat g ) { values[G] = g; }
    void		setBlue		( const GLfloat b ) { values[B] = b; }
    void		setAlpha	( const GLfloat a ) { values[A] = a; }
    GLfloat		getRed		( ) const { return values[R]; }
    GLfloat		getGreen	( ) const { return values[G]; }
    GLfloat		getBlue		( ) const { return values[B]; }
    GLfloat		getAlpha	( ) const { return values[A]; }
    void		operator =	( const KColor & );
    GLfloat 		operator[]	(int i) const { return values[i]; }
    
    void		glColor		() const { glColor4fv(values); }
};

#endif