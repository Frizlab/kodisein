/*
 *  KLight.cpp
 *  kodisein
 */

#include "KLight.h"
#include "KModules.h"
#include "KObjects.h"
#include "KConsole.h"

#include "KController.h"

KDL_CLASS_INTROSPECTION_1 (KLight, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KLight::KLight ( KMatrixModule * m ) : KMatrixHandle ( m )
{
    spot_exponent = 0.0;
    spot_cutoff   = 180.0;
    c_attenuation = 1.0;
    l_attenuation = 0.0;
    q_attenuation = 0.0;
    directional	  = false;
}

// --------------------------------------------------------------------------------------------------------
void KLight::initLight ( GLenum light, const KMatrix & eyeMatrix, 
                            const KColor * ambient, const KColor * diffuse, const KColor * specular )
{
    glLightf  (light, GL_SPOT_EXPONENT,		spot_exponent);
    glLightf  (light, GL_SPOT_CUTOFF,		spot_cutoff);
    glLightf  (light, GL_CONSTANT_ATTENUATION,	c_attenuation);
    glLightf  (light, GL_LINEAR_ATTENUATION,	l_attenuation);
    glLightf  (light, GL_QUADRATIC_ATTENUATION,	q_attenuation);

    KVector direction = eyeMatrix.getZVector();
    KVector position  = eyeMatrix.getPosition();
    position = KVector(position[X], position[Y], position[Z], (directional ? 0.0 : 1.0));

    glLightfv (light, GL_POSITION, position.getValues());
    glLightfv (light, GL_SPOT_DIRECTION, direction.getValues());
    
    if (diffuse) glLightfv (light, GL_DIFFUSE, diffuse->getValues());
    else
    {
        GLfloat tmpDiffuse[4] = {1.0, 1.0, 1.0, 1.0};
        glLightfv (light, GL_DIFFUSE, tmpDiffuse);
    }
    if (specular) glLightfv (light, GL_SPECULAR, specular->getValues());
    else
    {
        GLfloat tmpSpecular[4] = {1.0, 1.0, 1.0, 1.0};
        glLightfv (light, GL_SPECULAR, tmpSpecular);
    }
    if (ambient) glLightfv (light, GL_AMBIENT, ambient->getValues());
    else
    {
        GLfloat tmpAmbient[4] = {0.0, 0.0, 0.0, 1.0};
        glLightfv (light, GL_AMBIENT, tmpAmbient);
    }
    
    glEnable  (light);
}

// --------------------------------------------------------------------------------------------------------
void KLight::render ()
{
    unloadId();

    GLfloat zf 	= 10.0 / (c_attenuation + l_attenuation * 10.0 + q_attenuation * 100.0);
    GLfloat zn 	= 1.0  / (c_attenuation + l_attenuation + q_attenuation);

    if (spot_cutoff < 180.0)
    {
        GLfloat sinus	= sin(DEG2RAD(spot_cutoff));
        GLfloat cosinus = cos(DEG2RAD(spot_cutoff));
        GLfloat farz 	= cosinus * zf;
        GLfloat nearz 	= cosinus * zn;        
        
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, zn);
        glVertex3f(0.0, 0.0, zf);
        glVertex3f(0, 	 sinus * zn, 	nearz);
        glVertex3f(0, 	 sinus * zf,	farz);
        glVertex3f(0, 	-sinus * zn, 	nearz);
        glVertex3f(0, 	-sinus * zf,	farz);
        glVertex3f( sinus * zn, 0.0, 	nearz);
        glVertex3f( sinus * zf,	0.0, 	farz);
        glVertex3f(-sinus * zn, 0.0, 	nearz);
        glVertex3f(-sinus * zf,	0.0,	farz);
        glEnd();
    }
    else
    {
        glBegin(GL_LINES);
        glVertex3f(0.0, -zf, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,  zf, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, -zf); glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0,  zf); glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(-zf, 0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glVertex3f( zf, 0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glEnd();
    }
}

// --------------------------------------------------------------------------------------------------------
void KLight::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        if (Controller.modules->objects->flags[KDS_OBJECTS_FLAG_DISPLAY_LIGHTS]) 
        {
            glPushAttrib( GL_CURRENT_BIT | GL_LIGHTING_BIT );
            glDisable(GL_LIGHTING);
            module->getModuleColor().glColor();
            render();
            glPopAttrib();
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KLight::setCAttenuation ( GLfloat a )
{
    c_attenuation = kMax(a, 0.0);
}

// --------------------------------------------------------------------------------------------------------
void KLight::setLAttenuation ( GLfloat a )
{
    l_attenuation = kMax(a, 0.0);
}

// --------------------------------------------------------------------------------------------------------
void KLight::setQAttenuation ( GLfloat a )
{
    q_attenuation = kMax(a, 0.0);
}

// --------------------------------------------------------------------------------------------------------
void KLight::setSpotCutoff ( GLfloat c )
{
    if (c > 90.0) spot_cutoff = 180.0;
    else spot_cutoff = kMax(0.0, c);
}

// --------------------------------------------------------------------------------------------------------
void KLight::setSpotExponent ( GLfloat e )
{
    spot_exponent = kMax(0.0, kMin(128.0, e));
}

