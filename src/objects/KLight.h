/*
 *  KLight.h
 *  kodisein
 */

#ifndef __KLight
#define __KLight

#include "KMatrixHandle.h"

class KLight : public KMatrixHandle
{
    INTROSPECTION

    protected:

    GLfloat				spot_exponent;
    GLfloat				spot_cutoff;
    GLfloat				c_attenuation;
    GLfloat				l_attenuation;
    GLfloat				q_attenuation;
    bool				directional;
    
    public:
    
                                        KLight			( KMatrixModule * );
    
    virtual void			display 		( int mode );
    virtual void			render 			();
    virtual void			initLight		( GLenum, const KMatrix &,
                                                                    const KColor *, const KColor *, const KColor * );
    virtual void			setDirectional		( bool d ) { directional = d; }
    virtual void			setCAttenuation		( GLfloat );
    virtual void			setLAttenuation		( GLfloat );
    virtual void			setQAttenuation		( GLfloat );
    virtual void			setSpotCutoff		( GLfloat );
    virtual void			setSpotExponent		( GLfloat );

    virtual bool			getDirectional		() const { return directional; }
    virtual GLfloat			getCAttenuation		() const { return c_attenuation; }
    virtual GLfloat			getLAttenuation		() const { return l_attenuation; }
    virtual GLfloat			getQAttenuation		() const { return q_attenuation; }
    virtual GLfloat			getSpotCutoff		() const { return spot_cutoff; }
    virtual GLfloat			getSpotExponent		() const { return spot_exponent; }
};

#endif
