/*
 *  KModuleInspector.h
 *  kodisein
 */

#ifndef __KModuleInspector
#define __KModuleInspector

#include "KWindow.h"

class KLabel;
class KModule;
class KIconButton;
class KWidget;

class KModuleInspector : public KWindow
{
    INTROSPECTION
    
    protected:
    
    KLabel * 			type_label;
    KWidgetArray * 		values_widget;
    
    void 			alignLabels 		();
    
    public:
            
                                KModuleInspector	();
                                
    void			setInspectedModule	( KModule * );
    void			clear			() { setInspectedModule(NULL); }
    void			maximize		();
    void			setTitle		( const string & );
    string			getTitle		() const;
    bool			isMinimized		() const;
    bool			isVisibleAndMaximized	() const;
    void			showOrMaximize		( bool );
    void			addValueWidget		( KWidget * );
    KWidgetArray *		getValuesWidget		() { return values_widget; }
};

#endif