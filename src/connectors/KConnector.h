/*
 *  KConnector.h
 *  kodisein
 */

#ifndef __KConnector
#define __KConnector

#include "KSelectable.h"
#include "KMatrix.h"

enum {	KDS_ANY_CONNECTOR, KDS_FREE_CONNECTOR, KDS_USED_CONNECTOR };

enum {	KDS_CONNECTOR_FLAT, 
        KDS_CONNECTOR_MATRIX_OUT, KDS_CONNECTOR_MATRIX_IN,
        KDS_CONNECTOR_MODULATOR_OUT, KDS_CONNECTOR_MODULATOR_IN,
        KDS_CONNECTOR_VALUE_OUT, KDS_CONNECTOR_VALUE_IN, 
        KDS_CONNECTOR_PARTICLE_OUT, KDS_CONNECTOR_PARTICLE_IN, 
        KDS_CONNECTOR_ATTRIBUTE_OUT, KDS_CONNECTOR_ATTRIBUTE_IN,
        KDS_CONNECTOR_TEXTURE_BATCH_IN, KDS_CONNECTOR_TEXTURE_BATCH_OUT,
        KDS_CONNECTOR_TEXTURE_FILE_IN, KDS_CONNECTOR_TEXTURE_FILE_OUT,
        KDS_CONNECTOR_TEXTURE_VERSION_IN, KDS_CONNECTOR_TEXTURE_VERSION_OUT,
        KDS_CONNECTOR_SCENE_IN, KDS_CONNECTOR_SCENE_OUT };
        
#define KDS_CONNECTOR_LINE_WIDTH	2.0f
#define KDS_CONNECTOR_MIN_DISTANCE	0.1f

#define KDS_CONNECTION_HEADER \
    INTROSPECTION \
    static   	const int type; \
    static 	const int connection_type; \
    public: \
    virtual  int getType() const { return type; } \
    virtual  int getConnectionType() const { return connection_type; } \
    private:

#define KDS_CONNECTION_VALUES(className, cType, cConnectionType) \
    KDL_CLASS_INTROSPECTION_1(className, KConnector) \
    const int className::type = cType; \
    const int className::connection_type = cConnectionType;

class KModule;

class KConnector : public KMatrix, public KSelectable
{
    KDS_CONNECTION_HEADER

    protected:

    vector<KConnector*>	connected_connectors;
    
    string		name;
    KModule *		module;
    
    public:
                        KConnector		( KModule *, const string & name = "connector");
                            
    vector<KModule*>	getConnectedModules	() const;
    KModule *		getConnectedModule	() const;
    KConnector *	getConnectedConnector	() const;
    vector<KConnector*>	getConnectedConnectors	() const { return connected_connectors; }
    KConnector *      	getConnectedChildConnector() const;

    KModule *		getModule		() const { return module; }

    void		setName			( const string & n ) { name = n; }
    const string &	getName 		() const { return name; }

    void		setPicked		( bool );

    void		addConnectedConnector	( KConnector * );
    void		removeConnectedConnector( KConnector * );
    bool		isConnected		() const {return !connected_connectors.empty();}
    bool		isUnconnected		() const {return connected_connectors.empty();}
    bool		isChildConnector	() const { return !isParentConnector(); }

    virtual void	disconnect		();
    virtual void	display			();
    virtual void	render			();
    
    virtual string	getDisplayName		() const;
    virtual void	connectWithConnector	( KConnector * );
    virtual bool	isUnlimited		() const { return false; }
    virtual bool	isAcceptingConnections	() const;
    virtual bool	isParentConnector	() const { return false; }
    virtual bool	isCutCopyPasteable	() const { return false; }
    		
    virtual void	setXML			( string & );
    virtual void	setXMLAttributes	( const string & ) {}
    virtual string	getXML			( int depth = 0, bool = false ) const;
    virtual string	getXMLAttributes	( bool = false ) const;
};

#endif