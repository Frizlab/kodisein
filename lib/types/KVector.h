/*
 *  KVector.h
 *  kodisein
 */

#ifndef __KVector
#define __KVector

#pragma warning(disable:4786)

#include <math.h>
#ifndef M_PI
#define M_PI 3.141592654f
#endif

#include <SDL_opengl.h>

#include "KIntrospection.h"

// --------------------------------------------------------------------------------------------------------
typedef GLfloat GLmat[16];
typedef GLfloat GLvec[4];

class KSize
{
    public:
    
    int w, h;
    
    KSize (int _w = 0, int _h = 0) { w=_w; h=_h; }
    KSize operator/ ( float d ) const { return KSize((int)(w/d), (int)(h/d)); }
    KSize operator* ( float d ) const { return KSize((int)(w*d), (int)(h*d)); }
    KSize operator- ( KSize s ) const { return KSize(w-s.w,h-s.h); }
    KSize operator+ ( KSize s ) const { return KSize(w+s.w,h+s.h); }
    bool  operator==( KSize s ) const { return (w==s.w && h==s.h); }
};

class KPosition
{
    public:
    
    int x, y;
    
    KPosition (int _x = 0, int _y = 0) { x=_x; y=_y; }
    KPosition operator+ ( KPosition p ) const { return KPosition(x+p.x,y+p.y); }
    KPosition operator- ( KPosition p ) const { return KPosition(x-p.x,y-p.y); }
    KPosition operator+ ( KSize p ) const { return KPosition(x+p.w,y+p.h); }
    KPosition operator- ( KSize p ) const { return KPosition(x-p.w,y-p.h); }
    bool  operator==( KPosition p ) const { return (x==p.x && y==p.y); }
};

// --------------------------------------------------------------------------------------------------------

#define DEG2RAD(d)			(M_PI*(d)/180.0)
#define RAD2DEG(r)			((r)*180.0/M_PI)

#define kMin(a,b) 			(((a) <= (b)) ? (a) : (b))
#define kMax(a,b) 			(((a) >= (b)) ? (a) : (b))
#define kAbs(d) 			(((d) >= 0) ? (d) : -(d))
#define kAbsMax(a,b)			((kAbs((a)) >= kAbs((b))) ? (a) : (b))

// --------------------------------------------------------------------------------------------------------
               
enum {	X = 0, SX = 0, Y, Z, W, SY = 5, SZ = 10, TX = 12, TY, TZ };

class KVector
{
    INTROSPECTION

    friend class KMatrix;
    friend KVector operator* (const GLfloat, const KVector &);
    friend KVector operator- (const KVector &);

    protected:
    
    GLvec		vector;
    
    public:
    
                                KVector 		();
                                KVector			( const GLfloat, const GLfloat, 
                                                          const GLfloat = 0.0, const GLfloat = 0.0 );
                                KVector 		( const KVector & );
                                
    inline void			reset			();
    inline void			normalize		();
    inline void			operator=		( const KVector & );
    inline void			operator+=		( const KVector & );
    inline void			operator-=		( const KVector & );    
    inline void			operator*=		( GLfloat );
    inline void			operator/=		( GLfloat );
    inline KVector		cross			( const KVector & ) const;
    inline GLfloat		operator*		( const KVector & ) const;
    inline KVector		operator-		( const KVector & ) const;
    inline KVector		operator+		( const KVector & ) const;
    inline KVector		operator*		( GLfloat ) const;
    inline KVector		operator/		( GLfloat ) const;
    inline GLfloat		operator[] 		(int i) const { return vector[i]; }
    inline KVector		perpendicular		( const KVector & ) const;
    inline KVector		parallel		( const KVector & ) const;
    inline KVector		reflect			( const KVector & ) const;
    inline KVector		normal			() const;
    inline GLfloat		length			() const;
    inline GLfloat		angle			( const KVector & ) const;
    inline GLfloat		xyangle			( const KVector & ) const;
    inline KVector		xyperp			() const;
    inline const GLfloat *	getValues		() const { return vector; }
    inline void			glVertex		() const { glVertex3fv(vector); }
};

// --------------------------------------------------------------------------------------------------------
inline void  KVector::operator= ( const KVector & v )
{
    vector[X] = v.vector[X]; vector[Y] = v.vector[Y]; vector[Z] = v.vector[Z]; vector[W] = v.vector[W];
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::parallel ( const KVector & n ) const
{
    float dot = vector[X]*n.vector[X] + vector[Y]*n.vector[Y] + vector[Z]*n.vector[Z];
    return KVector(dot*n.vector[X], dot*n.vector[Y], dot*n.vector[Z]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::perpendicular ( const KVector & n ) const
{
    float dot = vector[X]*n.vector[X] + vector[Y]*n.vector[Y] + vector[Z]*n.vector[Z];
    return KVector(vector[X]-dot*n.vector[X], vector[Y]-dot*n.vector[Y], vector[Z]-dot*n.vector[Z]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::reflect ( const KVector & n ) const
{
    float dot = 2.0*(vector[X]*n.vector[X] + vector[Y]*n.vector[Y] + vector[Z]*n.vector[Z]);
    return KVector(vector[X]-dot*n.vector[X], vector[Y]-dot*n.vector[Y], vector[Z]-dot*n.vector[Z]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::cross ( const KVector & v ) const
{
    return KVector( vector[Y]*v.vector[Z]-vector[Z]*v.vector[Y],
                    vector[Z]*v.vector[X]-vector[X]*v.vector[Z],
                    vector[X]*v.vector[Y]-vector[Y]*v.vector[X]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::normal () const
{
    KVector normalized(*this);
    normalized.normalize();
    return normalized;
}

// --------------------------------------------------------------------------------------------------------
inline void KVector::normalize ()
{
    float l = sqrt(vector[X]*vector[X]+vector[Y]*vector[Y]+vector[Z]*vector[Z]*vector[W]*vector[W]);
    if (l != 0.0) 
    {
        l = 1.0/l; 
        vector[X] *= l; vector[Y] *= l; vector[Z] *= l; vector[W] *= l;
    }
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::xyperp () const
{
    return KVector(-vector[Y], vector[X]);
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::xyangle ( const KVector & v ) const
{
    KVector thisXY  = KVector(vector[X], vector[Y]).normal();
    KVector otherXY = KVector(v[X], v[Y]).normal();
    if (thisXY.xyperp() * otherXY >= 0) return RAD2DEG(acos(thisXY * otherXY));
    return -RAD2DEG(acos(thisXY * otherXY));
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::angle ( const KVector & v ) const
{
    return RAD2DEG(acos(this->normal()*v.normal()));
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::length () const
{
    return sqrt(vector[X]*vector[X]+vector[Y]*vector[Y]+vector[Z]*vector[Z]+vector[W]*vector[W]);
}

// -------------------------------------------------------------------------------------------------------- 
inline void KVector::operator+= ( const KVector & v )
{
    vector[X]+=v.vector[X]; vector[Y]+=v.vector[Y]; vector[Z]+=v.vector[Z]; vector[W]+=v.vector[W];
}

// --------------------------------------------------------------------------------------------------------
inline void KVector::operator-= ( const KVector & v )
{
    vector[X]-=v.vector[X]; vector[Y]-=v.vector[Y]; vector[Z]-=v.vector[Z]; vector[W]-=v.vector[W];
} 

// --------------------------------------------------------------------------------------------------------
inline void KVector::operator*= ( const GLfloat f )
{
    vector[X] *= f; vector[Y] *= f; vector[Z] *= f; vector[W] *= f;
}

// --------------------------------------------------------------------------------------------------------
inline void KVector::operator/= ( const GLfloat f )
{
    vector[X] /= f; vector[Y] /= f; vector[Z] /= f; vector[W] /= f;
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::operator* ( const KVector & v ) const
{
    return vector[X]*v.vector[X] + vector[Y]*v.vector[Y] + vector[Z]*v.vector[Z] + vector[W]*v.vector[W];
}

// --------------------------------------------------------------------------------------------------------
inline KVector operator* ( const GLfloat f, const KVector & v )
{
    return KVector (f*v.vector[X], f*v.vector[Y], f*v.vector[Z], f*v.vector[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector operator- ( const KVector & v )
{
    return KVector (-v.vector[X], -v.vector[Y], -v.vector[Z], -v.vector[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator* ( const GLfloat f ) const
{
    return KVector(vector[X]*f, vector[Y]*f, vector[Z]*f, vector[W]*f);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator/ ( const GLfloat f ) const
{
    return KVector(vector[X]/f, vector[Y]/f, vector[Z]/f, vector[W]/f);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator- ( const KVector & v ) const
{
    return KVector(vector[X]-v.vector[X],vector[Y]-v.vector[Y],vector[Z]-v.vector[Z],vector[W]-v.vector[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator+ ( const KVector & v ) const
{
    return KVector(vector[X]+v.vector[X],vector[Y]+v.vector[Y],vector[Z]+v.vector[Z],vector[W]+v.vector[W]);
}

// --------------------------------------------------------------------------------------------------------
inline void KVector::reset ()
{
    vector[X] = 0.0; vector[Y] = 0.0; vector[Z] = 0.0; vector[W] = 0.0;
}

#endif