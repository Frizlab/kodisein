/*
 *  KConnectorTextureFileOut.h
 *  kodisein
 */

#ifndef __KConnectorTextureFileOut
#define __KConnectorTextureFileOut

#include "KConnector.h"

class KConnectorTextureFileOut : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorTextureFileOut ( KModule * m, const string & n = "texture file out")
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return false; }
    bool	isAcceptingConnections	() const;
    void	render			();
};

#endif
