/*
 *  KConnectorTextureBatchOut.h
 *  kodisein
 */

#ifndef __KConnectorTextureBatchOut
#define __KConnectorTextureBatchOut

#include "KConnector.h"

class KConnectorTextureBatchOut : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorTextureBatchOut ( KModule * m, const string & n = "texture batch out" )
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return false; }
    void	render			();
};

#endif
