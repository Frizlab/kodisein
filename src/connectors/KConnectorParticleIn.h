/*
 *  KConnectorParticleIn.h
 *  kodisein
 */

#ifndef __KConnectorParticleIn
#define __KConnectorParticleIn

#include "KConnector.h"

class KConnectorParticleIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorParticleIn	( KModule * m, const string & n = "particle in")
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return true; }
    void	render			();
};

#endif
