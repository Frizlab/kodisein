/*
 *  KConnectorTextureFileIn.h
 *  kodisein
 */

#ifndef __KConnectorTextureFileIn
#define __KConnectorTextureFileIn

#include "KConnector.h"

class KConnectorTextureFileIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorTextureFileIn ( KModule * m, const string & n = "texture file in")
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return true; }
    void	render			();
};

#endif
