/*
 *  KModuleParticleEmitter.h
 *  kodisein
 */

#ifndef __KModuleParticleEmitter
#define __KModuleParticleEmitter

#include "KMatrixModule.h"

class KModuleParticleEmitter : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    unsigned int		last_time;
    unsigned int		emitter_delay;
    void			createConnectors       ();

    public:
                                KModuleParticleEmitter ();

    void			setEmitterDelay		( float );
    float			getEmitterDelay		() const { return emitter_delay; }
    
    void 			display		 	( int );
    void 			displayConnectors 	( int );

    virtual KMatrixModule *	getFirstChild		() const;
};

#endif
