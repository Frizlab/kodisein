/*
 *  KModules.h
 *  kodisein
 */

#ifndef __KModules
#define __KModules

#include "KModule.h"
#include "KSelectionHandler.h"
#include "KCameraHandler.h"

#include <hash_map>

typedef KModule * (KModule::*ModuleConstructorPtr)();

enum {	KDS_MODULES_FLAG_SHOW_MODULATORS = KDL_PICKHANDLER_FLAG_END, 
        KDS_MODULES_FLAG_SHOW_CONNECTIONS, 
        KDS_MODULES_FLAG_SHOW_INACTIVE,
        KDS_MODULES_FLAG_SHOW_TEXTURES,
        KDS_MODULES_FLAG_SHOW_MODULATOR_STATUS,
        KDS_MODULES_FLAG_END };
        
class KModuleInspector;
class KModuleCamera;
class KGlobalModulator;
class KModulator;
class KObjects;
class KValueModule;
class KConnectorValueInOut;

typedef hash_multimap<long, KConnector*> KConnectorMultiMap;

class KModules : public KSelectionHandler
{
    INTROSPECTION
    
    friend class KObjects;
    friend class KTextureSets;

    KCameraHandler 			camera_handler;
    KConnectorMultiMap	connector_links;
    vector<GLuint>			display_list_names;
    string 				filename;
    vector<KModule*>			active_root_modules;
    vector<KModule*>			hidden_root_modules;
    vector<KValueModule*> 	  	value_modules;	

    public:

    KGlobalModulator *	global_modulator;
    KObjects *		objects;
    
                KModules		();
                ~KModules		();

    void	startPlaying		(); // modes
    void	stopPlaying		();
    void	startEditing		();
    void	stopEditing		();
    
    void	displayPickables	( int mode ); // display
    void	display			( int mode );
    void	displayCameraView	( KModuleCamera * );
    void	displayModulatorStatus	(); 
    void	updateModuleInspector	();
    
    void	toggleModuleHierarchy	( bool, KModule * );
    void	toggleRootModulesOfType ( bool, const KClassId & );
    
    void	stopModulation		(); // modulation
    void	resetModulation		();
    void	updateModulation	();
    
    void	pickModule 		( KModule * ); // picking
    void	selectModulesInVector	( const vector<KModule*> & );
    
    bool	isModulePicked		( KModule * ) const;
    KModule *	getModuleForPickable 	( const KPickable * ) const;
    
    void	activateRootModule	( KModule * );
    vector<KModule*> getRootModules	( bool = false ) const;
    void	getModulesOfType 	( vector<KModule*> &, bool, 
                                                            const KClassId & = KClassId(NULL) );
    
    void	addModule		( KModule * ); // module management
    void	removePickable		( KPickable * );
    void	deletePickable		( KPickable * );
    
    void	addValueModule		( KValueModule * );
    void	removeValueModule	( KValueModule * );
    
    KModule *	newModuleForName	( const string & );
    void	connectNewModule	( KModule * );
    
    void	connect		 	();
    void	disconnect	 	();
    void	centerModule	 	();
    void	expandModule	 	();
    void	deleteAllModules	();
    void	deleteModuleHierarchy	( KModule * );
    
    void	toggleShowModulators	();
    bool	getShowTextures		() const {return flags[KDS_MODULES_FLAG_SHOW_TEXTURES];}
    void	setShowTextures		( bool );
    bool	getShowInactiveModules	() const {return flags[KDS_MODULES_FLAG_SHOW_INACTIVE];}
    void	setShowInactiveModules	( bool );
    bool	getShowModulators	() const {return flags[KDS_MODULES_FLAG_SHOW_MODULATORS];}
    void	setShowModulators	( bool );
    bool	getShowConnections	() const {return flags[KDS_MODULES_FLAG_SHOW_CONNECTIONS];}
    void	setShowConnections	( bool b ) {flags[KDS_MODULES_FLAG_SHOW_CONNECTIONS] = b;}
    void	setShowModulatorStatus	( bool b ) {flags[KDS_MODULES_FLAG_SHOW_MODULATOR_STATUS] = b;}
    bool	getShowModulatorStatus	() const {return flags[KDS_MODULES_FLAG_SHOW_MODULATOR_STATUS];}

    void	addObjectCallback	( const string & );

    void	setFileName 		( const string & f ) { filename = f; }   
    string	getFileName 		() const { return filename; }
    
    void	addDisplayListName	( GLuint );
    void	deleteDisplayLists	();
    
    void	cut			();
    void	pasted			( const string & );
    void	moved			( const KMouseEvent & );
    void	picked			();

    void	resolveGotoLinks	();
    void	resolveConnectorLinks	();
    void	addConnectorLink 	( KConnector *, long );
 
    KModule *	parseXMLForModule	( string & );
    void	parseXML		( string & );
    void	setXML			( string & );
    string	getXML			();
    
    void	focusOnPickedPickable	( bool = false );
};

// --------------------------------------------------------------------------------------------------------

#endif