/*
 *  KConnectorMatrixIn.h
 *  kodisein
 */

#ifndef __KConnectorMatrixIn
#define __KConnectorMatrixIn

#include "KConnector.h"

class KConnectorMatrixIn : public KConnector
{
    KDS_CONNECTION_HEADER

    public:
                KConnectorMatrixIn 	( KModule * m, const string & n = "matrix in" )
                                        : KConnector (m,n) {}
                        
    bool	isParentConnector	() const { return true; }
    void	render 			();
};

#endif
