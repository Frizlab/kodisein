/*
 *  KConnectorSceneOut.h
 *  kodisein
 */

#ifndef __KConnectorSceneOut
#define __KConnectorSceneOut

#include "KConnector.h"

class KConnectorSceneOut : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorSceneOut	( KModule * m, const string & n = "scene out" )	
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return false; }
    void	render			();
};

#endif
