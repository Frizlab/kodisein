/*
 *  KPerspectiveProjection.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KPerspectiveProjection.h"
#include "KEventHandler.h"
#include "KConsole.h"
#include "KXMLTools.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KPerspectiveProjection, KProjection)

// -------------------------------------------------------------------------------------------------------- 
// -------------------------------------------------------------------------------------------------------- 
KPerspectiveProjection::KPerspectiveProjection ( GLfloat f, GLfloat zn, GLfloat zf ) : KProjection ( zn, zf )
{
    reset ();
    fov = f; 
}

// --------------------------------------------------------------------------------------------------------
KPerspectiveProjection::KPerspectiveProjection ( const KProjection & p ) : KProjection (p)
{
}

// --------------------------------------------------------------------------------------------------------
KProjection * KPerspectiveProjection::copy() const
{
    return new KPerspectiveProjection(*this);
}
 
// -------------------------------------------------------------------------------------------------------- 
void KPerspectiveProjection::rotate ( const GLfloat x, const GLfloat y, const GLfloat z )
{
    KVector savePos = getLookAtPosition();
    translate(-getPosition());
        
    if (KEventHandler::flags[KDL_DISPLAY_MODE_FREE_ROTATION])
    {
        KMatrix::rotate(x, y, z);
    }
    else
    {
        KVector up   = getYVector();
        KVector look = getZVector();
    
        KMatrix rotxz; rotxz.rotate (x, 0.0, z);
        KMatrix roty;  roty.rotate  (0.0, y, 0.0);
    
        KVector yunit(0.0, 1.0, 0.0), zunit (0.0, 0.0, 1.0);
    
        KVector lookperp = look.perpendicular (yunit); // y-axis rotation    
        if (lookperp.length() > 0)
        {
            look 	= roty * lookperp + look.parallel(yunit);
            up   	= roty * up.perpendicular(yunit) + up.parallel(yunit);
        }
        
        // x & z-axis rotation 
        KMatrix transmat(up.cross(look), up, look);
        
        KVector uprotxz		= rotxz * yunit;
        KVector lookrotxz 	= rotxz * zunit;
    
        up		= transmat * uprotxz;
        look 		= transmat * lookrotxz;
        
        *((KMatrix*)this) = KMatrix(up.cross(look), up, look);
    }
    
    setPosition( savePos + eye_distance * getZVector());
}

// --------------------------------------------------------------------------------------------------------
void KPerspectiveProjection::apply ()
{
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    
    gluPerspective (fov, getCurrentAspectRatio(), znear, zfar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    KVector lookAt = getLookAtPosition();

    gluLookAt(	matrix[TX], matrix[TY], matrix[TZ],
                lookAt[X], lookAt[Y], lookAt[Z],
                matrix[4], matrix[5], matrix[6]);
}

// --------------------------------------------------------------------------------------------------------
void KPerspectiveProjection::focusOn ( const KVector & pos )
{
    setPosition(pos + eye_distance*getZVector());
}

// --------------------------------------------------------------------------------------------------------
void KPerspectiveProjection::setEyeDistance ( GLfloat ed )
{
    KVector lookAtPos = getLookAtPosition();
    eye_distance = kMin( kMax(znear, ed), 0.9 * zfar );
    setPosition(lookAtPos + eye_distance * getZVector());
}

// --------------------------------------------------------------------------------------------------------
KVector KPerspectiveProjection::getLookAtPosition () const
{
    return (-eye_distance * getZVector() + getPosition());
}

// -------------------------------------------------------------------------------------------------------- 
void KPerspectiveProjection::reset ()
{
    fov          = 60.0;
    eye_distance = znear;
    KMatrix::reset();
    translate(0.0, 0.0, eye_distance);
}

// --------------------------------------------------------------------------------------------------------
void KPerspectiveProjection::setXML ( string & xml )
{
    kXMLParseNamedOpenTag(xml, "Projection");
    kXMLParseValue(xml, "matrix",   KDL_XML_VALUE_MATRIX, this);
    kXMLParseValue(xml, "eye distance", KDL_XML_VALUE_FLOAT, &eye_distance, false);
    kXMLParseNamedCloseTag(xml, "Projection");
}

// --------------------------------------------------------------------------------------------------------
string KPerspectiveProjection::getXML ( int depth ) const
{
    string xml;
    xml += kXMLOpenTag("Projection", "", depth);
    xml += kXMLValue("matrix", KDL_XML_VALUE_MATRIX, this, depth+KDL_XML_INDENT);
    xml += kXMLValue("eye distance", KDL_XML_VALUE_FLOAT, &eye_distance, depth+KDL_XML_INDENT);
    xml += kXMLCloseTag("Projection", depth);
    return xml;
}

