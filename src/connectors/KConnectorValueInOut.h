/*
 *  KConnectorValueInOut.h
 *  kodisein
 */

#ifndef __KConnectorValueInOut
#define __KConnectorValueInOut

#include "KConnectorValueIn.h"
#include "KFloatValueObject.h"

class KWidgetArray;
class KModuleInspector;

#define KDS_CONNECTOR_OFFSET(index, numSisters) (1.0f - (index)*2.0f/(numSisters+1.0f))

#define NEW_IO_CONNECTOR_TR(vname,tx,ty,tz,rx,ry,rz,objectName,className,setCallbackName,getCallbackName) \
    ioConnector = new KConnectorValueInOut( this, vname ); \
    ioConnector->translate (tx, ty, tz); \
    ioConnector->rotate (rx, ry, rz); \
    addConnector(ioConnector); \
    values.push_back((KFloatValueObject*)ioConnector); \
    ((KFloatValueObject*)values.back())->setProviderCallback(objectName, (KGetFloatPtr) & className::getCallbackName ); \
    ((KFloatValueObject*)values.back())->addReceiverCallback(objectName, (KSetFloatPtr) & className::setCallbackName );
    
#define NEW_IO_CONNECTOR_Y(vname,dirx,y,dirz,index,numSisters,objectName,className,setCallbackName,getCallbackName) \
    NEW_IO_CONNECTOR_TR(vname,  dirx * (1.0f + KDS_VALUECONNECTOR_RADIUS) + \
                                - (dirz) * KDS_CONNECTOR_OFFSET(index, numSisters), \
                                y, \
                                dirz * (1.0f + KDS_VALUECONNECTOR_RADIUS) + \
                                dirx * KDS_CONNECTOR_OFFSET(index, numSisters), \
                               (dirz * 90.0f), (-90.0f * dirz) + ((dirx == -1) ? 180.0f : 0.0), -90.0f * kAbs(dirx), \
                               objectName, className, setCallbackName, getCallbackName )

#define NEW_IO_CONNECTOR(vname,dirx,dirz,index,numSisters,objectName,className,setCallbackName,getCallbackName) \
    NEW_IO_CONNECTOR_Y(vname,dirx,0,dirz,index,numSisters,objectName,className,setCallbackName,getCallbackName)

class KConnectorValueInOut : public KConnectorValueIn, public KFloatValueObject
{
    INTROSPECTION
    
    public:
                        KConnectorValueInOut 	( KModule * m, const string & n = "value in") 
                                                : KConnectorValueIn(m,n), KFloatValueObject(n) {}
                        
    virtual float	getValue 		() const  { return value; }
    virtual void	setValue		( float );
    virtual void	setReceiverValue	( float );
    
    virtual void	providerSet		();

    virtual void	connectWithConnector	( KConnector * );

    virtual int		getRangeSize		() const { return 0; }
    virtual void	addToWidget		( KWidgetArray * );
    
    void		textFieldPicked		( bool b );
};

#endif
