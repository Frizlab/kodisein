/*
 *  KConnectorModulatorOut.h
 *  kodisein
 */

#ifndef __KConnectorModulatorOut
#define __KConnectorModulatorOut

#include "KConnector.h"

class KConnectorModulatorOut : public KConnector
{
    KDS_CONNECTION_HEADER
    
    public:
                KConnectorModulatorOut 	( KModule * m, const string & n = "modulator out" )
                                        : KConnector (m,n) {}
                        
    void	render			();
};

#endif
