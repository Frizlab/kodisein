/*
 *  KCameraHandler.h
 *  kodisein
 */
 
#ifndef __KCameraHandler
#define __KCameraHandler

#include "KPickHandler.h"

class KModuleCamera;
class KPerspectiveProjection;

class KCameraHandler : public KPickHandler
{
    public:
    
    vector<KModuleCamera*>		cameras;
    vector<KProjection*>		saved_cameras;
    
                KCameraHandler  	();
                
    void	startPlaying		();
    void	stopPlaying		();
    
    bool	hasManualCameras	();
    
    bool	pick			( const KMouseEvent & ) { return false; }
    bool	mouseMotion		( const KMouseEvent & );
    void	updateProjection	( const KMouseEvent & );
    
    void	addCamera		( KModuleCamera * );
    void	removeCamera		( KModuleCamera * );
};

#endif