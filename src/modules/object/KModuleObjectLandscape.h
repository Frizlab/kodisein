/*
 *  KModuleObjectLandscape.h
 *  kodisein
 */

#ifndef __KModuleObjectLandscape
#define __KModuleObjectLandscape

#include "KObjectModule.h"

class KModuleObjectLandscape : public KObjectModule
{
    KDS_MODULE_HEADER

    protected:
    
    void 	createConnectors	();

    public:
                KModuleObjectLandscape ();

    void	setXMLValues		( string & );
    string	getXMLValues		( int depth = 0 ) const;
};

#endif

