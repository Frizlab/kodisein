/*
 *  KConnectorAttributeIn.h
 *  kodisein
 */

#ifndef __KConnectorAttributeIn
#define __KConnectorAttributeIn

#include "KConnector.h"

class KConnectorAttributeIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorAttributeIn	( KModule * m, const string & n = "attributes in" )
                                        : KConnector (m,n) {}
                        
    void	render			();
};

#endif
