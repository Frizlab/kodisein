/*
 *  KConnectorTextureBatchIn.h
 *  kodisein
 */

#ifndef __KConnectorTextureBatchIn
#define __KConnectorTextureBatchIn

#include "KConnector.h"

class KConnectorTextureBatchIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorTextureBatchIn ( KModule * m, const string & n = "texture batch in" )
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return true; }
    void	render			();
};

#endif
