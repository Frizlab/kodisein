/*
 *  KModuleRandom.h
 *  kodisein
 */

#ifndef __KModuleRandom
#define __KModuleRandom

#include "KValueModule.h"

class KModuleRandom : public KValueModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    float	last_value;
    float	new_random;
    float	old_random;
    
    void	createConnectors	();
    
    public:
    
                KModuleRandom		();
                ~KModuleRandom		();
                        
    float	getValue 		() const;
    void	randomize		( float );
    
    bool	shouldPropagate		( int = 0 );
    
    void	displayConnectors	( int );
    
    void	addToWidget		( KWidgetArray *, int = 0 );
};

#endif