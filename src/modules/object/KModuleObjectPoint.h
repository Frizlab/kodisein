/*
 *  KModuleObjectPoint.h
 *  kodisein
 */

#ifndef __KModuleObjectPoint
#define __KModuleObjectPoint

#include "KObjectModule.h"

class KModuleObjectPoint : public KObjectModule
{
    KDS_MODULE_HEADER
    
    public:
                                KModuleObjectPoint 	();
    
    virtual void		display			( int );
    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int depth = 0 ) const;
};

#endif

