/*
 *  KPreferences.cpp
 *  kodisein
 */

#include "KPreferences.h"
#include "KModules.h"
#include "KFileTools.h"
#include "KGlobalModulator.h"
#include "KFloatValueObject.h"
#include "KBoolValueObject.h"
#include "KSizeValueObject.h"
#include "KKeyValueObject.h"
#include "KFileNameValueObject.h"
#include "KFloatValueObject.h"
#include "KXMLTools.h"
#include "KMainMenu.h"
#include "KIconButton.h"
#include "KButtonBox.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 ( KPreferences, KWindow )

#define TAB_NAME_MODULATION_KEYS   "modulation keys"
#define TAB_NAME_DEFAULT_PROJECT   "default project"
#define TAB_NAME_SCREEN_SIZES 	   "screen sizes"
#define TAB_NAME_MISC	 	   "misc"

// --------------------------------------------------------------------------------------------------------
KPreferences::KPreferences() : KWindow ( KDL_WINDOW_FEATURES_CLOSE_BUTTON | KDL_WINDOW_FEATURES_PROJECTION )
{
    default_project		= "";
    last_project_by_default	= true;

    screenshots_dir		= ".";

    fullscreen_size		= KSize(1024, 768);
    window_size			= KSize(1024, 695);
    global_activation_key	= "ESCAPE";
    mouse_activation_key	= "CTRL_ESCAPE";
    reset_key 		 	= "PAGEDOWN";
    value_up_key		= "UP";
    value_down_key		= "DOWN";
    speed_up_key		= "RIGHT";
    speed_down_key		= "LEFT";
    speed_multiply_key		= "KPMULTIPLY";
    speed_divide_key		= "KPDIVIDE";
    start_stop_key		= "RETURN";
    smooth_start_key		= "HOME";
    smooth_stop_key		= "END";
    bind_mouse_x_key		= "CTRL_x";
    bind_mouse_y_key		= "CTRL_z";

    flags[KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED] 	= true;

    button_widget->addChild(new KLabel("preferences"));

    values_widget = new KWidgetArray ();
    values_widget->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    values_widget->flags[KDL_WIDGET_FLAG_FRAMED]	  = true;
    widget->addChild(values_widget);
    widget->hide();
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::show ()
{
    createPreferenceTabs();
    widget->layout();
    widget->show();
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::hide ()
{
    KPickHandler::removeAllPickables(); // remove all pickables
    values_widget->clear();		// delete all children on values_widget
    addPickable(widget);		// add removed pickables again
    addPickable(close_button);
    widget->hide();
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::setGlobalActivationKey ( const string & activationKey )
{
    global_activation_key = activationKey;
    if (Controller.modules != NULL)
    {
        Controller.modules->global_modulator->setActivationKey(global_activation_key);
    }
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::tabButtonCallback ( const string & buttonText )
{
    if (buttonText == TAB_NAME_MODULATION_KEYS)
    {
        modulator_tab->show();
        screen_tab->hide();
        default_project_tab->hide();
        misc_tab->hide();
    }
    else if (buttonText == TAB_NAME_SCREEN_SIZES)
    {
        screen_tab->show();
        modulator_tab->hide();
        default_project_tab->hide();
        misc_tab->hide();
    }
    else if (buttonText == TAB_NAME_DEFAULT_PROJECT)
    {
        modulator_tab->hide();
        screen_tab->hide();
        default_project_tab->show();
        misc_tab->hide();
    }
    else if (buttonText == TAB_NAME_MISC)
    {
        modulator_tab->hide();
        screen_tab->hide();
        default_project_tab->hide();
        misc_tab->show();
    }
    
    layout();
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::createPreferenceTabs ()
{
    KButtonBox * tabButtons = new KButtonBox();
    tabButtons->setFrameSpacing(0);
    values_widget->addChild(tabButtons);

    //............................................................... tab buttons
    KButton * screenButton    = new KButton (TAB_NAME_SCREEN_SIZES);
    tabButtons->addButton(screenButton);
    screenButton->addReceiverCallback(this, (KSetStringPtr)&KPreferences::tabButtonCallback);
    addPickable(screenButton);

    KButton * modulatorButton = new KButton (TAB_NAME_MODULATION_KEYS);
    tabButtons->addButton(modulatorButton);
    modulatorButton->addReceiverCallback(this, (KSetStringPtr)&KPreferences::tabButtonCallback);
    addPickable(modulatorButton);

    KButton * defaultProjectButton = new KButton (TAB_NAME_DEFAULT_PROJECT);
    tabButtons->addButton(defaultProjectButton);
    defaultProjectButton->addReceiverCallback(this, (KSetStringPtr)&KPreferences::tabButtonCallback);
    addPickable(defaultProjectButton);

    KButton * miscButton = new KButton (TAB_NAME_MISC);
    tabButtons->addButton(miscButton);
    miscButton->addReceiverCallback(this, (KSetStringPtr)&KPreferences::tabButtonCallback);
    addPickable(miscButton);

    //............................................................... tab widgets
    //............................................................... screen size preferences 
    screen_tab = new KWidgetArray();
    screen_tab->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    screen_tab->flags[KDL_WIDGET_FLAG_FRAMED] = true;
    values_widget->addChild(screen_tab); 

    KSizeValueObject * windowSize = new KSizeValueObject ("window size");
    windowSize->addReceiverCallback(this, (KSetSizePtr)&KPreferences::setWindowSize);
    windowSize->setProviderCallback(this, (KGetSizePtr)&KPreferences::getWindowSize);
    windowSize->addToWidget(screen_tab);
    
    KSizeValueObject * fullscreenSize = new KSizeValueObject ("fullscreen size");
    fullscreenSize->addReceiverCallback(this, (KSetSizePtr)&KPreferences::setFullscreenSize);
    fullscreenSize->setProviderCallback(this, (KGetSizePtr)&KPreferences::getFullscreenSize);
    fullscreenSize->addToWidget(screen_tab);
    
    KWidgetArray * applyArray = new KWidgetArray();
    screen_tab->addChild(applyArray);
    applyArray->addChild(new KLabel(""));
    KButton * applyButton = new KButton("apply");
    applyButton->addReceiverCallback(this, (KCallbackPtr)&KPreferences::applyVideoMode);
    applyArray->addChild(applyButton);
    addPickable(applyButton);
    
    screen_tab->alignLabels();

    // ............................................................... modulator preferences 
    modulator_tab = new KWidgetArray();
    modulator_tab->flags[KDL_WIDGET_FLAG_FRAMED] = true;
    values_widget->addChild(modulator_tab);
    
    KWidgetArray * leftColumn = new KWidgetArray();
    leftColumn->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    modulator_tab->addChild(leftColumn);
    KWidgetArray * rightColumn = new KWidgetArray();
    rightColumn->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    modulator_tab->addChild(rightColumn);

    KKeyValueObject * keyValue;
    keyValue = new KKeyValueObject( "global modulator", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setGlobalActivationKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getGlobalActivationKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "mouse activation", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setMouseActivationKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getMouseActivationKey);
    keyValue->addToWidget(rightColumn);

    keyValue = new KKeyValueObject( "start/stop", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setStartStopKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getStartStopKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "reset", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setResetKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getResetKey);
    keyValue->addToWidget(rightColumn);

    keyValue = new KKeyValueObject( "smooth start", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setSmoothStartKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getSmoothStartKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "smooth stop", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setSmoothStopKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getSmoothStopKey);
    keyValue->addToWidget(rightColumn);

    keyValue = new KKeyValueObject( "speed up", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setSpeedUpKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getSpeedUpKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "speed down", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setSpeedDownKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getSpeedDownKey);
    keyValue->addToWidget(rightColumn);

    keyValue = new KKeyValueObject( "speed multiply", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setSpeedMultiplyKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getSpeedMultiplyKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "speed divide", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setSpeedDivideKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getSpeedDivideKey);
    keyValue->addToWidget(rightColumn);

    keyValue = new KKeyValueObject( "value up", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setValueUpKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getValueUpKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "value down", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setValueDownKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getValueDownKey);
    keyValue->addToWidget(rightColumn);

    keyValue = new KKeyValueObject( "bind mouse x", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setBindMouseXKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getBindMouseXKey);
    keyValue->addToWidget(leftColumn);

    keyValue = new KKeyValueObject( "bind mouse y", 1 );
    keyValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setBindMouseYKey);
    keyValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getBindMouseYKey);
    keyValue->addToWidget(rightColumn);

    leftColumn->alignLabels();
    rightColumn->alignLabels();

    // ............................................................... default project preferences 
    default_project_tab = new KWidgetArray();
    default_project_tab->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    default_project_tab->flags[KDL_WIDGET_FLAG_FRAMED] = true;
    values_widget->addChild(default_project_tab); 

    KFileNameValueObject * filenameValue;
    filenameValue = new KFileNameValueObject("default project file");
    filenameValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setDefaultProjectFile);
    filenameValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getDefaultProjectFile);
    filenameValue->addToWidget(default_project_tab);

    KBoolValueObject * boolValue = new KBoolValueObject ("last project is default");
    boolValue->addReceiverCallback (this, (KSetBoolPtr)&KPreferences::setLastProjectByDefault);
    boolValue->setProviderCallback (this, (KGetBoolPtr)(bool (KWidget::*)() const)&KPreferences::getLastProjectByDefault);
    boolValue->addToWidget(default_project_tab);

    default_project_tab->alignLabels();

    // ............................................................... misc preferences 
    misc_tab = new KWidgetArray();
    misc_tab->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    misc_tab->flags[KDL_WIDGET_FLAG_FRAMED] = true;
    values_widget->addChild(misc_tab); 

    filenameValue = new KFileNameValueObject("save screenshots in", true, true);
    filenameValue->addReceiverCallback(this, (KSetStringPtr)&KPreferences::setScreenShotsDir);
    filenameValue->setProviderCallback(this, (KGetStringPtr)&KPreferences::getScreenShotsDir);
    filenameValue->addToWidget(misc_tab);

    KFloatValueObject * intValue = new KFloatValueObject("modulator status height");
    intValue->addReceiverCallback(this, (KSetFloatPtr)&KPreferences::setModStatusHeight);
    intValue->setProviderCallback(this, (KGetFloatPtr)&KPreferences::getModStatusHeight);
    intValue->addToWidget(misc_tab);

    misc_tab->alignLabels();

    // ............................................................... save preferences 
    KButton * savePreferencesButton = new KButton ("save");
    values_widget->addChild(savePreferencesButton);
    savePreferencesButton->addReceiverCallback(this, (KCallbackPtr)&KPreferences::save);
    addPickable(savePreferencesButton);

    // ............................................................... default project preferences 
    modulator_tab->hide();
    default_project_tab->hide();
    screenButton->setPicked(true);
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::applyVideoMode ()
{
    Controller.setFullscreenMode(KEventHandler::getFullscreen());
}

// --------------------------------------------------------------------------------------------------------
void KPreferences::save ()
{
    string xmlString;

    // save current project file as default if last_project_by_default
    if (last_project_by_default)
    {
        if (kFileIsFile(kFileAbsPathName(Controller.modules->getFileName())))
        {
            default_project = kFileAbsPathName(Controller.modules->getFileName());
        }
    }

    xmlString += kXMLValue("ProjectFile",    		KDL_XML_VALUE_STRING,	&default_project);
    xmlString += kXMLValue("LastProjectByDefault", 	KDL_XML_VALUE_BOOL,	&last_project_by_default);
    xmlString += kXMLValue("FullscreenSize", 		KDL_XML_VALUE_SIZE,	&fullscreen_size);
    xmlString += kXMLValue("WindowSize",     		KDL_XML_VALUE_SIZE,	&window_size);
    xmlString += kXMLValue("ModStatusHeight",     	KDL_XML_VALUE_INT,	&mod_status_height);
    xmlString += kXMLValue("ScreenShotsDir",     	KDL_XML_VALUE_STRING,	&screenshots_dir);
    xmlString += kXMLValue("GlobalActivationKey",	KDL_XML_VALUE_STRING,	&global_activation_key);
    xmlString += kXMLValue("MouseActivationKey",	KDL_XML_VALUE_STRING,	&mouse_activation_key);
    xmlString += kXMLValue("ValueUpKey",		KDL_XML_VALUE_STRING,	&value_up_key);
    xmlString += kXMLValue("ValueDownKey",		KDL_XML_VALUE_STRING,	&value_down_key);
    xmlString += kXMLValue("SpeedUpKey",		KDL_XML_VALUE_STRING,	&speed_up_key);
    xmlString += kXMLValue("SpeedDownKey",		KDL_XML_VALUE_STRING,	&speed_down_key);
    xmlString += kXMLValue("SpeedMultiplyKey",		KDL_XML_VALUE_STRING,	&speed_multiply_key);
    xmlString += kXMLValue("SpeedDivideKey",		KDL_XML_VALUE_STRING,	&speed_divide_key);
    xmlString += kXMLValue("SmoothStartKey",		KDL_XML_VALUE_STRING,	&smooth_start_key);
    xmlString += kXMLValue("SmoothStopKey",		KDL_XML_VALUE_STRING,	&smooth_stop_key);
    xmlString += kXMLValue("ResetKey",			KDL_XML_VALUE_STRING,	&reset_key);
    xmlString += kXMLValue("BindMouseXKey",		KDL_XML_VALUE_STRING,	&bind_mouse_x_key);
    xmlString += kXMLValue("BindMouseYKey",		KDL_XML_VALUE_STRING,	&bind_mouse_y_key);

    xmlString += Controller.main_menu->getXML();
    Controller.saveXMLInFileWithName(xmlString, config_file);
}

// --------------------------------------------------------------------------------------------------------
bool KPreferences::load ()
{
    // check for - and if exists, read - config file (path == PORTING_PROBLEM)
    if (kFileIsFile(config_file))
    {
        string xmlString;
        xmlString = Controller.getXMLFromFileWithName(config_file);
        string attributes;
        
        kXMLParseValue (xmlString, "ProjectFile",    		KDL_XML_VALUE_STRING, &default_project);
        kXMLParseValue (xmlString, "LastProjectByDefault",    	KDL_XML_VALUE_BOOL,   &last_project_by_default);
        kXMLParseValue (xmlString, "FullscreenSize", 		KDL_XML_VALUE_SIZE,   &fullscreen_size);
        kXMLParseValue (xmlString, "WindowSize",     		KDL_XML_VALUE_SIZE,   &window_size);
        kXMLParseValue (xmlString, "ModStatusHeight",     	KDL_XML_VALUE_INT,    &mod_status_height);
        kXMLParseValue (xmlString, "ScreenShotsDir",     	KDL_XML_VALUE_STRING, &screenshots_dir);
        kXMLParseValue (xmlString, "GlobalActivationKey",	KDL_XML_VALUE_STRING, &global_activation_key);
        kXMLParseValue (xmlString, "MouseActivationKey",	KDL_XML_VALUE_STRING, &mouse_activation_key);
        kXMLParseValue (xmlString, "ValueUpKey",		KDL_XML_VALUE_STRING, &value_up_key);
        kXMLParseValue (xmlString, "ValueDownKey",		KDL_XML_VALUE_STRING, &value_down_key);
        kXMLParseValue (xmlString, "SpeedUpKey",		KDL_XML_VALUE_STRING, &speed_up_key);
        kXMLParseValue (xmlString, "SpeedDownKey",		KDL_XML_VALUE_STRING, &speed_down_key);
        kXMLParseValue (xmlString, "SpeedMultiplyKey",		KDL_XML_VALUE_STRING, &speed_multiply_key);
        kXMLParseValue (xmlString, "SpeedDivideKey",		KDL_XML_VALUE_STRING, &speed_divide_key);
        kXMLParseValue (xmlString, "SmoothStartKey",		KDL_XML_VALUE_STRING, &smooth_start_key);
        kXMLParseValue (xmlString, "SmoothStopKey",		KDL_XML_VALUE_STRING, &smooth_stop_key);
        kXMLParseValue (xmlString, "ResetKey",			KDL_XML_VALUE_STRING, &reset_key);
        kXMLParseValue (xmlString, "BindMouseXKey",		KDL_XML_VALUE_STRING, &bind_mouse_x_key);
        kXMLParseValue (xmlString, "BindMouseYKey",		KDL_XML_VALUE_STRING, &bind_mouse_y_key);
        
        menu_xml = xmlString;
        
        return true;
    }
    
    return false;    
}

