/*
 *  KModules.cpp
 *  kodisein
 */

#include "KModules.h"
#include "KController.h"
#include "KObjects.h"
#include "KLightingProjection.h"
#include "KOrthographicProjection.h"
#include "KConnectorValueOut.h"
#include "KConnectorValueInOut.h"
#include "KConnectorTextureVersionOut.h"
#include "KModuleInspector.h"
#include "KConsole.h"
#include "KTextureSets.h"
#include "KXMLTools.h"

#include <SDL.h>

#include "KModuleObjectText.h"
#include "KModuleParticleEmitter.h"
#include "KModuleParticle.h"
#include "KModuleVertex.h"
#include "KModuleObjectSphere.h"
#include "KModuleObjectBox.h"
#include "KModuleObjectDisk.h"
#include "KModuleObjectCylinder.h"
#include "KModuleObjectLandscape.h"
#include "KModuleObjectFace.h"
#include "KModuleObjectPoint.h"
#include "KModuleIdentity.h"
#include "KModuleLabel.h"
#include "KModuleGoto.h"
#include "KModuleScale.h"
#include "KModuleRotate.h"
#include "KModuleTranslate.h"
#include "KOperationModule.h"
#include "KModuleRandom.h"
#include "KModuleSwitch.h"
#include "KModuleTrigger.h"
#include "KModuleAccu.h"
#include "KFilterModule.h"
#include "KModuleVariable.h"
#include "KGlobalModulator.h"
#include "KModuleCamera.h"
#include "KModuleLight.h"
#include "KModuleColor.h"
#include "KModuleColorMask.h"
#include "KModuleBlend.h"
#include "KModuleSize.h"
#include "KModuleTexture.h"
#include "KModuleTextureFile.h"
#include "KModuleTextureMatrix.h"
#include "KModuleMaterial.h"
#include "KModuleFog.h"
#include "KModuleMatrixHub.h"
#include "KModuleAttributeHub.h"
#include "KModuleLSystem.h"
#include "KTextureSet.h"
#include "KTextureBatch.h"
#include "KTextureFile.h"
#include "KSceneSet.h"
#include "KScene.h"
#include "KConnector.h"

#include <algorithm>

using namespace std;

KDL_CLASS_INTROSPECTION_1 (KModules, KSelectionHandler);

#define MODULE_FOR_NAME(name, className) \
    if (name == className::name()) return new className ();

// --------------------------------------------------------------------------------------------------------
KModule * KModules::newModuleForName ( const string & name )
{
    MODULE_FOR_NAME(name, KModuleMatrix);
    MODULE_FOR_NAME(name, KModuleScale);
    MODULE_FOR_NAME(name, KModuleRotate);
    MODULE_FOR_NAME(name, KModuleTranslate);
    MODULE_FOR_NAME(name, KModuleIdentity);
    MODULE_FOR_NAME(name, KModuleLabel);
    MODULE_FOR_NAME(name, KModuleGoto);
    MODULE_FOR_NAME(name, KModuleMatrixHub);
    MODULE_FOR_NAME(name, KModuleAttributeHub);
    MODULE_FOR_NAME(name, KModuleAdd);
    MODULE_FOR_NAME(name, KModuleMultiply);
    MODULE_FOR_NAME(name, KModuleModulo);
    MODULE_FOR_NAME(name, KModuleAttack);
    MODULE_FOR_NAME(name, KModuleDecay);
    MODULE_FOR_NAME(name, KModuleInvert);
    MODULE_FOR_NAME(name, KModuleRandom);
    MODULE_FOR_NAME(name, KModuleSwitch);
    MODULE_FOR_NAME(name, KModuleTrigger);
    MODULE_FOR_NAME(name, KModuleAccu);
    MODULE_FOR_NAME(name, KModuleVariable);
    MODULE_FOR_NAME(name, KModuleObjectBox);
    MODULE_FOR_NAME(name, KModuleObjectSphere);
    MODULE_FOR_NAME(name, KModuleObjectDisk);
    MODULE_FOR_NAME(name, KModuleObjectCylinder);
    MODULE_FOR_NAME(name, KModuleObjectLandscape);
    MODULE_FOR_NAME(name, KModuleObjectFace);
    MODULE_FOR_NAME(name, KModuleObjectPoint);
    MODULE_FOR_NAME(name, KModuleObjectText);
    MODULE_FOR_NAME(name, KModuleParticleEmitter);
    MODULE_FOR_NAME(name, KModuleParticle);
    MODULE_FOR_NAME(name, KModuleVertex);
    MODULE_FOR_NAME(name, KModuleCamera);
    MODULE_FOR_NAME(name, KModuleLight);
    MODULE_FOR_NAME(name, KModuleColor);
    MODULE_FOR_NAME(name, KModuleColorMask);
    MODULE_FOR_NAME(name, KModuleBlend);
    MODULE_FOR_NAME(name, KModuleSize);
    MODULE_FOR_NAME(name, KModuleTexture);
    MODULE_FOR_NAME(name, KModuleTextureFile);
    MODULE_FOR_NAME(name, KModuleTextureMatrix);
    MODULE_FOR_NAME(name, KModuleMaterial);
    MODULE_FOR_NAME(name, KModuleFog);
    MODULE_FOR_NAME(name, KModuleLSystem);
    MODULE_FOR_NAME(name, KTextureBatch);
    MODULE_FOR_NAME(name, KTextureFile);
    MODULE_FOR_NAME(name, KSceneSet);
    MODULE_FOR_NAME(name, KScene);
    MODULE_FOR_NAME(name, KModulator);
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KModules::addObjectCallback ( const string & itemText )
{
    KModule * module;
         if (itemText == "transform") 		module = new KModuleMatrix ();
    else if (itemText == "scale") 		module = new KModuleScale ();
    else if (itemText == "rotate") 		module = new KModuleRotate ();
    else if (itemText == "translate") 		module = new KModuleTranslate ();
    else if (itemText == "identity") 		module = new KModuleIdentity ();
    else if (itemText == "label") 		module = new KModuleLabel ();
    else if (itemText == "goto") 		module = new KModuleGoto ();
    else if (itemText == "matrix hub") 		module = new KModuleMatrixHub ();
    else if (itemText == "attribute hub")	module = new KModuleAttributeHub ();
    else if (itemText == "cube") 		module = new KModuleObjectBox ();
    else if (itemText == "particle emitter") 	module = new KModuleParticleEmitter ();
    else if (itemText == "particle") 		module = new KModuleParticle ();
    else if (itemText == "vertex") 		module = new KModuleVertex ();
    else if (itemText == "sphere") 		module = new KModuleObjectSphere ();
    else if (itemText == "disk") 		module = new KModuleObjectDisk ();
    else if (itemText == "cylinder") 		module = new KModuleObjectCylinder ();
    else if (itemText == "landscape") 		module = new KModuleObjectLandscape ();
    else if (itemText == "face") 		module = new KModuleObjectFace ();
    else if (itemText == "point") 		module = new KModuleObjectPoint ();
    else if (itemText == "text")		module = new KModuleObjectText ();
    else if (itemText == "light") 		module = new KModuleLight ();
    else if (itemText == "camera") 		module = new KModuleCamera ();
    else if (itemText == "color") 		module = new KModuleColor ();
    else if (itemText == "color mask") 		module = new KModuleColorMask ();
    else if (itemText == "blend") 		module = new KModuleBlend ();
    else if (itemText == "size") 		module = new KModuleSize ();
    else if (itemText == "texture") 		module = new KModuleTexture ();
    else if (itemText == "texture (file)") 	module = new KModuleTextureFile ();
    else if (itemText == "texture matrix") 	module = new KModuleTextureMatrix ();
    else if (itemText == "material") 		module = new KModuleMaterial ();
    else if (itemText == "fog") 		module = new KModuleFog ();
    else if (itemText == "l-system") 		module = new KModuleLSystem ();
    else if (itemText == "variable")		module = new KModuleVariable ();
    else if (itemText == "modulator")		module = new KModulator ();
    else if (itemText == "multiply")		module = new KModuleMultiply ();
    else if (itemText == "modulo")		module = new KModuleModulo ();
    else if (itemText == "add")			module = new KModuleAdd ();
    else if (itemText == "random")		module = new KModuleRandom ();
    else if (itemText == "switch")		module = new KModuleSwitch ();
    else if (itemText == "trigger")		module = new KModuleTrigger ();
    else if (itemText == "accu")		module = new KModuleAccu ();
    else if (itemText == "attack")		module = new KModuleAttack ();
    else if (itemText == "decay")		module = new KModuleDecay ();
    else if (itemText == "invert")		module = new KModuleInvert ();
    else if (itemText == "texture batch")	module = new KTextureBatch ();
    else if (itemText == "texture file")	module = new KTextureFile ();
    else if (itemText == "scene set")		module = new KSceneSet ();
    else if (itemText == "scene")		module = new KScene ();
    else if (itemText == "texture set")
    {
        KModule * batchModule = new KTextureBatch ();
        addModule(batchModule);
        KModule * fileModule = new KTextureFile ();
        addModule(fileModule);
        batchModule->connectModule(fileModule);
        module = KTextureSet::newTextureSet ();
        module->connectModule(batchModule);
    }
    // value shortcuts (should move somewhere (python scriptable?))
    else if (itemText == "multiply modulated variable")		
    {
        KModule * variableModule = new KModuleVariable(1.0);
        addModule(variableModule);
        KModule * multiplyModule = new KModuleMultiply();
        addModule(multiplyModule);
        module = new KModuleMultiply();
        multiplyModule->connectModule(variableModule, multiplyModule->getConnectorWithName("value in 2"));
        module->connectModule(multiplyModule, module->getConnectorWithName("value in 2"));
    }
    else if (itemText == "add modulated variable")		
    {
        KModule * variableModule = new KModuleVariable(360.0);
        addModule(variableModule);
        KModule * multiplyModule = new KModuleMultiply();
        addModule(multiplyModule);
        module = new KModuleAdd();
        multiplyModule->connectModule(variableModule, multiplyModule->getConnectorWithName("value in 2"));
        module->connectModule(multiplyModule, module->getConnectorWithName("value in 2"));
    }
    else if (itemText == "multiply and modulo")		
    {
        KModule * variableModule = new KModuleVariable(2.0);
        addModule(variableModule);
        KModule * moduloModule = new KModuleModulo();
        addModule(moduloModule);
        moduloModule->connectModule(variableModule, moduloModule->getConnectorWithName("value in 2"));
        variableModule = new KModuleVariable(2.0);
        addModule(variableModule);
        
        module = new KModuleMultiply();
        module->connectModule(variableModule, module->getConnectorWithName("value in 2"));
        moduloModule->connectModule(module, moduloModule->getConnectorWithName("value in 1"));
    }
    else if (itemText == "trigger switches value")		
    {
        KModuleTrigger * triggerModule = new KModuleTrigger();
        addModule(triggerModule);
        KModuleVariable * variableModule = new KModuleVariable(1.0);
        addModule(variableModule);
        
        module = new KModuleSwitch();
        module->connectModule(variableModule, module->getConnectorWithName("value in 2"));
        module->connectModule(triggerModule,  module->getConnectorWithName("switch"));
    }
    else
    {
        KConsole::printError("unknown object name");
        return;
    }
    
    addModule(module);
    connectNewModule(module);
}

// --------------------------------------------------------------------------------------------------------
KModules::KModules () : KSelectionHandler ()
{
    Controller.modules = this;

    depth	 = -INT_MAX;
    
    objects	= new KObjects();
    
    projection  = new KLightingProjection();
    projection->setEyeDistance(20.0);
    
    filename	= "";
    
    flags.resize(KDS_MODULES_FLAG_END);
    flags[KDL_PICKHANDLER_FLAG_FOCUS_ON_ENABLED]   	= true;
    flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED] 	= true;
    flags[KDS_MODULES_FLAG_SHOW_MODULATORS]   	  	= true;
    flags[KDS_MODULES_FLAG_SHOW_TEXTURES]   	  	= true;
    flags[KDS_MODULES_FLAG_SHOW_CONNECTIONS]		= true;
    flags[KDS_MODULES_FLAG_SHOW_INACTIVE]		= true;
    flags[KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED] 	= false;
    
    global_modulator = new KGlobalModulator ();
    addPickable(global_modulator);
}

// --------------------------------------------------------------------------------------------------------
KModules::~KModules () 
{
    delete global_modulator;
    delete objects;
}

// --------------------------------------------------------------------------------------------------------
void KModules::displayCameraView (KModuleCamera * cameraModule)
{
    vector<KModule*> 		modules;
    vector<KModule*>::iterator	iter;

    // check, if camera inactive
    modules = cameraModule->getParentModules();
    iter = modules.begin();
    while (iter != modules.end())
    {
        if ((*iter)->getClassId() >= KModuleLabel::classId() && 
            ((KModuleLabel*)(*iter))->getActive() == false)
        {
            return; // camera is inactive -> don't display view
        }
        iter++;
    }

    modules.clear();

    cameraModule->getModulesInHierarchy(modules, true);
    cameraModule->initProjection();

    // light initialization
    GLenum light = GL_LIGHT0 - 1;
    iter = modules.begin();
    while (iter != modules.end())
    {
        if ((*iter)->getClassId() >= KModuleLight::classId())
        {
            ((KModuleLight*)*iter)->initLight(++light);
        }
        iter++;
    }
    if (light >= GL_LIGHT0) 	glEnable(GL_LIGHTING); 
    else  			glDisable(GL_LIGHTING);

    GLint maxLights; glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
    for (GLenum l = light+1; l < (GL_LIGHT0+(GLuint)maxLights); l++) glDisable(l);
    
    // display modules
    cameraModule->getWorldMatrix().glMultMatrix();
    modules.clear();
    modules = cameraModule->getChildModulesOfType(KDS_CONNECTOR_MATRIX_OUT);
    iter = modules.begin();
    while (iter != modules.end())
    {
        (*iter)->display(KDS_APPLICATION_MODE_ANIMATION);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        updateModulation();
        
        global_modulator->initScene();

        // display each camera view
        vector<KModuleCamera*>::iterator cameraIter = camera_handler.cameras.begin();
        while (cameraIter != camera_handler.cameras.end())
        {
            displayCameraView(*cameraIter);
            cameraIter++;
        }
        
        displayModulatorStatus();
        deleteDisplayLists();
    }
    else if ( mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        KPickHandler::display(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::displayModulatorStatus ()
{
    // show modulator status
    global_modulator->displayStatus(flags[KDS_MODULES_FLAG_SHOW_MODULATOR_STATUS]);
}

// --------------------------------------------------------------------------------------------------------
bool depth_comp ( KPickable * a, KPickable * b )
{
    return (((KModule*)a)->getDepthValue() > ((KModule*)b)->getDepthValue());
}

// --------------------------------------------------------------------------------------------------------
void KModules::displayPickables ( int mode )
{
    sort(pickables.begin(), pickables.end(), depth_comp);
    PickableVector::const_iterator iter = pickables.begin();
    while (iter != pickables.end())
    {
        (*iter)->display(mode);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::addValueModule ( KValueModule * vm )
{
    if (find(value_modules.begin(), value_modules.end(), vm) == value_modules.end())
    {
        value_modules.push_back(vm);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::removeValueModule ( KValueModule * vm )
{
    vector<KValueModule*>::iterator result = find(value_modules.begin(), value_modules.end(), vm);
    if (result != value_modules.end())
    {
        value_modules.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::getModulesOfType ( vector<KModule*> & modules, bool activeOnly, const KClassId & cid )
{
    vector<KModule*>::iterator iter = active_root_modules.begin();
    while (iter != active_root_modules.end())
    {
        if (cid.isEmpty() || (*iter)->getClassId() >= cid) 
        {
            modules.push_back(*iter);
        }
        if (cid.isEmpty() || ((*iter)->getClassId() >= KTextureSet::classId()) == false || 
            cid == KTextureFile::classId() || cid == KTextureBatch::classId())
        {
            (*iter)->getModulesInHierarchy(modules, activeOnly, cid);
        }
        iter++;
    }
    if (activeOnly == false)
    {
        iter = hidden_root_modules.begin();
        while (iter != hidden_root_modules.end())
        {
            if (cid.isEmpty() || (*iter)->getClassId() >= cid) 
            {
                modules.push_back(*iter);
            }
            if (cid.isEmpty() || ((*iter)->getClassId() >= KTextureSet::classId()) == false || 
                cid == KTextureFile::classId() || cid == KTextureBatch::classId())
            {
                (*iter)->getModulesInHierarchy(modules, activeOnly, cid);
            }
            iter++;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::setShowInactiveModules ( bool b )
{
    if (b != flags[KDS_MODULES_FLAG_SHOW_INACTIVE])
    {
        flags[KDS_MODULES_FLAG_SHOW_INACTIVE] = b;
        vector<KModule*> labels;
        getModulesOfType(labels, true, KModuleLabel::classId());
        vector<KModule*>::iterator iter = labels.begin();
        while (iter != labels.end())
        {
            if (((KModuleLabel*)*iter)->getActive() == false)
            {
                toggleModuleHierarchy (b, (*iter)->getConnectorWithName("matrix out")->getConnectedModule());
            }
            iter++;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::setShowTextures ( bool b )
{
    if (b != flags[KDS_MODULES_FLAG_SHOW_TEXTURES])
    {
        flags[KDS_MODULES_FLAG_SHOW_TEXTURES] = b;
        toggleRootModulesOfType (b, KTextureSet::classId());
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::resetModulation ()
{
    // reset accu modules
    vector<KModule*> accuModules;
    getModulesOfType (accuModules, true, KModuleAccu::classId());
    vector<KModule*>::iterator iter = accuModules.begin();
    while (iter != accuModules.end())
    {	
        ((KModuleAccu*)*iter)->reset();
        iter++;
    }

    global_modulator->resetModulation();
}

// --------------------------------------------------------------------------------------------------------
void KModules::stopModulation ()
{
    global_modulator->stopModulation();
}

// --------------------------------------------------------------------------------------------------------
void KModules::updateModulation ()
{
    global_modulator->updateModulatorValues();
    
    vector<KValueModule*>::iterator iter = value_modules.begin();
    while (iter != value_modules.end())
    {
        (*iter)->propagateValue(Controller.frame_time);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::setShowModulators ( bool b )
{
    if (b != flags[KDS_MODULES_FLAG_SHOW_MODULATORS])
    {
        flags[KDS_MODULES_FLAG_SHOW_MODULATORS] = b;
        toggleRootModulesOfType (b, KModulator::classId());
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::toggleModuleHierarchy ( bool activate, KModule * rootModule )
{
    if (rootModule == NULL) return;
    vector<KModule*> childModules;
    childModules.push_back(rootModule);
    rootModule->getModulesInHierarchy(childModules, true);
    vector<KModule*>::iterator iter = childModules.begin();
    while (iter != childModules.end())
    {
        if (activate)
        {
            PickableVector::iterator result = find(pickables.begin(), pickables.end(), *iter);
            if (result == pickables.end())
            {
                pickables.push_back(*iter);
            }
        }
        else
        {
            KSelectionHandler::removePickable(*iter);
        }
        iter++;
    }
    initializeIds();
}

// --------------------------------------------------------------------------------------------------------
void KModules::toggleRootModulesOfType ( bool activate, const KClassId & cid )
{
    if (activate) 
    {
        vector<KModule*>::iterator iter = hidden_root_modules.begin();
        while (iter != hidden_root_modules.end())
        {
            if ((*iter)->getClassId() >= cid)
            {
                activateRootModule(*iter);
                toggleModuleHierarchy(activate, *iter);
                iter = hidden_root_modules.erase(iter);
            }
            else iter++;
        }
    }
    else // deactivate
    {
        vector<KModule*>::iterator iter = active_root_modules.begin();
        while (iter != active_root_modules.end())
        {
            if ((*iter)->getClassId() >= cid)
            {
                hidden_root_modules.push_back(*iter);
                toggleModuleHierarchy(activate, *iter);
                iter = active_root_modules.erase(iter);
            }
            else iter++;
        }
    }
    unselectAll();
    initializeIds();
}

// --------------------------------------------------------------------------------------------------------
void KModules::addDisplayListName ( GLuint listName )
{
    display_list_names.push_back(listName);
}
    
// --------------------------------------------------------------------------------------------------------
void KModules::deleteDisplayLists ()
{    
    while (display_list_names.size() != 0)
    {
        glDeleteLists(display_list_names.back(), 1);
        display_list_names.pop_back();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::addModule( KModule * module )
{
    KPickHandler::addPickable(module);    

    if (module->getClassId() >= KModuleCamera::classId())
    {
        camera_handler.addCamera((KModuleCamera*)module);
    }
    else if (module->getClassId() >= KTextureSet::classId())
    {
        Controller.texture_sets->addTextureSet((KTextureSet*)module);
    }
    else if (module->getClassId() == KModulator::classId())
    {
        global_modulator->addModulator((KModulator*)module);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::removePickable( KPickable * pickable )
{
    Controller.inspector->clear();
    if (pickable->getClassId() >= KModuleCamera::classId())
    {
        camera_handler.removeCamera((KModuleCamera*)pickable);
    }
    else if (pickable->getClassId() >= KTextureSet::classId())
    {
        Controller.texture_sets->removeTextureSet((KTextureSet*)pickable);
    }
    else if (pickable->getClassId() >= KModulator::classId())
    {
        global_modulator->removeModulator((KModulator*)pickable);
    }
    
    if (((KModule*)pickable)->isRootModule() && pickable != global_modulator)
    {
        vector<KModule*>::iterator result;
        result = find (active_root_modules.begin(), active_root_modules.end(), pickable);
        if (result != active_root_modules.end())
        {	
            active_root_modules.erase(result);
            vector<KModule*> children = ((KModule*)pickable)->getChildModules();
            vector<KModule*>::iterator iter = children.begin();
            while (iter != children.end())
            {
                toggleModuleHierarchy(true, *iter);
                activateRootModule(*iter);
                iter++;
            }
        }
        else
        {
            result = find (hidden_root_modules.begin(), hidden_root_modules.end(), pickable);
            if (result != hidden_root_modules.end()) 
            {
                hidden_root_modules.erase(result);
                vector<KModule*> children = ((KModule*)pickable)->getChildModules();
                hidden_root_modules.insert(active_root_modules.end(), children.begin(), children.end());
            }
        }
    }
        
    KSelectionHandler::removePickable(pickable);
}

// --------------------------------------------------------------------------------------------------------
void KModules::deletePickable ( KPickable * pickable )
{
    removePickable(pickable);
    if (pickable != global_modulator)
    {
        delete pickable;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::connectNewModule ( KModule * newModule )
{
    KModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        bool wasRoot = pickedModule->isRootModule();
        pickedModule->connectModule(newModule, pickedModule->getPickedConnector());
        if (wasRoot && pickedModule->isRootModule() == false)
        {
            active_root_modules.erase(find(active_root_modules.begin(), active_root_modules.end(), pickedModule));
        }
    }
            
    if (newModule->isRootModule()) 
    {
        activateRootModule(newModule);
    }
    
    unpick();
    
    if (find(pickables.begin(), pickables.end(), newModule) != pickables.end())
    {
        pickModule(newModule);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::connect ()
{
    KConnector * connector;

    // filter connectors from selected pickables
    vector<KConnector*> connectors;
    vector<KConnector*>::iterator connectorIter;
    vector<KSelectable*>::iterator iter = selected_selectables.begin();
    while (iter != selected_selectables.end())
    {
        if ((*iter)->getClassId() >= KConnector::classId())
        {
            connectors.push_back((KConnector*)*iter);
        }
        iter++;
    }

    // enable modulator connection, without selecting the value out connector
    if (picked_pickable && (picked_pickable->getClassId() >= KConnector::classId()) == false)
    {
        connector = getModuleForPickable(picked_pickable)->getConnectorOfType(KDS_CONNECTOR_VALUE_OUT);
        if (connector && connector->isChildConnector())
        {
            connectors.insert(connectors.begin(), connector);
        }
    }

    connector = NULL;
    // if more than 2 connectors selected -> find first unlimited connector
    if (connectors.size() > 2)
    {
        connectorIter = connectors.begin();
        while (connectorIter != connectors.end())
        {
            if ((*connectorIter)->isUnlimited())
            {
                connector = *connectorIter; 
                break;
            }
            connectorIter++;
        }
        
        if (connector == NULL) return;
    }
    else if (connectors.size() == 2)
    {
        if (connectors[0]->isChildConnector()) connector = connectors[0];
        else                                   connector = connectors[1];
        connectors.erase(find(connectors.begin(), connectors.end(), connector));
    }
    else
    {
        return;
    }
    
    connectorIter = connectors.begin();
    while (connectorIter != connectors.end())
    {
        if (connector->getModule() != (*connectorIter)->getModule() &&  // no self connection
            connector->getConnectionType() == (*connectorIter)->getType())
        {
            // we could connect already, but let the module do the connection (see value modules)
            connector->getModule()->connectModule((*connectorIter)->getModule(), connector, (*connectorIter));
        }
        connectorIter++;
    }
    
    updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KModules::disconnect ()
{
    vector<KSelectable*>::iterator iter = selected_selectables.begin();
    while (iter != selected_selectables.end())
    {	
        if ((*iter)->getClassId() >= KConnector::classId())
        {
            ((KConnector*)*iter)->getModule()->disconnectConnector(((KConnector*)*iter));
        }
        iter++;
    }
    
    updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KModules::startPlaying ()
{        
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Controller.addPickHandler(&camera_handler);

    // check for manual cameras
    if (camera_handler.hasManualCameras())
    {
        Controller.setProjectionHandler(&camera_handler);
        camera_handler.startPlaying();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::stopPlaying ()
{
    Controller.removePickHandler(&camera_handler);

    if (camera_handler.hasManualCameras())
    {
        Controller.removeProjectionHandler(&camera_handler);
        camera_handler.stopPlaying();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::startEditing ()
{
    Controller.addPickHandler(this);
    Controller.setProjectionHandler(this);
}

// --------------------------------------------------------------------------------------------------------
void KModules::stopEditing ()
{
    Controller.removePickHandler(this);
    Controller.removeProjectionHandler(this);

}

// --------------------------------------------------------------------------------------------------------
void KModules::toggleShowModulators ()
{
    flags[KDS_MODULES_FLAG_SHOW_MODULATORS] = !flags[KDS_MODULES_FLAG_SHOW_MODULATORS];
}

// --------------------------------------------------------------------------------------------------------
void KModules::updateModuleInspector ()
{
    Controller.inspector->setInspectedModule(getModuleForPickable(picked_pickable));
}

// --------------------------------------------------------------------------------------------------------
void KModules::centerModule()
{
    KModule * pickedModule = getModuleForPickable(picked_pickable);
    
    if (pickedModule)
    {
        KModule * rootModule = pickedModule->getRootModule();
        rootModule->setPosition(rootModule->getPosition() - pickedModule->getPosition());
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::expandModule()
{
    KModule * pickedModule = getModuleForPickable(picked_pickable);
    
    if (pickedModule)
    {
        if (pickedModule->getClassId() >= KObjectModule::classId())
        {
            unselectAll();
            unpick();
            ((KObjectModule*)pickedModule)->expand();
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::cut ()
{
    if (Controller.getApplicationMode() == KDS_APPLICATION_MODE_EDIT_MODULES)
    {	
        KSelectionHandler::cut();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::pasted ( const string & pasteBufferString )
{
    string tmpString = pasteBufferString;
    KModule * newModule = parseXMLForModule(tmpString);
    if (newModule == NULL)
    {
        KConsole::printError("paste operation failed\n(see console for pastebuffer content)");
        KConsole::printf("pastebuffer content:\n%s", pasteBufferString.c_str());
        return;
    }
    resolveConnectorLinks();
    connectNewModule(newModule);
}

// --------------------------------------------------------------------------------------------------------
void KModules::moved ( const KMouseEvent & mouseEvent )
{
    KModule * module = getModuleForPickable(picked_pickable);
    if (module == NULL) return;
    
    module = module->getRootModule();

    KVector posVec = module->getPosition();
    
    if (projection->moveObjectRelativeToWindow(mouseEvent.delta, posVec))
    {
        module->setPosition(posVec);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::pickModule ( KModule * module )
{
    if (picked_pickable == NULL || getModuleForPickable(picked_pickable) != module)
    {
        if (picked_pickable) picked_pickable->setPicked(false);
        picked_pickable = module;
        if (picked_pickable) picked_pickable->setPicked(true);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::selectModulesInVector ( const vector<KModule*> & modules )
{
    vector<KModule*>::const_iterator iter = modules.begin();
    while (iter != modules.end())
    {
        select(*iter);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::picked ()
{
    // select hierarchy if modifier alt pressed
    if (SDL_GetModState() & (KMOD_ALT | KMOD_META) || SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(3))
    {
        vector<KModule*> hierarchyModules;
        getModuleForPickable(picked_pickable)->getModulesInHierarchy(hierarchyModules);
        
        vector<KModule*>::iterator iter = hierarchyModules.begin();
        while (iter != hierarchyModules.end())
        {
            select((*iter));
            iter++;
        }
    }    
}

// --------------------------------------------------------------------------------------------------------
bool KModules::isModulePicked ( KModule * m ) const
{ 
    return (getModuleForPickable(picked_pickable) == m); 
}
                                                        
// --------------------------------------------------------------------------------------------------------
KModule * KModules::getModuleForPickable ( const KPickable * pickable ) const
{
    if (!pickable) return NULL;
    if (pickable->getClassId() >= KModule::classId())
    {
        return (KModule*)pickable;
    }
    else if (pickable->getClassId() >= KConnector::classId())
    {
        return ((KConnector*)pickable)->getModule();
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KModules::focusOnPickedPickable ( bool zoom )
{
    if (picked_pickable == NULL) return;

    projection->focusOn(getModuleForPickable(picked_pickable)->getPosition());
    if (zoom) projection->setEyeDistance(5.0);
}

// --------------------------------------------------------------------------------------------------------
 vector<KModule*> KModules::getRootModules ( bool includeTextureSets ) const
 {
    vector<KModule*> rootModules;
    vector<KModule*>::const_iterator iter = active_root_modules.begin();
    while (iter != active_root_modules.end())
    {
        if (*iter != global_modulator && 
            (includeTextureSets || (*iter)->getClassId() != KTextureSet::classId()))
        {
            rootModules.push_back((*iter));
        }
        iter++;
    }
    return rootModules;
}

// --------------------------------------------------------------------------------------------------------
void KModules::deleteModuleHierarchy ( KModule * module )
{
    if (module == NULL) return;
    vector<KModule*> childModules;
    module->getModulesInHierarchy(childModules);
    vector<KModule*>::iterator iter = childModules.begin();
    while (iter != childModules.end())
    {
        deletePickable(*iter);
        iter++;
    }
    deletePickable(module);
}

// --------------------------------------------------------------------------------------------------------
void KModules::deleteAllModules ()
{
    unpick();
    
    bool showTextures   = getShowTextures();
    bool showModulators = getShowModulators();
    bool showInactive   = getShowInactiveModules();
 
    setShowTextures(true);
    setShowModulators(true);
    setShowInactiveModules(true);

    deleteModuleHierarchy(global_modulator);

    vector<KModule*> rootModules = getRootModules(true);
    vector<KModule*>::iterator iter = rootModules.begin();
    while (iter != rootModules.end())
    {
        deleteModuleHierarchy(*iter);
        iter++;
    }
        
    pickables.clear();
    selected_selectables.clear();
    
    KPickHandler::addPickable(global_modulator);
    
    setShowTextures(showTextures);    
    setShowModulators(showModulators);
    setShowInactiveModules(showInactive);
    
    // center global modulator and set the reset projection
    global_modulator->setPosition(KVector());
    projection->reset();
    pickModule(global_modulator);
    focusOnPickedPickable(true);
    setResetProjection();
}

// --------------------------------------------------------------------------------------------------------
void KModules::resolveGotoLinks ()
{
    vector<KModule*> gotos; 
    getModulesOfType ( gotos, false, KModuleGoto::classId() );
    vector<KModule*>::iterator iter = gotos.begin();
    while (iter != gotos.end())
    {	
        ((KModuleGoto*)*iter)->setLabelName(((KModuleGoto*)*iter)->getLabelName());
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::resolveConnectorLinks ()
{
    if (connector_links.size() == 0) return;

    PickableVector::iterator iter = pickables.begin();
    while (iter != pickables.end())
    {
        if ((*iter)->getClassId() >= KValueModule::classId())
        {
            vector<KConnector*> outConnectors;
            outConnectors = ((KModule*)*iter)->getConnectorsOfType(KDS_CONNECTOR_VALUE_OUT);
            vector<KConnector*>::iterator connectorIter = outConnectors.begin();
            while (connectorIter != outConnectors.end())
            {
                long objectId = ((KConnectorValueOut*)*connectorIter)->getObjectId();
                KConnectorMultiMap::iterator result;
                while ((result = connector_links.find(objectId)) != connector_links.end())
                {
                    (*connectorIter)->connectWithConnector((*result).second);
                    connector_links.erase(result);
                }
                connectorIter++;
            }
        }
        iter++;
    }
    if (connector_links.size() > 0)
    {
        KConsole::printError(kStringPrintf("invalid XML:\nunable to resolve %d link(s)", 
                                                                        connector_links.size()));
        KConnectorMultiMap::iterator iter = connector_links.begin();
        while (iter != connector_links.end())
        {
            KConsole::printf("--> unresolved link id: %ld", (*iter).first);        
            iter++;
        }
    }
    connector_links.clear();
}

// --------------------------------------------------------------------------------------------------------
void KModules::addConnectorLink ( KConnector * inConnector, long outConnectorId )
{
    connector_links.insert(KConnectorMultiMap::value_type(outConnectorId, inConnector));    
}

// --------------------------------------------------------------------------------------------------------
KModule * KModules::parseXMLForModule ( string & xml )
{
    KModule * newModule = NULL;
    string name, attributes;
    
    if (kXMLParseOpenTag(xml, name, &attributes, false) == false) return NULL;
    
    if (name == "GlobalModulator")
    {
        global_modulator->setXMLAttributes(attributes);
        global_modulator->setXML(xml);
        return global_modulator;
    }
    else if (newModule = newModuleForName(name))
    {
        newModule->setXMLAttributes(attributes);
        newModule->setXML(xml);
        addModule(newModule);
    }
    
    return newModule;
}

// --------------------------------------------------------------------------------------------------------
void KModules::activateRootModule ( KModule * rootModule )
{
    vector<KModule*>::iterator result = find(active_root_modules.begin(), active_root_modules.end(), rootModule);
    if (result == active_root_modules.end())
    {
        active_root_modules.push_back(rootModule);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::parseXML ( string & xml )
{
    KModule * rootModule;
    while ((rootModule = parseXMLForModule(xml))) 
    {
        activateRootModule(rootModule);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModules::setXML ( string & xml )
{
    deleteAllModules();
    unpick();
    setShowModulators(true);

    kXMLParseNamedOpenTag(xml, "Modules");
    projection->setXML(xml);
    if (kXMLReadNamedOpenTag(xml, "ResetProjection"))
    {
        kXMLParseNamedOpenTag (xml, "ResetProjection");
        ((KProjection*)getResetProjection())->setXML(xml);
        kXMLParseNamedCloseTag(xml, "ResetProjection");
    }
    parseXML(xml);
    kXMLParseNamedCloseTag(xml, "Modules");
    resolveConnectorLinks();
    resolveGotoLinks();
    
    objects->setXML(xml);
}

// --------------------------------------------------------------------------------------------------------
string KModules::getXML ()
{
    string xml;
    
    xml += kXMLOpenTag("Modules");
    xml += projection->getXML(KDL_XML_INDENT);
    if (reset_projection)
    {
        xml += kXMLOpenTag("ResetProjection", "", KDL_XML_INDENT);
        xml += reset_projection->getXML(KDL_XML_INDENT+KDL_XML_INDENT);
        xml += kXMLCloseTag("ResetProjection", KDL_XML_INDENT);
    }
    xml += global_modulator->getXML(KDL_XML_INDENT);
    
    PickableVector::iterator iter = pickables.begin();
    while (iter != pickables.end())
    {
        if (((KModule*)*iter)->isRootModule() && 
                (((*iter)->getClassId() >= KModulator::classId()) == false) &&
                (((*iter)->getClassId() >= KTextureSet::classId()) == false))
        {
            xml += ((KModule*)*iter)->getXML(KDL_XML_INDENT);
        }
        iter++;
    }
    xml += kXMLCloseTag("Modules");
    
    xml += objects->getXML();

    return xml;
}
