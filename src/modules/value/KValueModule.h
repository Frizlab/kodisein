/*
 *  KValueModule.h
 *  kodisein
 */

#ifndef __KValueModule
#define __KValueModule

#include "KModule.h"

class KModuleInspector;
class KConnectorValueOut;
class KConnectorValueInOut;

#define VALUE_OUT 		"value out"
#define VALUE_IN 		"value in"
#define VALUE_UNKNOWN_STRING 	"#"
#define VALUE_MAX_DEPTH		5

enum {	VALUEMODULE_SEX_NEUTRUM, VALUEMODULE_SEX_FEMALE, VALUEMODULE_SEX_MALE };

class KValueModule : public KModule
{
    INTROSPECTION
        
    public:
    
                                KValueModule		();
                                
    virtual float		getValue		() const = 0;
    
    virtual bool		connectModule		( KModule *, KConnector * = NULL, 
                                                                     KConnector * = NULL );
    
    virtual int			getSex			() const;
    virtual void		changeSex		( int );
    KConnectorValueOut *	getTargetOutConnector	() const;
    
    virtual void		addToWidget		( KWidgetArray *, int = 0 ) {};
    virtual void		initInspector 		( KModuleInspector * );
    
    virtual bool 		shouldPropagate		( int = 0 );
    virtual void 		propagateValue 		( int = 0 );

            void 		getLeafConnectors	( vector<KConnectorValueInOut*> & );
};

#endif
