/*
 *  KCamera.h
 *  kodisein
 */

#ifndef __KCamera
#define __KCamera

#include "KMatrixHandle.h"
#include "KPerspectiveProjection.h"

class KModuleInspector;

class KCamera : public KMatrixHandle
{
    INTROSPECTION

    protected:
    
    KProjection *		projection;
    
    public:
    
                                KCamera			( KMatrixModule * m );
    
    virtual void		display 		( int mode );
    virtual void		render 			();
    virtual KProjection *	getProjection		() { return projection; }
    virtual void 		notify		 	() const;
    virtual void		initInspector 		( KModuleInspector * );
    
    virtual void		setPerspective 		( bool );
    virtual bool		getPerspective		( ) const;
    
    virtual GLfloat	getViewportRelativeWidth	() const
                                                        { return projection->getViewportRelativeWidth(); }
    virtual GLfloat	getViewportRelativeHeight	() const
                                                        { return projection->getViewportRelativeHeight(); }
    virtual GLfloat	getViewportRelativePosX 	() const
                                                        { return projection->getViewportRelativePosX(); }
    virtual GLfloat	getViewportRelativePosY		() const
                                                        { return projection->getViewportRelativePosY(); }
    virtual void	setViewportRelativePosX 	( GLfloat x )	
                                                        { projection->setViewportRelativePosX(x); }
    virtual void	setViewportRelativePosY 	( GLfloat y )	
                                                        { projection->setViewportRelativePosY(y); }
    virtual void	setViewportRelativeWidth	( GLfloat w )
                                                        { projection->setViewportRelativeWidth(w); }
    virtual void	setViewportRelativeHeight	( GLfloat h )
                                                        { projection->setViewportRelativeHeight(h); }
    virtual GLfloat	getFov				()  const { return projection->getFov(); }
    virtual void	setFov				( GLfloat f ) 	{ projection->setFov(f); }
    virtual GLfloat	getAspectRatio			() const { return projection->getAspectRatio(); }
    virtual void	setAspectRatio			( GLfloat f )	{ projection->setAspectRatio(f); }
};

#endif
