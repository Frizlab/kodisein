/*
 *  KCameraHandler.cpp
 *  kodisein
 */

#include "KCameraHandler.h"
#include "KModuleCamera.h"
#include "KController.h"
#include "KModules.h"
#include "KGlobalModulator.h"
#include "KConsole.h"

#include <algorithm>

using namespace std;

// --------------------------------------------------------------------------------------------------------
KCameraHandler::KCameraHandler () : KPickHandler ()
{
    flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] = true;
}

// --------------------------------------------------------------------------------------------------------
void KCameraHandler::addCamera ( KModuleCamera * camera )
{
    vector<KModuleCamera*>::iterator cameraIter;
    cameraIter = find(cameras.begin(), cameras.end(), camera);
    if (cameraIter == cameras.end())
    {	
        cameras.push_back(camera);
    }
}

// --------------------------------------------------------------------------------------------------------
void KCameraHandler::removeCamera ( KModuleCamera * camera )
{
    vector<KModuleCamera*>::iterator cameraIter;
    cameraIter = find(cameras.begin(), cameras.end(), camera);
    cameras.erase(cameraIter);
}

// --------------------------------------------------------------------------------------------------------
bool KCameraHandler::hasManualCameras ()
{
    vector<KModuleCamera*>::iterator cameraIter = cameras.begin();
    while (cameraIter != cameras.end())
    {
        if ((*cameraIter)->getManualMode())
        {
            return true;
        }
        cameraIter++;
    }
    
    return false;
}

// --------------------------------------------------------------------------------------------------------
void KCameraHandler::startPlaying ()
{
    vector<KModuleCamera*>::iterator cameraIter = cameras.begin();
    while (cameraIter != cameras.end())
    {
        if ((*cameraIter)->getManualMode())
        {
            KCamera * cameraObject = (KCamera*)(*cameraIter)->getMatrixObject();
            KProjection * cameraProjection = cameraObject->getProjection();
            *(KMatrix*)cameraProjection = *(KMatrix*)cameraObject; // store handle matrix in projection
            saved_cameras.push_back (cameraProjection->copy()); // save projection
        }
        cameraIter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KCameraHandler::stopPlaying ()
{
    vector<KModuleCamera*>::iterator cameraIter = cameras.begin();
    while (cameraIter != cameras.end())
    {
        if ((*cameraIter)->getManualMode()) 
        {
            KCamera * cameraObject = (KCamera*)(*cameraIter)->getMatrixObject();
            KProjection * cameraProjection = cameraObject->getProjection();

            *(KMatrix*)cameraObject = *(KMatrix*)saved_cameras.back(); // restore handle matrix
            *cameraProjection = *(KProjection*)saved_cameras.back(); // restore projection
            
            delete saved_cameras.back(); // delete saved projections
            saved_cameras.pop_back();
        }
        cameraIter++;
    }
}

// --------------------------------------------------------------------------------------------------------
bool KCameraHandler::mouseMotion ( const KMouseEvent & mouseEvent )
{
    KSize screenSize(KEventHandler::getScreenSize());
    float xValue = mouseEvent.pos.x / (float)screenSize.w;
    float yValue = mouseEvent.pos.y / (float)screenSize.h;
    Controller.modules->global_modulator->setMouseValues(xValue, yValue);
    return false;
}

// --------------------------------------------------------------------------------------------------------
void KCameraHandler::updateProjection ( const KMouseEvent & mouseEvent )
{
    vector<KModuleCamera*>::iterator cameraIter = cameras.begin();
    while (cameraIter != cameras.end())
    {
        if ((*cameraIter)->getManualMode())
        {
            int mouseMode = KDL_MOUSE_MODE_ROTATE;
            if (SDL_GetModState() & KMOD_CTRL || mouseEvent.button_state == SDL_BUTTON(3))
            {
                mouseMode = KDL_MOUSE_MODE_TRANSLATE;
            }
            else if (SDL_GetModState() & KMOD_ALT || mouseEvent.button_state == SDL_BUTTON(2))
            {
                mouseMode = KDL_MOUSE_MODE_SCALE;
            }

            KCamera * camera = (KCamera*)((*cameraIter)->getMatrixObject());
            if (camera)
            {
                projection = camera->getProjection();
                *(KMatrix*)projection = *(KMatrix*)camera;
                updateProjectionFromEventInMode (projection, mouseEvent, mouseMode);
                *(KMatrix*)camera = *(KMatrix*)projection;
            }
        }
        
        cameraIter++;
    }
}
