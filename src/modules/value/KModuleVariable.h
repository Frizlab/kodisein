/*
 *  KModuleVariable.h
 *  kodisein
 */

#ifndef __KModuleVariable
#define __KModuleVariable

#include "KValueModule.h"

class KModuleInspector;

class KModuleVariable : public KValueModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    float	value;
    void	createConnectors	();
    
    public:
    
                KModuleVariable		( const GLfloat = 0.0 );
                                
    void	changeSex		( int ) {}
    string	getDisplayName		() const;
    float	getValue 		() const { return value; }
    void	setValue		( float );
    
    void	initInspector		( KModuleInspector * );
    void	addToWidget		( KWidgetArray *, int = 0 );
};

#endif