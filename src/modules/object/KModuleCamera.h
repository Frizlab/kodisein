/*
 *  KModuleCamera.h
 *  kodisein
 */

#ifndef __KModuleCamera
#define __KModuleCamera

#include "KMatrixModule.h"
#include "KCamera.h"

class KModuleCamera : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    bool		manual_mode;
    
    void		createConnectors	();

    public:
    
                        KModuleCamera		();
    
    virtual void	initProjection		();

    virtual void	displayConnectors	( int mode );
    
    bool		getManualMode		() const { return manual_mode; }
    void		setManualMode		( bool b ) { manual_mode = b; }
};

#endif