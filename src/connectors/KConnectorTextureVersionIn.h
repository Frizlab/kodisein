/*
 *  KCennectorTextureVersionIn.h
 *  kodisein
 */

#ifndef __KCennectorTextureVersionIn
#define __KCennectorTextureVersionIn

#include "KConnector.h"

class KConnectorTextureVersionIn : public KConnector
{
    KDS_CONNECTION_HEADER
    
    public:
                KConnectorTextureVersionIn ( KModule * m, const string & n = "texture version in" )
                                        : KConnector (m,n) {}

    bool	isParentConnector	() const { return true; }
    void	render			();
};    

#endif

