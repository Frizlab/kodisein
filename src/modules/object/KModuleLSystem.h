/*
 *  KModuleLSystem.h
 *  kodisein
 */

#ifndef __KModuleLSystem
#define __KModuleLSystem

#include "KMatrixModule.h"

class KModuleInspector;

class KModuleLSystem : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    bool			leaf_mode;
    float			depth[4];
    unsigned int		ls_display_list;
    
    void			createConnectors	();

    public:
    
                                KModuleLSystem		();
    
    virtual void		displayBranch 		( int, float, vector<KMatrixModule*> &, vector<float> &, int);
    virtual void		displayTree		( int );
    virtual void		display			( int );
    virtual void		displayChildModules	( int );
    virtual void		displayConnectors	( int );
    
    void			setLeafMode		( bool b ) { leaf_mode = b; }
    void			setDepth1		( float d ) { depth[0] = d; }
    void			setDepth2		( float d ) { depth[1] = d; }
    void			setDepth3		( float d ) { depth[2] = d; }
    void			setDepth4		( float d ) { depth[3] = d; }

    bool			getLeafMode		() const { return leaf_mode; }
    float			getDepth1		() const { return depth[0]; }
    float			getDepth2		() const { return depth[1]; }
    float			getDepth3		() const { return depth[2]; }
    float			getDepth4		() const { return depth[3]; }
};

#endif
