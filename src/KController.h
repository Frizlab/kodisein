/*
 *  KController.h
 *  kodisein
 */

#ifndef __KController
#define __KController

#include "KEventHandler.h"

extern float KODISEIN_VERSION;

enum {	KDS_APPLICATION_MODE_EDIT_MODULES, 
        KDS_APPLICATION_MODE_EDIT_OBJECTS, 
        KDS_APPLICATION_MODE_ANIMATION };
enum {  KDL_NOTIFICATION_TYPE_APPLICATION_OPEN_FILE = KDL_NOTIFICATION_TYPE_EVENT_HANDLER_END,
        KDL_NOTIFICATION_TYPE_CONTROLLER_END };

#ifdef __cplusplus
class KSceneSet;
class KModules;
class KMainMenu;
class KPreferences;
class KFileTreeWindow;
class KModuleInspector;
class KTextureSets;

class KController : public KEventHandler
{
    INTROSPECTION

    int			old_mode;	// previous application mode
    
    KSceneSet *		scene_set;

    public:
    
    string		app_name;
    KPreferences *	preferences;
    KMainMenu *		main_menu;
    KModules *		modules;
    KModuleInspector *	inspector;
    KFileTreeWindow *	file_browser;
    KTextureSets *	texture_sets;

    KKeyActionHandler 	mod_key_handler;
    
                        KController 			();
    
    void		projectionHandlerChanged	();
    void		applicationModeChanged		(); // application modes
    void		toggleAnimation			();
    void		startAnimation			();
    void		stopAnimation			();
    void		startModuleEditing 		();
    void		startObjectEditing 		();

    bool		init				();
    void		quit	 			();

    void		displayPickHandlers		();

    void		handleMouseButtonEvent 		( SDL_MouseButtonEvent & );
    void		handleUserEvent			( SDL_UserEvent & );
    
    void		mouseModeCallback		( const string & );

    void		openKodiseinFile			( const string & );
    void		saveProjectFile			( const string & );
    void		open				();
    void		close				();
    void		save				();
    void		saveAs				();
    void		saveScreenShot			();

    bool		checkHeaderInFileWithName	( const string & );
    string 		getXMLFromFileWithName		( const string & );
    bool 		saveXMLInFileWithName		( const string &, const string & );
    
    void		openSceneSetFile		( const string & );
    void		openSceneSet			();
    void		closeSceneSet			();
    void		saveSceneSet			();

    void		setFastDisplay			( bool );

    void		setFullscreenMode		( bool );
    bool		getFullscreenMode		() { return KEventHandler::getFullscreen(); }

    int			getApplicationMode		() const { return mode; }
};

extern KController Controller;
#endif // __cplusplus

#endif
