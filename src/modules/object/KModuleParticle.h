/*
 *  KModuleParticle.h
 *  kodisein
 */

#ifndef __KModuleParticle
#define __KModuleParticle

#include "KMatrixModule.h"
#include "KParticle.h"

class KModuleParticle : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    int				connection_mode;
    int				lifetime;
    vector<KParticle*>		particles;
    
    void			createConnectors       ();

    public:
    
                                KModuleParticle 	();

    void			setLifeTime		( float );
    void			setConnectionMode	( int m ) { connection_mode = m; }

    float			getLifeTime		() const { return lifetime; } 
    int				getConnectionMode	() const { return connection_mode; }

    void			emit			();
    void			display			( int );
    void 			displayConnectors 	( int );
};

#endif
