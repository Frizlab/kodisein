/*
 *  KLandscape.h
 *  kodisein
 */

#ifndef __KLandscape
#define __KLandscape

#include "KMatrixHandle.h"

class KVertexHandle;

class KLandscape : public KMatrixHandle
{
    INTROSPECTION

    protected:
    
    GLint			u_order, v_order;
    GLint			u_steps, v_steps;
    
    vector<KVertexHandle*> 	vertices;
    
    void			createControllPoints	();
    
    public:
                                KLandscape		( KMatrixModule * );
                        
    virtual void		display			( int );
    
    virtual void		setUOrder		( float );
    virtual float 		getUOrder		() const { return u_order; }
    virtual void		setVOrder		( float );
    virtual float 		getVOrder		() const { return v_order; }
    virtual void		setUSteps		( float i ) { u_steps = (int)i; }
    virtual float 		getUSteps		() const { return u_steps; }
    virtual void		setVSteps		( float i ) { v_steps = (int)i; }
    virtual float		getVSteps		() const { return v_steps; }

    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int = 0 ) const;
}; 

#endif