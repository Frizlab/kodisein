/*
 *  KConnectorTextureVersionOut.h
 *  kodisein
 */

#ifndef __KConnectorTextureVersionOut
#define __KConnectorTextureVersionOut

#include "KConnector.h"

class KConnectorTextureVersionOut : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorTextureVersionOut ( KModule * m, const string & n = "texture version out")
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return false; }
    void	render			();
};

#endif
