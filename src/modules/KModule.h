/*
 *  KModule.h
 *  kodisein
 */

#pragma warning(disable:4786)

#ifndef __KModule
#define __KModule

#include "KSelectable.h"
#include "KColor.h"
#include "KModuleInspector.h"
    
using namespace std;

class KConnector;
class KValueObject;
class KAttributeModule;

#define KDS_MODULE_HEADER \
    INTROSPECTION \
    static   	const string class_name; \
    static 	KColor module_color; \
    public: \
    static   const string & name()          { return class_name; } \
    virtual  const string & getName() const { return class_name; } \
    virtual  const KColor & getModuleColor () const { return module_color; } \
    private:

#define KDS_MODULE_VALUES(className,name,r,g,b,a) \
    const string className::class_name(name); \
    KColor className::module_color(r,g,b,a);

class KModule : public KMatrix, public KSelectable
{
    KDS_MODULE_HEADER
    
    protected:
    
    int					min_id;
    int					max_id;

    string 				description;
        
    vector<KValueObject*>		values;
    PickableVector 			connectors;

    unsigned int			display_list;
    
    void				deleteDisplayList();
    
    public:
                                        KModule 		();

    virtual	       			~KModule		();
    
    virtual void			updateMatrix 		();
    virtual void			updateChildren 		();
    
    virtual void			addConnector		( KConnector * connector );
        
    virtual void			pushAttributes		( int mode );
    virtual void			displayConnectors	( int mode );
    virtual void			preDisplay		( int mode );
    virtual void			display 		( int mode );
    virtual void			postDisplay		( int mode );
    virtual void			popAttributes		( int mode );
    virtual void			displayChildModules	( int mode );
        
    virtual void			rotate			( const GLfloat x, 
                                                                  const GLfloat y, 
                                                                  const GLfloat z );
    virtual void			setPosition		( const KVector & );

    virtual void 			setPicked 		( bool );
    virtual void 			setSelected 		( bool );
    
    KConnector *			getPickedConnector	() const;
    KConnector *			getConnectorWithName	( const string & ) const;
    KConnector *			getConnectorForModule	( KModule * ) const;
    KConnector *			getConnectorOfType	( int, int = 0 ) const;
    virtual KConnector * 		getParentConnector	() const;
    vector<KConnector*>			getConnectorsOfType	( int, int = 0 ) const;
    bool				hasConnectorOfType	( int, int = 0 ) const;
    
    virtual bool			connectModule		( KModule *, KConnector * = NULL,
                                                                             KConnector * = NULL );
    virtual void			disconnect		();
    virtual void			disconnectConnector	( KConnector * );    
    virtual bool			isAcceptingConnection	( KConnector * ) const;
    virtual KConnector *		getAcceptingConnector	( KConnector * ) const;

    virtual bool			hasSubPickables		() const { return true; }
    virtual const PickableVector *	getSubPickables		() const { return &connectors; }
    virtual void			setMinId		( int i ) { min_id = i; }
    virtual void			setMaxId		( int i ) { max_id = i; }
    virtual int				getMinId		() { return min_id; }
    virtual int				getMaxId		() { return max_id; }
    
    virtual string			getDisplayName		() const { return "[" + getName() + "]"; }

    virtual void			getModulesInHierarchy 	( vector<KModule*> &, bool = false, 
                                                        const KClassId & = KModule::classId() ) const;
    virtual void			getLeafModules 		( vector<KModule*> & ) const;
    virtual vector<KModule*>		getParentModules	() const;
    virtual vector<KModule*>		getChildModules		() const;
    virtual vector<KModule*>		getChildModulesOfType	( int ) const;
    virtual KModule *			getParentModule		() const;
    virtual KModule *			getRootModule		() const;    
    virtual bool			isRootModule		() const 
                                                                { return (getParentModule() == NULL); }
    virtual void			initInspector 		( KModuleInspector * );
    
    virtual bool			isCutCopyPasteable	() const;
    virtual string			getPasteBufferString	() const;
    
    virtual void			setDescription		( const string & s ) { description = s; }
    virtual string			getDescription		() const { return description; }

    virtual void			setXML			( string & );
    virtual string			getXML			( int = 0, bool = false ) const;
    virtual void			setXMLValues		( string & );
    virtual string			getXMLValues		( int = 0 ) const;
    virtual void			setXMLAttributes	( const string & );
    virtual string			getXMLAttributes	() const;
};

#endif

