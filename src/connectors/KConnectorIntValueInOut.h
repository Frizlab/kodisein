/*
 *  KConnectorDiscreteValueInOut.h
 *  kodisein
 */

#ifndef __KConnectorIntValueInOut
#define __KConnectorIntValueInOut

#include "KConnectorValueInOut.h"

#include <string>
#include <algorithm>

using namespace std;

class KConnectorIntValueInOut : public KConnectorValueInOut
{
    INTROSPECTION
    
    protected:
    
    vector<int>			values;
    vector<string>		names;
    
    public:
                                KConnectorIntValueInOut ( KModule * m,
                                                            const vector<string> & nv,
                                                            const vector<int> & vv,
                                                            const string & n = "discrete value in") 
                                                            : KConnectorValueInOut (m,n)
                                                            { names = nv; values = vv; }

    void			providerSet		();
    void			setValue		( float );
    
    void			setTypedReceiverValue	( int v );
    int				getRangeSize		() const { return values.size(); }
    int 			getValueAtIndex		( int ) const;
    int				getIndexForValue	( int ) const;
    int 			getValueForName		( const string & ) const;
    const string &		getNameForValue		( int ) const;
    void			buttonCallback		( const string & );

    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int = 0 ) const;
    virtual void		addToWidget		( KWidgetArray * );
};

// --------------------------------------------------------------------------------------------------------

#endif
