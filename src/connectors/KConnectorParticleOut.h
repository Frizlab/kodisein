/*
 *  KConnectorParticleOut.h
 *  kodisein
 */

#ifndef __KConnectorParticleOut
#define __KConnectorParticleOut

#include "KConnector.h"

class KConnectorParticleOut : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorParticleOut 	( KModule * m, const string & n = "particle out")
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return false; }
    void	render			();
};

#endif
