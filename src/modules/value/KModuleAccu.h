/*
 *  KModuleAccu.h
 *  kodisein
 */

#ifndef __KModuleAccu
#define __KModuleAccu

#include "KValueModule.h"

class KModuleInspector;

#define RESET_IN "reset in"

class KModuleAccu : public KValueModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    float		accu_value;
    float		old_value;
    float		old_reset;
    bool		increment;
    
    void		createConnectors	();
    
    public:
    
                        KModuleAccu		();
                        
    virtual float	getValue 		() const;
    virtual void	reset			();

    virtual void	setIncrement		( bool b ) { increment = b; }
    virtual bool	getIncrement		() const { return increment; }
    
    virtual void	displayConnectors	( int );
    
    virtual void	addToWidget		( KWidgetArray *, int = 0 );
};

#endif