/*
 *  KPreferences.h
 *  kodisein
 */

#include "KWindow.h"
#include "KController.h"

class KPreferences : public KWindow
{
    INTROSPECTION
    
    friend class KController;
    
    protected:
    
    KWidgetArray *	screen_tab;
    KWidgetArray *	modulator_tab;
    KWidgetArray *	default_project_tab;
    KWidgetArray *	misc_tab;
    
    KWidgetArray * 	values_widget;
    string		menu_xml;
    string		config_file;	// config file for menu shortcuts and last project file
    KSize		window_size;	// video modes
    KSize		fullscreen_size;
    
    int			mod_status_height;

    string		default_project;
    string		screenshots_dir;
    bool		last_project_by_default;
    
    string		global_activation_key;
    string		mouse_activation_key;
    string		value_up_key;
    string		value_down_key;
    string		speed_up_key;
    string		speed_down_key;
    string		speed_multiply_key;
    string		speed_divide_key;
    string		start_stop_key;
    string		smooth_stop_key;
    string		smooth_start_key;
    string		reset_key;
    string		bind_mouse_x_key;
    string		bind_mouse_y_key;
        
    void		createPreferenceTabs ();
    
    public:
    
                        KPreferences ();
                        
    bool		load	();
    void		save	();
    void		show	();
    void		hide	();
    
    void		tabButtonCallback	( const string & );
    
    void		applyVideoMode		();
        
    // acessor methods
    void 		setWindowSize		( const KSize & s ) { window_size = s; }
    KSize		getWindowSize		() const { return window_size; }

    void 		setFullscreenSize	( const KSize & s ) { fullscreen_size = s; }
    KSize		getFullscreenSize	() const { return fullscreen_size; }

    void		setScreenShotsDir	( const string & s ) { screenshots_dir = s; }
    string	 	getScreenShotsDir	() const { return screenshots_dir; }

    void		setDefaultProjectFile	( const string & s ) { default_project = s; }
    string	 	getDefaultProjectFile	() const { return default_project; }

    void		setLastProjectByDefault	( bool b ) { last_project_by_default = b; }
    bool		getLastProjectByDefault	() const { return last_project_by_default; }

    void 		setGlobalActivationKey	( const string & s );
    string		getGlobalActivationKey	() const { return global_activation_key; }

    void 		setMouseActivationKey	( const string & s ) { mouse_activation_key = s; }
    string		getMouseActivationKey	() const { return mouse_activation_key; }
    
    void		setSpeedUpKey		( const string & s ) { speed_up_key = s; }
    string 		getSpeedUpKey		() const { return speed_up_key; }

    void		setSpeedDownKey		( const string & s ) { speed_down_key = s; }
    string 		getSpeedDownKey		() const { return speed_down_key; }

    void		setStartStopKey		( const string & s ) { start_stop_key = s; }
    string 		getStartStopKey		() const { return start_stop_key; }

    void		setResetKey		( const string & s ) { reset_key = s; }
    string 		getResetKey		() const { return reset_key; }

    void		setValueUpKey		( const string & s ) { value_up_key = s; }
    string 		getValueUpKey		() const { return value_up_key; }

    void		setValueDownKey		( const string & s ) { value_down_key = s; }
    string 		getValueDownKey		() const { return value_down_key; }

    void		setSmoothStartKey	( const string & s ) { smooth_start_key = s; }
    string 		getSmoothStartKey	() const { return smooth_start_key; }

    void		setSmoothStopKey	( const string & s ) { smooth_stop_key = s; }
    string 		getSmoothStopKey	() const { return smooth_stop_key; }

    void		setSpeedMultiplyKey	( const string & s ) { speed_multiply_key = s; }
    string 		getSpeedMultiplyKey	() const { return speed_multiply_key; }

    void		setSpeedDivideKey	( const string & s ) { speed_divide_key = s; }
    string 		getSpeedDivideKey	() const { return speed_divide_key; }

    void		setBindMouseXKey	( const string & s ) { bind_mouse_x_key = s; }
    string 		getBindMouseXKey	() const { return bind_mouse_x_key; }

    void		setBindMouseYKey	( const string & s ) { bind_mouse_y_key = s; }
    string 		getBindMouseYKey	() const { return bind_mouse_y_key; }

    void		setModStatusHeight	( float f ) { mod_status_height = kMax(0,kMin((int)f,10)); }
    float 		getModStatusHeight	() const { return (float)mod_status_height; }
};

