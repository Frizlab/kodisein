/*
 *  KObjects.h
 *  kodisein
 */

#ifndef __KObjects
#define __KObjects

#include "KPickHandler.h"

class KHandle;
class KCamera;
class KModule;
class KMatrixModule;
class KProjection;

enum {  KDS_OBJECTS_FLAG_DISPLAY_HANDLES = KDL_PICKHANDLER_FLAG_END,
        KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE, 
        KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES, 
        KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES, 
        KDS_OBJECTS_FLAG_DISPLAY_CAMERAS, 
        KDS_OBJECTS_FLAG_DISPLAY_LIGHTS, 
        KDS_OBJECTS_FLAG_END };

class KObjects : public KPickHandler
{
    INTROSPECTION

    protected:
    
    KCamera *			current_camera;

    public:
                                KObjects			();

    void			startEditing			();
    void			stopEditing			();

    void			display				( int );
    void			displayPickables		( int );
    
    void			pickHandle			( KHandle * );
    KMatrixModule * 		getModuleForPickable 		( const KPickable * ) const;
    void			moved				( const KMouseEvent &  );
    void			focusOnPickedPickable		( bool = false );
    void			cameraView			();
    void			toggleShowCameras		();
    void			toggleShowLights		();
    void			toggleShowPicked		();
    void			toggleShowSelected		();
    void			setShowCameras			( bool );
    void			setShowLights			( bool );
    void			setShowPicked			( bool );
    void			setShowSelected			( bool );
    void			setShowUnselected		( bool );
    bool			getShowCameras			();
    bool			getShowLights			();
    bool			getShowPicked			();
    bool			getShowSelected			();
    bool			getShowUnselected		();
    void			hideAll				();
    void			showAll				();
    void			showParent			();
    void			showChildren			();
    void			showPrevSibling			();
    void			showNextSibling			();
    void			showRoot			();
    void			showLeaves			();
    void			resetHandle			();
    void			resetHandlePosition		();
    void			resetHandleRotation		();
    void			resetHandleSize			();
    KProjection *		getProjection			();
    
    bool			shouldModuleDisplayHandles 	( KModule * );
    bool			isProjectionEnabled		() const;

    void			setXML				( string & );
    string 			getXML				();
};

// --------------------------------------------------------------------------------------------------------

#endif
