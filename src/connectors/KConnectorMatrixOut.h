/*
 *  KConnectorMatrixOut.h
 *  kodisein
 */

#ifndef __KConnectorMatrixOut
#define __KConnectorMatrixOut

#include "KConnector.h"

class KConnectorMatrixOut : public KConnector
{
    KDS_CONNECTION_HEADER
    
    public:
                KConnectorMatrixOut 	( KModule * m, const string & n = "matrix out" )
                                        : KConnector (m,n) {}
    
    void	render 			();
};

#endif
