/*
 *  KMainMenu.cpp
 *  kodisein
 */

#include "KMainMenu.h"
#include "KController.h"
#include "KKeyActionHandler.h"
#include "KPreferences.h"
#include "KTextureSets.h"
#include "KGlobalModulator.h"
#include "KModules.h"
#include "KObjects.h"
#include "KConsole.h"
#include "KSubMenuItem.h"
#include "KStatusMenuItem.h"
#include "KMessagePanel.h"
#include "KButtonBox.h"

KDL_CLASS_INTROSPECTION_1 (KMainMenu, KMenuWindow)

#if defined(__APPLE__) && defined(__MACH__) // Mac default key bindings

#define KEYS_OPEN    "META_o"
#define KEYS_SAVE    "META_s"
#define KEYS_SAVE_AS "SHIFT+META_s"
#define KEYS_CLOSE   "META_w"
#define KEYS_QUIT    "META_q"

#define KEYS_CUT     "META_x"
#define KEYS_COPY    "META_c"
#define KEYS_PASTE   "META_v"
#define KEYS_UNDO    "META_z"

#define KEYS_SHORTCUTS "CTRL_s"
#define KEYS_SCREENSHOT "SHIFT+ALT_s"

#define KEYS_TEST    "META_t"
#define KEYS_ABOUT   "SHIFT+CTRL+ALT+META_a"

#else // Windows/Linux default key bindings

#define KEYS_OPEN    "CTRL_o"
#define KEYS_SAVE    "CTRL_s"
#define KEYS_SAVE_AS "SHIFT+CTRL_s"
#define KEYS_CLOSE   "CTRL_w"
#define KEYS_QUIT    "CTRL_q"

#define KEYS_CUT     "CTRL_x"
#define KEYS_COPY    "CTRL_c"
#define KEYS_PASTE   "ALT_v"
#define KEYS_UNDO    "CTRL_z"

#define KEYS_SHORTCUTS  "ALT_s"
#define KEYS_SCREENSHOT "SHIFT+ALT_s"

#define KEYS_TEST    "ALT_t"
#define KEYS_ABOUT   "SHIFT+CTRL+ALT_a"

#endif

// --------------------------------------------------------------------------------------------------------
KMainMenu::KMainMenu () : KMenuWindow ()
{
    depth = INT_MAX-1;
    animation_key_handler = NULL;
    
    KEventHandler::notification_center.addReceiverCallback
            (this, (KCallbackPtr)&KMainMenu::mouseModeChanged, KDL_NOTIFICATION_TYPE_MOUSE_MODE_CHANGED);
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::create ()
{
    KMenuItem * item;
    KMenu * fileMenu			= new KMenu();
    KMenu * viewMenu			= new KMenu();
    KMenu *	viewHandlesMenu 	= new KMenu();
    KMenu *	viewModulatorsMenu	= new KMenu();
    KMenu * 	projectionMenu		= new KMenu();
    KMenu * 	displayModeMenu 	= new KMenu();
    KMenu * windowMenu			= new KMenu();
    KMenu * modulesMenu			= new KMenu();
    KMenu * 	matrixMenu		= new KMenu();
    KMenu * 	attributesMenu		= new KMenu();
    KMenu * 	texturesMenu		= new KMenu();
    //KMenu * 	scenesMenu		= new KMenu();
    //KMenu * 		sceneSetMenu	= new KMenu();
    KMenu * valueMenu			= new KMenu();
    KMenu * 	valueShortcutsMenu	= new KMenu();
    KMenu * editMenu			= new KMenu();
    KMenu * 	editModuleMenu		= new KMenu();
    KMenu * 	resetHandleMenu		= new KMenu();
    KMenu *	selectHandleMenu	= new KMenu();
    KMenu * modulationMenu 		= new KMenu();

#define ADD_OBJECT_CALLBACK \
            item->addReceiverCallback(Controller.modules, (KSetStringPtr)&KModules::addObjectCallback);
         
    addMenuItem(new KSubMenuItem ("file", fileMenu));
        fileMenu->addChild(item = new KMenuItem ("save", KEYS_SAVE));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::save );
        fileMenu->addChild(item = new KMenuItem ("save as ...", KEYS_SAVE_AS));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::saveAs );
        fileMenu->addChild(item = new KMenuItem ("open ...", KEYS_OPEN));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::open );
        fileMenu->addChild(item = new KMenuItem ("close", KEYS_CLOSE));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::close );
        
        fileMenu->addChild(item = new KSubMenuItem ("textures", texturesMenu));
        module_mode_items.push_back(item);
            texturesMenu->addChild(item = new KMenuItem ("texture file", "ALT_t ALT_f"));
            ADD_OBJECT_CALLBACK
            texturesMenu->addChild(item = new KMenuItem ("texture batch", "ALT_t ALT_b"));
            ADD_OBJECT_CALLBACK
            texturesMenu->addChild(item = new KMenuItem ("texture set", "ALT_t ALT_s"));
            ADD_OBJECT_CALLBACK
            texturesMenu->addChild(item = new KMenuItem ("save", "ALT_t s"));
            item->addReceiverCallback(Controller.texture_sets, (KCallbackPtr)&KTextureSets::save );
            texturesMenu->addChild(item = new KMenuItem ("close", "ALT_t w"));
            item->addReceiverCallback(Controller.texture_sets, (KCallbackPtr)&KTextureSets::close );

        fileMenu->addChild(item = new KMenuItem ("quit", KEYS_QUIT));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::quit );
            
    addMenuItem(new KSubMenuItem ("view", viewMenu));

        viewMenu->addChild(item = new KSubMenuItem ("projection", projectionMenu));
            projectionMenu->addChild(item = new KMenuItem ("focus on selection", "f"));
            item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::focusOnSelection );
            projectionMenu->addChild(item = new KMenuItem ("zoom on selection", "z"));
            item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::focusAndZoomOnSelection );
            projectionMenu->addChild(item = new KMenuItem ("camera view", "v"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::cameraView );
            object_mode_items.push_back(item);
            projectionMenu->addChild(item = new KMenuItem ("set reset", "SHIFT_r"));
            item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::setResetProjection );
            projectionMenu->addChild(item = new KMenuItem ("reset", "r"));
            item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::resetProjection );
        
        viewMenu->addChild(item = new KSubMenuItem ("modules", viewModulatorsMenu));
        module_mode_items.push_back(item);
            viewModulatorsMenu->addChild(item = new KStatusMenuItem ("hide modulators", "show modulators",
																						"CTRL_h CTRL_m"));
            item->addReceiverCallback(Controller.modules, (KSetBoolPtr)&KModules::setShowModulators );
            item->setProviderCallback(Controller.modules, (KGetBoolPtr)&KModules::getShowModulators );
            viewModulatorsMenu->addChild(item = new KStatusMenuItem ("hide connections", "show connections",
                                                                                         "CTRL_h CTRL_c"));
            item->addReceiverCallback(Controller.modules, (KSetBoolPtr)&KModules::setShowConnections );
            item->setProviderCallback(Controller.modules, (KGetBoolPtr)&KModules::getShowConnections );
            viewModulatorsMenu->addChild(item = new KStatusMenuItem ("hide inactive", "show inactive",
                                                                                         "CTRL_h CTRL_i"));
            item->addReceiverCallback(Controller.modules, (KSetBoolPtr)&KModules::setShowInactiveModules );
            item->setProviderCallback(Controller.modules, (KGetBoolPtr)&KModules::getShowInactiveModules );
            viewModulatorsMenu->addChild(item = new KStatusMenuItem ("hide textures", "show textures",
                                                                                         "CTRL_h CTRL_t"));
            item->addReceiverCallback(Controller.modules, (KSetBoolPtr)&KModules::setShowTextures );
            item->setProviderCallback(Controller.modules, (KGetBoolPtr)&KModules::getShowTextures );
        
        viewMenu->addChild(item = new KSubMenuItem ("handles", viewHandlesMenu));
        object_mode_items.push_back(item);            
            viewHandlesMenu->addChild(item = new KStatusMenuItem ("hide picked", "show picked",
                                                                                            "CTRL_h p"));
            item->addReceiverCallback(Controller.modules->objects, (KSetBoolPtr)&KObjects::setShowPicked );
            item->setProviderCallback(Controller.modules->objects, (KGetBoolPtr)&KObjects::getShowPicked );
            viewHandlesMenu->addChild(item = new KStatusMenuItem ("hide selected", "show selected",
                                                                                            "CTRL_h s"));
            item->addReceiverCallback(Controller.modules->objects, (KSetBoolPtr)&KObjects::setShowSelected );
            item->setProviderCallback(Controller.modules->objects, (KGetBoolPtr)&KObjects::getShowSelected );
            viewHandlesMenu->addChild(item = new KStatusMenuItem ("hide unselected", "show unselected",
                                                                                            "CTRL_h u"));
            item->addReceiverCallback(Controller.modules->objects, (KSetBoolPtr)&KObjects::setShowUnselected );
            item->setProviderCallback(Controller.modules->objects, (KGetBoolPtr)&KObjects::getShowUnselected );
            viewHandlesMenu->addChild(item = new KStatusMenuItem ("hide cameras", "show cameras",
                                                                                            "CTRL_h c"));
            item->addReceiverCallback(Controller.modules->objects, (KSetBoolPtr)&KObjects::setShowCameras );
            item->setProviderCallback(Controller.modules->objects, (KGetBoolPtr)&KObjects::getShowCameras );
            viewHandlesMenu->addChild(item = new KStatusMenuItem ("hide lights", "show lights",
                                                                                            "CTRL_h l"));
            item->addReceiverCallback(Controller.modules->objects, (KSetBoolPtr)&KObjects::setShowLights );
            item->setProviderCallback(Controller.modules->objects, (KGetBoolPtr)&KObjects::getShowLights );
            viewHandlesMenu->addChild(item = new KMenuItem ("show all"));
            item->addReceiverCallback(Controller.modules->objects, (KSetBoolPtr)&KObjects::showAll );
                
        viewMenu->addChild(item = new KSubMenuItem ("mode", displayModeMenu));
            displayModeMenu->addChild(item = new KStatusMenuItem ("nice & slow", "fast & ugly", "CTRL_d CTRL_u"));
            item->addReceiverCallback(&Controller, (KSetBoolPtr)&KEventHandler::setFastDisplay );
            item->setProviderCallback(&Controller, (KGetBoolPtr)&KEventHandler::getFastDisplay );
        
            displayModeMenu->addChild(item = new KStatusMenuItem ("solid", "wireframe", "CTRL_d w"));
            item->addReceiverCallback(&Controller, (KSetBoolPtr)&KController::setWireframeMode );
            item->setProviderCallback(&Controller, (KGetBoolPtr)&KController::getWireframeMode );
            displayModeMenu->addChild(item = new KStatusMenuItem ("constrained rotation", "free rotation",
                                                                                            "CTRL_r"));
            animation_mode_items.push_back(item); // active in animation mode
            item->addReceiverCallback(&Controller, (KSetBoolPtr)&KController::setFreeRotation );
            item->setProviderCallback(&Controller, (KGetBoolPtr)&KController::getFreeRotation );
            displayModeMenu->addChild(item = new KStatusMenuItem ("window", "fullscreen", "CTRL_d CTRL_f"));
            item->addReceiverCallback(&Controller, (KSetBoolPtr)&KController::setFullscreenMode );
            item->setProviderCallback(&Controller, (KGetBoolPtr)&KController::getFullscreenMode );
#ifdef TEST_MODE
            displayModeMenu->addChild(item = new KStatusMenuItem ("no test", "test", KEYS_TEST));
            item->addReceiverCallback(&Controller, (KSetBoolPtr)&KController::setTestFlag );
            item->setProviderCallback(&Controller, (KGetBoolPtr)&KController::getTestFlag );
            animation_mode_items.push_back(item); // active in animation mode
#endif
            displayModeMenu->addChild(item = new KStatusMenuItem ("hide shortcuts", "show shortcuts",
                                                                                            KEYS_SHORTCUTS));
            item->addReceiverCallback(this, (KSetBoolPtr)&KMainMenu::setShowShortCuts );
            item->setProviderCallback(this, (KGetBoolPtr)(bool (KWidget::*)() const)&KMainMenu::getShowShortCuts );

            displayModeMenu->addChild(item = new KStatusMenuItem ("hide fps", "show fps", "ALT_f"));
            item->addReceiverCallback(&Controller, (KSetBoolPtr)&KController::setDisplayFps );
            item->setProviderCallback(&Controller, (KGetBoolPtr)&KController::getDisplayFps );
            animation_mode_items.push_back(item); // active in animation mode

            displayModeMenu->addChild(item = new KMenuItem ("save screenshot", KEYS_SCREENSHOT));
            item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::saveScreenShot );
            animation_mode_items.push_back(item); // active in animation mode

        viewMenu->addChild(item = new KMenuItem ("show modules", "m")); 
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::startModuleEditing );
        object_mode_items.push_back(item);
        animation_mode_items.push_back(item); // active in animation mode
        viewMenu->addChild(item = new KMenuItem ("show objects", "o"));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::startObjectEditing );
        module_mode_items.push_back(item);
        animation_mode_items.push_back(item); // active in animation mode
        viewMenu->addChild(item = new KMenuItem ("start animation", "p"));
        item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::toggleAnimation );
        animation_mode_items.push_back(item); // active in animation mode
                
    addMenuItem(item = new KSubMenuItem ("matrix", matrixMenu));
    module_mode_items.push_back(item);	
        matrixMenu->addChild(item = new KMenuItem ("transform", "ALT_m m"));
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("scale", "ALT_m s")); 		
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("rotate", "ALT_m r"));
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("translate", "ALT_m t"));		
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("identity", "ALT_m i"));
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("goto", "ALT_m g"));
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("label", "ALT_m l"));
        ADD_OBJECT_CALLBACK
        matrixMenu->addChild(item = new KMenuItem ("matrix hub", "ALT_m h"));
        ADD_OBJECT_CALLBACK
   
    addMenuItem(item = new KSubMenuItem ("objects", modulesMenu));
    module_mode_items.push_back(item);
        modulesMenu->addChild(new KSubMenuItem ("attributes", attributesMenu));
            attributesMenu->addChild(item = new KMenuItem ("color", "ALT_a c"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("texture", "ALT_a t"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("texture (file)", "ALT_a f"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("texture matrix", "ALT_a SHIFT_t"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("material", "ALT_a m"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("blend", "ALT_a b"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("color mask", "ALT_a SHIFT_c"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("size","ALT_a s"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("fog","ALT_a o"));
            ADD_OBJECT_CALLBACK
            attributesMenu->addChild(item = new KMenuItem ("attribute hub", "ALT_a h"));
            ADD_OBJECT_CALLBACK

            modulesMenu->addChild(item = new KMenuItem ("sphere", "ALT_o s"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("cube", "ALT_o c"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("cylinder", "ALT_o y"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("disk", "ALT_o d"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("face", "ALT_o f"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("point", "ALT_o p"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("l-system", "ALT_o SHIFL_l"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("text", "ALT_o t"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("landscape"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("particle emitter", "ALT_o e"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("particle", "ALT_o SHIFT_p"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("vertex", "ALT_o v"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("light", "ALT_o l"));
            ADD_OBJECT_CALLBACK
            modulesMenu->addChild(item = new KMenuItem ("camera", "ALT_o SHIFT_c"));
            ADD_OBJECT_CALLBACK
    addMenuItem(item = new KSubMenuItem ("value", valueMenu));
        valueMenu->addChild(item = new KSubMenuItem ("shortcuts", valueShortcutsMenu));
            valueShortcutsMenu->addChild(item = new KMenuItem ("add modulated variable", "SHIFT+ALT_a"));
            ADD_OBJECT_CALLBACK
            valueShortcutsMenu->addChild(item = new KMenuItem ("multiply modulated variable", "SHIFT+ALT_m"));
            ADD_OBJECT_CALLBACK
            valueShortcutsMenu->addChild(item = new KMenuItem ("multiply and modulo", "SHIFT+ALT_o"));
            ADD_OBJECT_CALLBACK
            valueShortcutsMenu->addChild(item = new KMenuItem ("trigger switches value", "SHIFT+ALT_v"));
            ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("variable", "ALT_v v"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("multiply", "ALT_v m"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("modulo", "ALT_v SHIFT_m"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("add", "ALT_v a"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("switch", "ALT_v s"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("trigger", "ALT_v t"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("accu", "ALT_v c"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("random", "ALT_v r"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("attack", "ALT_v ALT_a"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("decay", "ALT_v ALT_d"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("invert", "ALT_v ALT_i"));
        ADD_OBJECT_CALLBACK
        valueMenu->addChild(item = new KMenuItem ("modulator", "ALT_v ALT_m"));
        ADD_OBJECT_CALLBACK
        /*
        modulesMenu->addChild(new KSubMenuItem ("scenes", scenesMenu));
            scenesMenu->addChild(item = new KMenuItem ("scene", "CTRL_s s"));
            ADD_OBJECT_CALLBACK
            scenesMenu->addChild(item = new KSubMenuItem ("scene set", sceneSetMenu, "CTRL_s CTRL_s"));
            ADD_OBJECT_CALLBACK
                sceneSetMenu->addChild(item = new KMenuItem ("save", "ALT_S s"));
                item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::saveSceneSet );
                sceneSetMenu->addChild(item = new KMenuItem ("open ...", "ALT_S o"));
                item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::open );
                sceneSetMenu->addChild(item = new KMenuItem ("close", "ALT_S w"));
                item->addReceiverCallback(&Controller, (KCallbackPtr)&KController::closeSceneSet );
        */
#undef ADD_OBJECT_CALLBACK

    addMenuItem(item = new KSubMenuItem ("edit", editMenu));
        editMenu->addChild(item = new KMenuItem ("cut", KEYS_CUT));
        module_mode_items.push_back(item);
        item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::cut );
        KEventHandler::menu_key_handler.setSequenceCallback
                                                ("DELETE", item, (KCallbackPtr)&KMenuItem::activate);
        KEventHandler::menu_key_handler.setSequenceCallback
                                                ("BACKSPACE", item, (KCallbackPtr)&KMenuItem::activate);
        editMenu->addChild(item = new KMenuItem ("copy", KEYS_COPY));
        module_mode_items.push_back(item);
        item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::copy );
        editMenu->addChild(item = new KMenuItem ("paste", KEYS_PASTE));
        item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::paste );
        module_mode_items.push_back(item);
        
        editMenu->addChild(item = new KSubMenuItem ("module", editModuleMenu));
        module_mode_items.push_back(item);
            editModuleMenu->addChild(item = new KMenuItem ("center", "SHIFT_c"));
            item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::centerModule );
            editModuleMenu->addChild(item = new KMenuItem ("connect", "c"));
            item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::connect );
            editModuleMenu->addChild(item = new KMenuItem ("disconnect", "d"));
            item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::disconnect );
        
        editMenu->addChild(item = new KSubMenuItem ("reset", resetHandleMenu));
        item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::resetHandle );
            resetHandleMenu->addChild(item = new KMenuItem ("position", "ALT_r p"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::resetHandlePosition );
            resetHandleMenu->addChild(item = new KMenuItem ("rotation", "ALT_r r"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::resetHandleRotation );
            resetHandleMenu->addChild(item = new KMenuItem ("size", "ALT_r s"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::resetHandleSize );
            resetHandleMenu->addChild(item = new KMenuItem ("all", "ALT_r ALT_r"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::resetHandle );
        editMenu->addChild(item = new KSubMenuItem ("select", selectHandleMenu));
            selectHandleMenu->addChild(item = new KMenuItem ("root", "END"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::showRoot );
            selectHandleMenu->addChild(item = new KMenuItem ("parent", "DOWN"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::showParent );
            selectHandleMenu->addChild(item = new KMenuItem ("children", "UP"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::showChildren );
            selectHandleMenu->addChild(item = new KMenuItem ("next sibling", "RIGHT"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::showNextSibling );
            selectHandleMenu->addChild(item = new KMenuItem ("previous sibling", "LEFT"));
            item->addReceiverCallback(Controller.modules->objects,(KCallbackPtr)&KObjects::showPrevSibling );

        editMenu->addChild(item = new KMenuItem ("unpick", KEYS_UNDO));
        module_mode_items.push_back(item);
        item->addReceiverCallback((KObject*)Controller.modules, (KCallbackPtr)&KModules::unpick );

    addMenuItem(item = new KSubMenuItem ("modulation", modulationMenu));
    object_mode_items.push_back(item);
        modulationMenu->addChild(item = new KMenuItem ("reset", "ALT_m ALT_r"));
        item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::resetModulation );
        animation_mode_items.push_back(item); // active in animation mode
        modulationMenu->addChild(item = new KMenuItem ("stop", "ALT_m ALT_s"));
        item->addReceiverCallback(Controller.modules, (KCallbackPtr)&KModules::stopModulation );
        animation_mode_items.push_back(item); // active in animation mode
        modulationMenu->addChild(item = new KStatusMenuItem ("stop mouse modulation", 
                                                            "start mouse modulation", "ALT_m ALT_m"));
        item->addReceiverCallback(Controller.modules->global_modulator, 
                                                    (KSetBoolPtr)&KGlobalModulator::setMouseModulation );
        item->setProviderCallback(Controller.modules->global_modulator, 
                                                    (KGetBoolPtr)(bool (KWidget::*)() const)&KGlobalModulator::getMouseModulation );
        animation_mode_items.push_back(item); // active in animation mode
        modulationMenu->addChild(item = new KStatusMenuItem ("hide status", "show status", "ALT_m ALT_i"));
        item->addReceiverCallback(Controller.modules, (KSetBoolPtr)&KModules::setShowModulatorStatus );
        item->setProviderCallback(Controller.modules, (KGetBoolPtr)&KModules::getShowModulatorStatus );
        animation_mode_items.push_back(item); // active in animation mode

    addMenuItem(item = new KSubMenuItem ("window", windowMenu));
        windowMenu->addChild(item = new KStatusMenuItem ("hide inspector", "show inspector", "i"));
        item->addReceiverCallback(Controller.inspector, (KSetBoolPtr)&KModuleInspector::showOrMaximize );
        item->setProviderCallback(Controller.inspector, (KGetBoolPtr)&KModuleInspector::isVisibleAndMaximized );
        windowMenu->addChild(item = new KStatusMenuItem ("hide console", "show console", "ALT_c"));
        item->addReceiverCallback(KConsole::getConsole(), (KSetBoolPtr)&KConsole::setVisibility );
        item->setProviderCallback(KConsole::getConsole(), (KGetBoolPtr)(bool (KWidget::*)() const)&KConsole::getVisibility );
        windowMenu->addChild(item = new KStatusMenuItem ("hide menu", "show menu", "CTRL_h m"));
        item->addReceiverCallback(this, (KSetBoolPtr)&KMainMenu::setVisibility );
        item->setProviderCallback(this, (KGetBoolPtr)(bool (KWidget::*)() const)&KMainMenu::getVisibility );
        windowMenu->addChild(item = new KStatusMenuItem ("hide preferences", "show preferences", "CTRL_h CTRL_p"));
        item->addReceiverCallback(Controller.preferences, (KSetBoolPtr)&KPreferences::setVisibility );
        item->setProviderCallback(Controller.preferences, (KGetBoolPtr)(bool (KWidget::*)() const)&KPreferences::getVisibility );
        windowMenu->addChild(item = new KMenuItem ("about kodisein", KEYS_ABOUT));
        item->addReceiverCallback(this, (KCallbackPtr)&KMainMenu::displayAboutPanel );
            
    rButton = new KButton ("r");
    tButton = new KButton ("t");
    zButton = new KButton ("z");
    
    rButton->addReceiverCallback(&Controller, (KSetStringPtr)&KController::mouseModeCallback );
    tButton->addReceiverCallback(&Controller, (KSetStringPtr)&KController::mouseModeCallback );
    zButton->addReceiverCallback(&Controller, (KSetStringPtr)&KController::mouseModeCallback );

    modeButtonBox = new KButtonBox ();
    
    modeButtonBox->setBGColor  (*(widget->getBGColor()));
    modeButtonBox->addButton   (rButton);
    modeButtonBox->addButton   (tButton);
    modeButtonBox->addButton   (zButton);
    modeButtonBox->setFrameSpacing(0);
    rButton->activate();
    
    pButton = new KButton ("p");
    pButton->addReceiverCallback(&Controller, (KCallbackPtr)&KController::startAnimation );
    mButton = new KButton ("m");
    mButton->addReceiverCallback(&Controller, (KCallbackPtr)&KController::startModuleEditing );
    oButton = new KButton ("o");
    oButton->addReceiverCallback(&Controller, (KCallbackPtr)&KController::startObjectEditing );
    widget->addChild(modeButtonBox);
    addPickable(modeButtonBox);
    
    startButtonBox = new KButtonBox ();
    startButtonBox->setBGColor (*(widget->getBGColor()));
    startButtonBox->addButton  (pButton);
    startButtonBox->addButton  (mButton);
    startButtonBox->addButton  (oButton);
    startButtonBox->setFrameSpacing(0);
    
    widget->addChild(startButtonBox);
    addPickable(startButtonBox);
 
    layout ();
    initializeIds();
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::layout ()
{
    widget->layout();
    startButtonBox->setPosition(KPosition(0, -240));
    modeButtonBox->setPosition (KPosition(0, -270));
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::mouseModeChanged ()
{
    switch (KEventHandler::getMouseMode())
    {
        case KDL_MOUSE_MODE_ROTATE:    rButton->activate(); break;
        case KDL_MOUSE_MODE_SCALE:     zButton->activate(); break;
        case KDL_MOUSE_MODE_TRANSLATE: tButton->activate(); break;
        default: break;
    }
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::updateAnimationKeyHandler ()
{
    if (animation_key_handler) delete animation_key_handler;
    animation_key_handler = new KKeyActionHandler();
    
    vector<KMenuItem*>::iterator iter = animation_mode_items.begin();
    while (iter != animation_mode_items.end())
    {
        animation_key_handler->setSequenceCallback
                                    ((*iter)->getShortcut(), (*iter), (KCallbackPtr)&KMenuItem::activate);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::applicationModeChanged ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        vector<KMenuItem*>::iterator iter;
        iter = module_mode_items.begin();
        while (iter != module_mode_items.end()) { (*iter)->hide(); iter++; }
	iter = object_mode_items.begin();
        while (iter != object_mode_items.end()) { (*iter)->show(); iter++; }

        oButton->activate();
    }
    else if (mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        vector<KMenuItem*>::iterator iter;
        iter = module_mode_items.begin();
        while (iter != module_mode_items.end()) 
        { 
            (*iter)->show(); 
            iter++; 
        }
	iter = object_mode_items.begin();
        while (iter != object_mode_items.end()) 
        { 
            (*iter)->hide();
            iter++; 
        }
        mButton->activate();
    }

    if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        updateAnimationKeyHandler();
        Controller.removeKeyHandler(&KEventHandler::menu_key_handler);
        Controller.addKeyHandler(animation_key_handler);
    }
    else
    {
        Controller.removeKeyHandler(animation_key_handler);
        Controller.addKeyHandler(&KEventHandler::menu_key_handler);
        delete animation_key_handler; animation_key_handler = NULL;
        layout();
    }
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::projectionHandlerChanged ( const KPickHandler * ph )
{
    if (ph != NULL && ph->isProjectionEnabled())
    {
        getItemWithCallback((KCallbackPtr)&KController::resetProjection)->show();
        getItemWithCallback((KCallbackPtr)&KController::focusOnSelection)->show();
        modeButtonBox->show();
        if (ph->flags[KDL_PICKHANDLER_FLAG_FOCUS_ON_ENABLED])
            getItemWithCallback((KCallbackPtr)&KController::focusOnSelection)->show();
        else
            getItemWithCallback((KCallbackPtr)&KController::focusOnSelection)->hide();        
    }
    else
    {
        getItemWithCallback((KCallbackPtr)&KController::resetProjection)->hide();
        getItemWithCallback((KCallbackPtr)&KController::focusOnSelection)->hide();
        modeButtonBox->hide();
        getItemWithCallback((KCallbackPtr)&KController::focusOnSelection)->hide();        
    }
    
    layout ();
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::setShowShortCuts ( bool b )
{
    if (b != KMenu::show_shortcuts)
    {
        KMenu::show_shortcuts = b;
        layout();
    }
}

// --------------------------------------------------------------------------------------------------------
bool KMainMenu::getShowShortCuts () const
{
    return KMenu::show_shortcuts;
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::displayIntroPanel ()
{
    KMessagePanel::displayMessage("welcome to kodisein!", 
		kStringPrintf("this is kodisein version %3.1f\n\nplease read the manual before using the program.\nit's available at:\n\nhttp://kodisein.sourceforge.net\n\nI hope you enjoy using this software.\nplease send feedback to:\n\nmonsterkodi@users.sourceforge.net\n", KODISEIN_VERSION));
}

// --------------------------------------------------------------------------------------------------------
void KMainMenu::displayAboutPanel ()
{
    KMessagePanel::displayMessage("about kodisein", 
		kStringPrintf("kodisein version %3.1f\n\nkodisein.sourceforge.net\n\n2002,2004 by (monster)kodi\n", KODISEIN_VERSION));
}

