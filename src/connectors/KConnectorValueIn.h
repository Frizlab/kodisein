/*
 *  KConnectorValueIn.h
 *  kodisein
 */

#ifndef __KConnectorValueIn
#define __KConnectorValueIn

#include "KValueConnector.h"

class KConnectorValueIn : public KValueConnector
{
    KDS_CONNECTION_HEADER
    
    public:
    
    unsigned int 	time;
    float		value;
    
                        KConnectorValueIn 	( KModule * m, const string & n = "value in");
                        
    virtual void 	connectWithConnector 	( KConnector * );
    virtual void	setValue 		( float );
    virtual float	getValue 		() const  { return value; }
    virtual void	render 			();
};

#endif
