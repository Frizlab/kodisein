/*
 *  KConnectorAttributeOut.h
 *  kodisein
 */

#ifndef __KConnectorAttributeOut
#define __KConnectorAttributeOut

#include "KConnector.h"

class KConnectorAttributeOut : public KConnector
{
    KDS_CONNECTION_HEADER
    
    public:
                KConnectorAttributeOut ( KModule * m, const string & n )
                                        : KConnector (m,n) {}
    
    bool	isParentConnector	() const { return true; }
    void	render 			();
};

#endif
