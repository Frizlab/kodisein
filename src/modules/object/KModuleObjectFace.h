/*
 *  KModuleObjectFace.h
 *  kodisein
 */

#ifndef __KModuleObjectFace
#define __KModuleObjectFace

#include "KObjectModule.h"

class KFace;

class KModuleObjectFace : public KObjectModule
{
    KDS_MODULE_HEADER
    
    public:
                                KModuleObjectFace ();

    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int depth = 0 ) const;
};

#endif

