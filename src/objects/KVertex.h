/*
 *  KVertex.h
 *  kodisein
 */

#ifndef __KVertex
#define __KVertex

#pragma warning(disable:4786)

#include "KMatrixHandle.h"

class KModuleInspector;

class KVertex : public KMatrixHandle
{
    INTROSPECTION
    
    public:
                                KVertex 		();
                                KVertex			( KMatrixModule * );

    virtual void		display			( int mode );

    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int depth = 0 ) const;

    virtual void		initInspector 		( KModuleInspector * );
};

#endif