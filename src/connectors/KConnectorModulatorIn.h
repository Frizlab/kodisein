/*
 *  KConnectorModulatorIn.h
 *  kodisein
 */

#ifndef __KConnectorModulatorIn
#define __KConnectorModulatorIn

#include "KConnector.h"

class KConnectorModulatorIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorModulatorIn 	( KModule * m, const string & n = "modulator in" )
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return true; }
    void	render			();
};

#endif
