/*
 *  KHubModule.h
 *  kodisein
 */

#ifndef __KHubModule
#define __KHubModule

#include "KMatrixModule.h"

class KHubModule : public KMatrixModule
{
    INTROSPECTION

    public:
    
                                KHubModule		();

    virtual const KMatrix &	getMatrix		() const;
    virtual KMatrix		getWorldMatrix		() const;
                                
    virtual void		display			( int );
    virtual void		initInspector		( KModuleInspector * );
    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues 		( int = 0 ) const;
};

#endif