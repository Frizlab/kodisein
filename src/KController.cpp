/*
 *  KController.cpp
 *  kodisein
 */

#include "KController.h"
#include "KKeyHandler.h"
#include "KPreferences.h"
#include "KMainMenu.h"
#include "KModules.h"
#include "KObjects.h"
#include "KConsole.h"
#include "KGlobalModulator.h"
#include "KKeyHandler.h"
#include "KFileTreeWindow.h"
#include "KPickHandler.h"
#include "KOrthographicProjection.h"
#include "KPerspectiveProjection.h"
#include "KTextureSets.h"
#include "KSceneSet.h"
#include "KMessagePanel.h"
#include "KTrash.h"
#include "KFileHandler.h"
#include "KFileTools.h"
#include "KXMLTools.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 (KController, KEventHandler)

float KODISEIN_VERSION = 1.0;
                
// --------------------------------------------------------------------------------------------------------
KController::KController () : KEventHandler ()
{
    mode = -1;
    scene_set = NULL;
    
    modules   	 = NULL;
    main_menu	 = NULL;
    inspector	 = NULL;
    file_browser = NULL;
    texture_sets = NULL;
}

// --------------------------------------------------------------------------------------------------------
bool KController::init ()
{
    KFileHandler::init();

    preferences = new KPreferences();
    preferences->setPosition(KPosition(80, -20));
    preferences->config_file = app_name + ".cfg";
    preferences->load();
    
    if (KEventHandler::setScreenSize(preferences->window_size, false) == false) 
    {
        KConsole::printError("trying to use 800x600 mode");
        if (KEventHandler::setScreenSize(KSize(800, 600), false) == false)
        {
            return false;
        }
    }
    
    // create and initialize controllers and pickhandlers
    notification_center.addReceiverCallback(this, (KCallbackPtr)&KController::projectionHandlerChanged, 
                                KDL_NOTIFICATION_TYPE_PROJECTION_HANDLER_CHANGED); // what a hack!

    KConsole::create();
    KConsole::getConsole()->setPosition(KPosition(80, -20));
    KConsole::getConsole()->setSize(KSize(300, 200));
    
    inspector = new KModuleInspector();
    inspector->setPosition(KPosition(100, 300));
    
    file_browser = new KFileTreeWindow();
    file_browser->setPosition(KPosition(80, -10));
    file_browser->setSize(KSize(500, 500));

    // texture_sets has to be created before modules because global modulator references it
    texture_sets = new KTextureSets();

    modules = new KModules ();

    main_menu = new KMainMenu();
    main_menu->create();

    if (!preferences->menu_xml.empty())
    {	
        // set user defined shortcuts
        main_menu->setXML(preferences->menu_xml);
    }
    else
    {
        main_menu->displayIntroPanel();
    }

    if (kFileIsFile(preferences->default_project))
    {
        openKodiseinFile(preferences->default_project);
    }

    addPickHandler((KPickHandler*)KConsole::getConsole());
    addPickHandler((KPickHandler*)inspector);
    addPickHandler((KPickHandler*)file_browser);
    addPickHandler((KPickHandler*)preferences);
    addPickHandler((KPickHandler*)main_menu);
    
    //KConsole::printf("GL_VERSION\t\t\t%s",	glGetString(GL_VERSION));
    //KConsole::printf("GL_RENDERER\t\t\t%s",	glGetString(GL_RENDERER));
    //KConsole::printf("GL_VENDOR\t\t\t%s",	glGetString(GL_VENDOR));
    
    //string extensions((char*)glGetString(GL_EXTENSIONS));
    //kStringReplace(extensions, " ", "\n\t");
    //kStringReplaceTabs(extensions, 21);
    //KConsole::printf("GL_EXTENSIONS\t\t%s", 	extensions.c_str());
    //KConsole::printf("GLUT_API_VERSION\t%d", GLUT_API_VERSION);

    startModuleEditing();
    resetLighting();

	KEventHandler::notification_center.addReceiverCallback
        (this, (KCallbackPtr)&KController::reloadTextures, KDL_NOTIFICATION_TYPE_VIDEO_MODE_CHANGED);

	
    return true;
}

// --------------------------------------------------------------------------------------------------------
void KController::quit ()
{
    preferences->save();
    exit(0);
}

// --------------------------------------------------------------------------------------------------------
void KController::displayPickHandlers ()
{
    if (mode != KDS_APPLICATION_MODE_ANIMATION)
    {
        KEventHandler::displayPickHandlers();
    }
    else // (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        Controller.modules->display(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::applicationModeChanged ()
{
    main_menu->applicationModeChanged (mode);
    
    // stop old mode
    if (old_mode == KDS_APPLICATION_MODE_EDIT_OBJECTS) 
    {
        modules->objects->stopEditing();
    }
    else if (old_mode == KDS_APPLICATION_MODE_EDIT_MODULES) 
    {
        modules->stopEditing();
        if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS) // from module to object editing: clean start 
        {
            modules->resetModulation();
        }
    }
    else if (old_mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        modules->stopPlaying();
    }
    
    // starting new mode ...
    
    // deactivate modulation handler in module edit mmode
    if (mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        removeKeyHandler(&mod_key_handler); // remove modulation handler
    }
    else
    {
        addKeyHandler(&mod_key_handler); // add modulation handler
    }
    
    // recover from animation mode 
    // -> reset lighting and projection handler (maybe cursor?)
    if (mode != KDS_APPLICATION_MODE_ANIMATION) 
    {
        resetLighting();
        // show cursor
    }
    else
    {
        // hide cursor
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::startModuleEditing ()
{	
    if (mode != KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        old_mode = mode;
        mode = KDS_APPLICATION_MODE_EDIT_MODULES;
        applicationModeChanged();
        modules->startEditing();
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::startObjectEditing ()
{
    if (mode != KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        old_mode = mode;
        mode = KDS_APPLICATION_MODE_EDIT_OBJECTS;
        applicationModeChanged();
        modules->objects->startEditing();
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::toggleAnimation ()
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION) 
    {
        stopAnimation();
    }
    else 
    {
        startAnimation();
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::startAnimation ()
{
    if (mode != KDS_APPLICATION_MODE_ANIMATION)
    {
        old_mode = mode;
        mode = KDS_APPLICATION_MODE_ANIMATION;
        applicationModeChanged();
        modules->startPlaying();
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::stopAnimation ()
{
    if (old_mode == KDS_APPLICATION_MODE_EDIT_OBJECTS) 
    {
        startObjectEditing();
    }
    else					       
    {
        startModuleEditing();
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::projectionHandlerChanged ()
{
    if (projection_handler == NULL)
    {
        if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS) 
        {
            projection_handler = Controller.modules->objects;
        }
        else if (mode == KDS_APPLICATION_MODE_EDIT_MODULES) 
        {
            projection_handler = Controller.modules;
        }
    }
    
    main_menu->projectionHandlerChanged(projection_handler);
}

// --------------------------------------------------------------------------------------------------------
void KController::setFastDisplay ( bool b )
{
    KEventHandler::setFastDisplay(b);
    if (b) modules->setShowConnections(false);
}

// --------------------------------------------------------------------------------------------------------
void KController::setFullscreenMode ( bool fullScreen )
{
    KEventHandler::setScreenSize(fullScreen ? preferences->fullscreen_size : preferences->window_size, 
                                 fullScreen);
	/*
    texture_sets->reload();
    resetLighting();
	*/
}

// --------------------------------------------------------------------------------------------------------
void KController::reloadTextures ()
{
	texture_sets->reload();
    resetLighting();
}

// --------------------------------------------------------------------------------------------------------
bool KController::checkHeaderInFileWithName ( const string & filename )
{
    // read header 
    string xml = kFileReadStringFromFile ( filename, 30 );
    
    string attributes;
    if (kXMLParseNamedOpenTag(xml, "KODISEIN", &attributes) == "")
    {
        KConsole::printError(kStringPrintf("not a kodisein file '%s'", filename.c_str()));
        return false;
    }
    else
    {
        string fileVersionString = kXMLReadNamedAttribute(attributes, "version");
        float fileVersion = (float)atof(fileVersionString.c_str());
        
        if (fileVersion < KODISEIN_VERSION)
        {
            KConsole::printf("[WARNING] old xml version '%g' (should be '%g')",  fileVersion, KODISEIN_VERSION);
        }
    }

    return true;
}

// --------------------------------------------------------------------------------------------------------
string KController::getXMLFromFileWithName ( const string & filename )
{
    if (kFileExists(filename) == false) return "";
    if (checkHeaderInFileWithName(filename) == false) return "";
    string xml = kFileReadStringFromFile ( filename );
    kXMLParseNamedOpenTag(xml, "KODISEIN");
    return xml;
}

// --------------------------------------------------------------------------------------------------------
bool KController::saveXMLInFileWithName ( const string & xml, const string & filename )
{   
    string kodiseinXML = kXMLTag("KODISEIN", kStringPrintf("version='%g'", KODISEIN_VERSION)) + xml;
    return kFileWriteStringToFile(kodiseinXML, filename);
}

// --------------------------------------------------------------------------------------------------------
void KController::saveScreenShot ()
{
    static int counter = -1;
    KSize screenSize = getScreenSize();
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
#endif
    amask = 0x00000000;

    void * pixels = malloc (screenSize.w * screenSize.h * sizeof(GLuint));
    glReadPixels (0, 0, screenSize.w, screenSize.h, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pixels);
    
    //............................................................ reverse order of lines (mirror vertical)
    int scanlineLength = screenSize.w * sizeof(GLuint);
    void * scanline = malloc (scanlineLength);
    for (int lineIndex = 0; lineIndex < screenSize.h/2; lineIndex++)
    {
        memcpy (scanline, 					// copy from bottom to save line
                &((char*)pixels)[lineIndex * scanlineLength], 
                scanlineLength);
        memcpy (&((char*)pixels)[lineIndex * scanlineLength],   // copy from top to bottom
                &((char*)pixels)[(screenSize.h-lineIndex-1) * scanlineLength], 
                scanlineLength);				// copy from save line to top
        memcpy (&((char*)pixels)[(screenSize.h-lineIndex-1) * scanlineLength], 
                scanline, 
                scanlineLength);
    }
    
    //............................................................ create SDL_surface from pixels
    SDL_Surface * saveSurface = SDL_CreateRGBSurfaceFrom (pixels, screenSize.w, screenSize.h, 32,
                                                          screenSize.w * 4, rmask, gmask, bmask, amask);
    
    free (scanline);
    
    if (saveSurface == NULL)
    {
        KConsole::printf("WARNING unable to copy screen surface for screenshot");
        free (pixels);
        return;
    }
    
    string screenShotFile;
    
    //............................................................ search for a free file name
    do  
    {
        counter++;
        if (!preferences->getScreenShotsDir().empty())
        {
            screenShotFile = kFileSubstitutePath(preferences->getScreenShotsDir()) + 
                                "/" + kStringPrintf("kodisein_screenshot_%03d.bmp", counter);
        }
        else
        {
            screenShotFile = kStringPrintf("kodisein_screenshot_%03d.bmp", counter);
        }
    }
    while (kFileExists(screenShotFile));
    
    //............................................................ save the screenshot
    if (SDL_SaveBMP(saveSurface, screenShotFile.c_str()) == 0) 
    {
        KConsole::printf("screenshot saved to file %s", kFileAbsPathName(screenShotFile).c_str());
    }
    else // ooops...
    {
        KConsole::printf("WARNING unable to write screenshot to file %s", screenShotFile.c_str());
    }
    
    SDL_FreeSurface(saveSurface);
    free (pixels);
}

// --------------------------------------------------------------------------------------------------------
void KController::saveProjectFile ( const string & filename )
{    
    string xml;
    
    modules->setFileName(filename);
    xml += modules->getXML();
    
    if (saveXMLInFileWithName(xml, filename))
    {
        file_browser->hide();
        KFileHandler::changeCurrentDir(kFileDirName(filename)); // change to project directory
    }
    else
    {
        // don't save doc if saving of project file failed
        return;
    }
    
    // ......................................................................... save project documentation
    string html;
    
    html = kFileReadStringFromFile (kFileDirName(preferences->config_file) + "docTemplate.html");
    
    if (!html.empty())
    {
        kStringInsertStringBehindTags (html, filename, "<!--project file-->");
        kStringInsertStringBehindTags (html, modules->global_modulator->getDocumentation(), 
                                                        "<!--project documentation-->");

        string docname = kFileDirName(filename) + kFileBaseName(filename, true) + ".html";
        
        kFileWriteStringToFile(html, docname);
    }
    
    modules->updateModuleInspector();
}

// --------------------------------------------------------------------------------------------------------
void KController::openKodiseinFile ( const string & filename )
{
    string xml = getXMLFromFileWithName(filename);
    if (!xml.empty())
    {
        if (kXMLReadNamedOpenTag(xml, "TextureSet"))
        {
            texture_sets->setCurrentTextureSetFileName(filename);
            file_browser->hide();
        }
        else
        {
            KFileHandler::changeCurrentDir(kFileDirName(filename)); // change to project directory
            file_browser->hide();
            modules->setXML(xml);
            modules->setFileName(kFileBaseName(filename));
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::open ()
{
    file_browser->addReceiverCallback(this, (KSetStringPtr)&KController::openKodiseinFile);
    file_browser->setOpenFileMode(true);
    file_browser->show();
}

// --------------------------------------------------------------------------------------------------------
void KController::close ()
{
    texture_sets->setCurrentTextureSetFileName("");
    modules->deleteAllModules();
    modules->setFileName("");
}

// --------------------------------------------------------------------------------------------------------
void KController::saveAs ()
{
    file_browser->addReceiverCallback(this, (KSetStringPtr)&KController::saveProjectFile);
    file_browser->setOpenFileMode(false);
    file_browser->show();
}

// --------------------------------------------------------------------------------------------------------
void KController::save ()
{
    if (modules->getFileName() == "")
    {
        saveAs();
    }
    else
    {
        saveProjectFile(modules->getFileName());
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::openSceneSetFile ( const string & fn )
{
    string sceneSetFile = fn;
    
    string xml = Controller.getXMLFromFileWithName(sceneSetFile);
    if (!xml.empty())
    {
        file_browser->hide();
        Controller.modules->unpick();
        closeSceneSet();
        scene_set = (KSceneSet*)Controller.modules->parseXMLForModule(xml);
        scene_set->setFileName(sceneSetFile);
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::openSceneSet ()
{
    file_browser->addReceiverCallback(this, (KSetStringPtr)&KController::openSceneSetFile);
    file_browser->show();
}

// --------------------------------------------------------------------------------------------------------
void KController::saveSceneSet ()
{
    if (scene_set != NULL)
    {
        scene_set->save();
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::closeSceneSet ()
{
    Controller.modules->deleteModuleHierarchy(scene_set);
}

// --------------------------------------------------------------------------------------------------------
void KController::mouseModeCallback ( const string & buttonText )
{	
    if      (buttonText == "r") mouse_mode = KDL_MOUSE_MODE_ROTATE;
    else if (buttonText == "t") mouse_mode = KDL_MOUSE_MODE_TRANSLATE;
    else if (buttonText == "z") mouse_mode = KDL_MOUSE_MODE_SCALE;
}

// --------------------------------------------------------------------------------------------------------
void KController::handleMouseButtonEvent ( SDL_MouseButtonEvent & event)
{
    KEventHandler::handleMouseButtonEvent(event);
    
    if (event.state == SDL_RELEASED)
    {
        setMouseMode(KDL_MOUSE_MODE_ROTATE);
    }
}

// --------------------------------------------------------------------------------------------------------
void KController::handleUserEvent ( SDL_UserEvent & event )
{
    switch (event.code)
    {
        case KDL_NOTIFICATION_TYPE_APPLICATION_OPEN_FILE:
            openKodiseinFile(string((const char *)event.data1));
            free (event.data1);
            break;
        default:
            KEventHandler::handleUserEvent(event);
    }
}


