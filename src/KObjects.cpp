/*
 *  KObjects.cpp
 *  kodisein
 */

#include "KObjects.h"
#include "KModules.h"
#include "KCamera.h"
#include "KModuleCamera.h"
#include "KController.h"
#include "KLightingProjection.h"
#include "KConnectorValueInOut.h"
#include "KXMLTools.h"

#include <algorithm>

KDL_CLASS_INTROSPECTION_1 (KObjects, KPickHandler)

// --------------------------------------------------------------------------------------------------------
KObjects::KObjects () : KPickHandler ()
{
    depth	= -INT_MAX;
    projection  = new KLightingProjection();
    projection->setEyeDistance(20.0);
    
    flags.resize(KDS_OBJECTS_FLAG_END);
    flags[KDL_PICKHANDLER_FLAG_FOCUS_ON_ENABLED]   	= true;
    flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED] 	= true;
    flags[KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED] 	= false;    
    flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS]		= true;
    flags[KDS_OBJECTS_FLAG_DISPLAY_LIGHTS]		= true;
    flags[KDS_OBJECTS_FLAG_DISPLAY_HANDLES]		= true;
    flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE]	= true; 
    flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES]	= true;
    flags[KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES]	= false;
    
    current_camera = NULL;
}

// --------------------------------------------------------------------------------------------------------
void KObjects::startEditing ()
{
    Controller.addPickHandler((KPickHandler*)this);
    Controller.setProjectionHandler(this);
    initializeIds();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::stopEditing ()
{
    Controller.removePickHandler((KPickHandler*)this);
    Controller.removeProjectionHandler(this);
}

// --------------------------------------------------------------------------------------------------------
void KObjects::moved ( const KMouseEvent & event )
{
    KHandle * handle = (KHandle*)picked_pickable;
    handle->moved(event);
    Controller.inspector->setInspectedModule(getModuleForPickable(picked_pickable));
}

// --------------------------------------------------------------------------------------------------------
void KObjects::pickHandle ( KHandle * handle )
{
    if (picked_pickable == NULL || ((KHandle*)picked_pickable)->getRootHandle() != handle)
    {
        if (picked_pickable) picked_pickable->setPicked(false);
        picked_pickable = handle;
        if (picked_pickable) picked_pickable->setPicked(true);
    }
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule * KObjects::getModuleForPickable ( const KPickable * pickable ) const
{
    if (pickable == NULL) return NULL;
    return (KMatrixModule*)((KHandle*)pickable)->getRootHandle()->getModule();
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::isProjectionEnabled () const
{
    return (current_camera == NULL);
}

// --------------------------------------------------------------------------------------------------------
void KObjects::cameraView ()
{
    static bool displayCameras = flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS];

    PickableVector::iterator iter;
    
    if (picked_pickable && ((KHandle*)picked_pickable)->getRootHandle()->getClassId() >= KCamera::classId())
    {
        if (current_camera == ((KHandle*)picked_pickable)->getRootHandle())
        {
            current_camera = NULL;
        }
        else
        {
            displayCameras = flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS];
            flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS] = false;
            
            current_camera = (KCamera*)((KHandle*)picked_pickable)->getRootHandle();
        }
    }
    else
    {
        if (current_camera == NULL)
        {
            displayCameras = flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS];
            flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS] = false;

            iter = pickables.begin();
        }
        else
        {
            iter = find(pickables.begin(), pickables.end(), current_camera);
            current_camera = NULL;
            iter++;
        }
        
        while(iter != pickables.end())
        {
            if ((*iter)->getClassId() >= KCamera::classId())
            {
                current_camera = (KCamera*)*iter;
                break;
            }
            iter++;
        }
    }
    
    if (current_camera == NULL)
    {
        // current camera was last camera -> back to projection
        flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS] = displayCameras;
        Controller.setProjectionHandler(this);
        return;
    }
    else
    {
        // notify controller about projection_handler change
        // (don't let the controller or main menu change the camera or saved projection)
        Controller.setProjectionHandler(this);
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showLeaves ()
{
    const KMatrixModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        vector<KModule*> leaves;
        pickedModule->getLeafModules(leaves);
        Controller.modules->unselectAll();
        Controller.modules->selectModulesInVector(leaves);
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showRoot ()
{
    const KMatrixModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        KModule * rootModule = pickedModule->getRootModule();
        if (rootModule != (KModule*)pickedModule)
        {
            rootModule->setPicked(true);
            Controller.modules->selectModulesInVector(rootModule->getChildModules());
        }
    }
    else
    {
        KModule * rootModule = Controller.modules->getRootModules()[0];
        rootModule->setPicked(true);
        Controller.modules->selectModulesInVector(rootModule->getChildModules());
    }
    setShowPicked(true);
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showPrevSibling ()
{
    const KMatrixModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        KMatrixModule * sibling = pickedModule->getPrevSibling();
        if (sibling != pickedModule)
        {
            sibling->setPicked(true);
            Controller.modules->selectModulesInVector(sibling->getChildModules());
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showNextSibling ()
{
    const KMatrixModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        KMatrixModule * sibling = pickedModule->getNextSibling();
        if (sibling != pickedModule)
        {
            sibling->setPicked(true);
            Controller.modules->selectModulesInVector(sibling->getChildModules());
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showChildren ()
{
    const KMatrixModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        KModule * firstChild = pickedModule->getFirstChild();
        if (firstChild)
        {
            Controller.modules->unpick();
            firstChild->setPicked(true);
            Controller.modules->selectModulesInVector(pickedModule->getChildModules());
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showParent ()
{
    const KModule * pickedModule = getModuleForPickable(picked_pickable);
    if (pickedModule)
    {
        KModule * parentModule = pickedModule->getParentModule();
        if (parentModule)
        {
            Controller.modules->unpick();
            parentModule->setPicked(true);
            Controller.modules->selectModulesInVector(parentModule->getChildModules());
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::toggleShowCameras ()
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS] = !flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::toggleShowLights ()
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_LIGHTS] = !flags[KDS_OBJECTS_FLAG_DISPLAY_LIGHTS];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::setShowCameras ( bool b )
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS] = b;
}

// --------------------------------------------------------------------------------------------------------
void KObjects::setShowLights ( bool b )
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_LIGHTS] = b;
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::getShowCameras ()
{
    return flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS];
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::getShowLights ()
{
    return flags[KDS_OBJECTS_FLAG_DISPLAY_LIGHTS];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::toggleShowPicked ()
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE] = !flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::setShowPicked ( bool b )
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE] = b;
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::getShowPicked ()
{
    return flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::toggleShowSelected ()
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES] = !flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::setShowSelected ( bool b )
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES] = b;
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::getShowSelected ()
{
    return flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::setShowUnselected ( bool b )
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES] = b;
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::getShowUnselected ()
{
    return flags[KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES];
}

// --------------------------------------------------------------------------------------------------------
void KObjects::showAll ()
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES] = true;
    flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES]   = true;
    flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE]      = true;
}

// --------------------------------------------------------------------------------------------------------
void KObjects::hideAll ()
{
    flags[KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES] = false;
    flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES]   = false;
    flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE]      = false;
}

// --------------------------------------------------------------------------------------------------------
bool KObjects::shouldModuleDisplayHandles ( KModule * module )
{
    if (flags[KDS_OBJECTS_FLAG_DISPLAY_HANDLES] == false) return false;
    if (Controller.modules->isModulePicked(module)) return flags[KDS_OBJECTS_FLAG_DISPLAY_PICKED_HANDLE];
    if (Controller.modules->isSelected(module))     return flags[KDS_OBJECTS_FLAG_DISPLAY_SELECTED_HANDLES];

    return flags[KDS_OBJECTS_FLAG_DISPLAY_UNSELECTED_HANDLES];        
}

// --------------------------------------------------------------------------------------------------------
void KObjects::resetHandlePosition ()
{
    if (picked_pickable == NULL) return;
    KHandle * rootHandle = ((KHandle*)picked_pickable)->getRootHandle();
    rootHandle->setTX(0); rootHandle->setTY(0); rootHandle->setTZ(0);
    rootHandle->notify();
    Controller.modules->updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::resetHandleRotation ()
{
    if (picked_pickable == NULL) return;
    KHandle * rootHandle = ((KHandle*)picked_pickable)->getRootHandle();
    rootHandle->setRX(0); rootHandle->setRY(0); rootHandle->setRZ(0);
    rootHandle->notify();
    Controller.modules->updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::resetHandleSize ()
{
    if (picked_pickable == NULL) return;
    KHandle * rootHandle = ((KHandle*)picked_pickable)->getRootHandle();
    rootHandle->setSX(1.0); rootHandle->setSY(1.0); rootHandle->setSZ(1.0);
    rootHandle->notify();
    Controller.modules->updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::resetHandle ()
{
    if (picked_pickable == NULL) return;
    KHandle * rootHandle = ((KHandle*)picked_pickable)->getRootHandle();
    rootHandle->reset();
    rootHandle->notify();
    Controller.modules->updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::focusOnPickedPickable ( bool zoom )
{
    if (picked_pickable == NULL) return;
    KHandle * pickedHandle = (KHandle*)picked_pickable;
    if (pickedHandle->getParent())
    {
        projection->focusOn(pickedHandle->getParent()->getWorldMatrix().getPosition());
    }
    else
    {
        projection->focusOn(pickedHandle->getWorldMatrix().getPosition());
    }
    if (zoom) projection->setEyeDistance(4.0);
}

// --------------------------------------------------------------------------------------------------------
KProjection * KObjects::getProjection () 
{ 
    if (current_camera)
    {
        return ((KCamera*)current_camera)->getProjection();
    }
    
    return KPickHandler::getProjection();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::display ( int mode )
{
    Controller.modules->updateModulation();

    if (current_camera)
    {
        ((KModuleCamera*)current_camera->getModule())->initProjection();
    }
    else
    {
        projection->initProjection();
    }

    displayPickables(mode);

    Controller.modules->displayModulatorStatus();
    Controller.modules->deleteDisplayLists();
}

// --------------------------------------------------------------------------------------------------------
void KObjects::displayPickables ( int mode )
{
    if (KEventHandler::flags[KDL_DISPLAY_MODE_WIREFRAME]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else 					      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    PickableVector::iterator iter = Controller.modules->pickables.begin();
    while (iter != Controller.modules->pickables.end())
    {
        if (((KModule*)*iter)->isRootModule())
        {
            ((KModule*)*iter)->display(mode);
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KObjects::setXML ( string & xml )
{
    kXMLParseNamedOpenTag(xml, "Objects");
    projection->setXML(xml);
    if (kXMLReadNamedOpenTag(xml, "ResetProjection"))
    {
        kXMLParseNamedOpenTag (xml, "ResetProjection");
        ((KProjection*)getResetProjection())->setXML(xml);
        kXMLParseNamedCloseTag(xml, "ResetProjection");
    }
    kXMLParseNamedCloseTag(xml, "Objects");
}

// --------------------------------------------------------------------------------------------------------
string KObjects::getXML ()
{
    string xml;
    xml += kXMLOpenTag("Objects");
    xml += projection->getXML(KDL_XML_INDENT);
    if (reset_projection)
    {
        xml += kXMLOpenTag("ResetProjection", "", KDL_XML_INDENT);
        xml += reset_projection->getXML(KDL_XML_INDENT+KDL_XML_INDENT);
        xml += kXMLCloseTag("ResetProjection", KDL_XML_INDENT);
    }
    xml += kXMLCloseTag("Objects");
    return xml;
}
