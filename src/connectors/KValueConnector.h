/*
 *  KValueConnector.h
 *  kodisein
 */

#ifndef __KValueConnector
#define __KValueConnector

#include "KConnector.h"

#define KDS_VALUECONNECTOR_RADIUS 	0.2f

class KValueConnector : public KConnector
{
    INTROSPECTION

    protected:
    
    bool		parent_connector;
    
    public:
    
                        KValueConnector		( KModule * m, const string & n )
                                                : KConnector (m,n) { parent_connector = false; }

    void		makeParentConnector	( bool b ) { parent_connector = b; }
    bool		isParentConnector	() const { return parent_connector; }
    
    virtual void	display			();
    virtual float	getValue 		() const { return 0.0; };
};

#endif