/*
 *  KGlobalModulator.h
 *  kodisein
 */

#ifndef __KGlobalModulator
#define __KGlobalModulator

#include "KModulator.h"

class KModuleInspector;

class KGlobalModulator : public KModulator
{
    KDS_MODULE_HEADER

    protected:
    
    bool		mouse_modulation;
    bool		clear_frame;
    vector<KModulator*>	modulators;
    
    float		mouse_x, mouse_y;
    
    void		createConnectors	();
        
    public:
    
                        KGlobalModulator	();

    void		activate		();
    void		deactivate		();

    void		addModulator		( KModulator * );
    void		removeModulator		( KModulator * );
    void		updateModulatorValues	();
    void		stopModulation		();
    void		resetModulation		();
    KModulator *	getSelectedModulator	();

    void		displayConnectors	( int );
    void		displayStatus		( bool );

    void		initScene		();
    bool		isCutCopyPasteable	() const { return false; }

    void		setMouseValues		( float x, float y ); // mouse modulation
    void		setMouseModulation	( bool b ) { mouse_modulation = b; }
    bool		getMouseModulation	() const { return mouse_modulation; }
    float		getMouseX		() { return mouse_x; }
    float		getMouseY		() { return mouse_y; }

    void		setClearFrame		( bool b ) { clear_frame = b; }
    bool		getClearFrame		() const { return clear_frame; }

    string		getDocumentation	();
    int			getSex			() const { return VALUEMODULE_SEX_FEMALE; }
    string		getXML 			( int = 0 ) const;
    void		initInspector 		( KModuleInspector * );
};

#endif
