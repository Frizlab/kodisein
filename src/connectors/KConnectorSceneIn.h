/*
 *  KConnectorSceneIn.h
 *  kodisein
 */

#ifndef __KConnectorSceneIn
#define __KConnectorSceneIn

#include "KConnector.h"

class KConnectorSceneIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorSceneIn 	( KModule * m, const string & n = "scene in" )
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return true; }
    void	render			();
};

#endif
