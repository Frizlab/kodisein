/*
 *  KModuleTrigger.h
 *  kodisein
 */

#ifndef __KModuleTrigger
#define __KModuleTrigger

#include "KActivationValueModule.h"

class KModuleInspector;

class KModuleTrigger : public KActivationValueModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    int		last_time;
    void	createConnectors	();
    
    public:
    
                KModuleTrigger		();
                ~KModuleTrigger		();
                        
    float	getValue 		() const;
    bool	shouldPropagate		( int = 0 ) { return activated || last_time; }
    
    void	activate		();
        
    string	getDisplayName		() const;
    void	displayConnectors	( int );
    
    void	initInspector 		( KModuleInspector * );
    void	addToWidget		( KWidgetArray *, int = 0 );
};

#endif