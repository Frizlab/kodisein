/*
 *  KModuleMaterial.h
 *  kodisein
 */

#ifndef __KModuleMaterial
#define __KModuleMaterial

#include "KAttributeModule.h"

class KModuleInspector;

class KModuleMaterial : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
     
    KColor			color;
    bool			cull_face;
    int				parameter;
    float			shininess;
    int				polygon_mode;
    int				shading_mode;
    int				face_mode;
    
    void			createConnectors	();
   
    public:
    
                                KModuleMaterial		();
    
    virtual void		apply			();
    
    void			setCullFace		( bool b )  { cull_face = b; }
    void			setShininess	( float );
    void			setShadingMode	( int i )   { shading_mode = i; }
    void			setPolygonMode	( int i )   { polygon_mode = i; }
    void			setParameter	( int i )   { parameter = i; }
    void			setFaceMode		( int i )   { face_mode = i; }

	bool			getCullFace		() 	const   { return cull_face; }
    float			getShininess	()  const   { return shininess; }    
    int				getShadingMode	() 	const   { return shading_mode; }
    int				getPolygonMode	() 	const   { return polygon_mode; }
    int				getParameter	()  const   { return parameter; }
    int				getFaceMode		()  const   { return face_mode; }
};

#endif