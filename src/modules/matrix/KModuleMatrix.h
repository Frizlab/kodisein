/*
 *  KModuleMatrix.h
 *  kodisein
 */

#ifndef __KModuleMatrix
#define __KModuleMatrix

#include "KMatrixModule.h"

class KModuleInspector;

class KModuleMatrix : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void			createConnectors	();
    void			createValueConnectors	();
    
    public:
    
                                KModuleMatrix		( bool = true );
                                
    virtual void		initInspector		( KModuleInspector * );

    virtual void		handleMoved		( void * );
    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues 		( int = 0 ) const;
};

#endif