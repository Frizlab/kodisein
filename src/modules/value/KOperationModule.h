/*
 *  KOperationModule.h
 *  kodisein
 */

#ifndef __KOperationModule
#define __KOperationModule

#include "KValueModule.h"

#define OPERATION_VALUE_IN_1 		"value in 1"
#define OPERATION_VALUE_IN_2 		"value in 2"
#define OPERATION_VALUE_IN_SWITCH 	"switch"

enum {	OPERATION_MULTIPLY, OPERATION_ADD, OPERATION_MODULO, OPERATION_SWITCH };

class KModuleInspector;
class KConnectorValueInOut;

class KOperationModule : public KValueModule
{
    INTROSPECTION
    
    protected:
    
    int			operation;
    void		resetInConnectors	();
    void		createConnectors	();
    
    public:
    
                        KOperationModule	( int );
                        ~KOperationModule	();
    
    virtual void	disconnect		();
    virtual void	disconnectConnector	( KConnector * );
    virtual void	connectInOutConnector	( KConnectorValueInOut * );
    virtual void	changeSex		( int );
    virtual float	getValue		() const;
    void 		addToWidget		( KWidgetArray *, int = 0 );
};

class KModuleAdd : public KOperationModule
{
    KDS_MODULE_HEADER
    
    public:    
                        KModuleAdd 		() : KOperationModule (OPERATION_ADD) {}
};

class KModuleMultiply : public KOperationModule
{
    KDS_MODULE_HEADER
    
    public:    
                        KModuleMultiply		() : KOperationModule (OPERATION_MULTIPLY) {}
};

class KModuleModulo : public KOperationModule
{
    KDS_MODULE_HEADER
    
    public:    
                        KModuleModulo 		() : KOperationModule (OPERATION_MODULO) {}
};

#endif
