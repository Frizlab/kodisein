/*
 *  KConnectorValueOut.h
 *  kodisein
 */

#ifndef __KConnectorValueOut
#define __KConnectorValueOut

#include "KValueConnector.h"
#include "KTools.h"

class KConnectorValueOut : public KValueConnector
{
    OBJECT_ID
    KDS_CONNECTION_HEADER
    
    public:
                KConnectorValueOut 	( KModule * m, const string & n = "value out" )
                                        : KValueConnector (m,n) { initObjectId(); }
                        
    float	getValue		() const;
    bool	isUnlimited		() const { return true; }

    void	render 			();

    string	getIdString 		() const;
    void	setXMLAttributes	( const string & );
    string	getXMLAttributes	( bool = false ) const;
    string	getXML			( int depth = 0, bool = false ) const;
};

#endif
