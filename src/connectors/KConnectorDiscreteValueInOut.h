/*
 *  KConnectorDiscreteValueInOut.h
 *  kodisein
 */
#pragma warning(disable:4786)

#ifndef __KConnectorDiscreteValueInOut
#define __KConnectorDiscreteValueInOut

#include "KConnectorValueInOut.h"
#include "KValueModule.h"
#include "KModulator.h"
#include "KModules.h"
#include "KConsole.h"
#include "KButtonBox.h"
#include "KButton.h"
#include "KLabel.h"
#include "KXMLTools.h"

#include <string>
#include <algorithm>

using namespace std;

template <class T>
class KConnectorDiscreteValueInOut : public KConnectorValueInOut
{
    //INTROSPECTION
    
    protected:
    
    vector<T>			values;
    vector<string>		names;
    
    public:
                                KConnectorDiscreteValueInOut ( KModule * m,
                                                            const vector<string> & nv,
                                                            const vector<T> & vv,
                                                            const string & n = "discrete value in") 
                                                            : KConnectorValueInOut (m,n)
                                                            { names = nv; values = vv; }

    void			providerSet		();
    void			setValue		( float );
    
    void			setTypedReceiverValue	( const T v );
    int				getRangeSize		() const { return values.size(); }
    const T &			getValueAtIndex		( int ) const;
    int				getIndexForValue	( const T & ) const;
    const T &			getValueForName		( const string & ) const;
    const string &		getNameForValue		( const T & ) const;
    void			buttonCallback		( const string & );

    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int = 0 ) const;
    virtual void		addToWidget		( KWidgetArray * );
};

// --------------------------------------------------------------------------------------------------------

//TEMPLATE_INTROSPECTION1(T, KConnectorDiscreteValueInOut, KConnectorValueInOut)
//INTROSPECTION_BASE_LIST1(KConnectorDiscreteValueInOut, KConnectorValueInOut)
//TEMPLATE_INFO_DEFINITION(T,KConnectorDiscreteValueInOut)
//template <class T> const KClassInfo KConnectorDiscreteValueInOut<T>::class_info("KConnectorDiscreteValueInOut", { 0 });

// --------------------------------------------------------------------------------------------------------
/*
template <class T>
void KConnectorDiscreteValueInOut<T>::applyModulation ()
{
    notifyReceivers(getValueAtIndex(((KValueConnector*)connected_connectors[0])->getValue()));
}
*/

// --------------------------------------------------------------------------------------------------------
template <class T>
void KConnectorDiscreteValueInOut<T>::setValue ( float v )
{
    notifyReceivers(getValueAtIndex(v)); // notify receivers without changing internal value
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KConnectorDiscreteValueInOut<T>::providerSet ()
{
    // this message is send, if a provider was. get and store the value from the provider.
    T v;
    receiveValue(&v);
    value = (float)getIndexForValue(v);
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KConnectorDiscreteValueInOut<T>::setTypedReceiverValue ( const T v )
{
    value = (float)getIndexForValue(v);
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
template <class T>
const string & KConnectorDiscreteValueInOut<T>::getNameForValue ( const T & typedValue ) const
{
    vector<T>::const_iterator result = find (values.begin(), values.end(), typedValue);
    if (result != values.end())
    {
        return names[result-values.begin()];
    }

    KConsole::printError(kStringPrintf("getNameForValue failed for module\n'%s'",
                                                                            module->getName().c_str()));
    return names[0];
}

// --------------------------------------------------------------------------------------------------------
template <class T>
const T & KConnectorDiscreteValueInOut<T>::getValueForName ( const string & valueName ) const
{
    vector<string>::const_iterator result = find (names.begin(), names.end(), valueName);
    if (result != names.end())
    {
        return values[(result - names.begin())];
    }

    KConsole::printError(kStringPrintf("getValueForName failed for module\n'%s'\nand name '%s'", 
                                                            module->getName().c_str(), valueName.c_str()));
    return values[0];
}

// --------------------------------------------------------------------------------------------------------
template <class T>
const T & KConnectorDiscreteValueInOut<T>::getValueAtIndex ( int index ) const
{
    return values[index % values.size()];
}
                                                                            
// --------------------------------------------------------------------------------------------------------
template <class T>
int KConnectorDiscreteValueInOut<T>::getIndexForValue ( const T & v ) const
{
    vector<T>::const_iterator result = find(values.begin(), values.end(), v);
    return (result-values.begin());
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KConnectorDiscreteValueInOut<T>::buttonCallback ( const string & buttonText )
{
    setTypedReceiverValue(getValueForName(buttonText));
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KConnectorDiscreteValueInOut<T>::setXMLValues ( string & xml )
{    
    string valueName;
    if (kXMLParseValue(xml, getName(), KDL_XML_VALUE_STRING, &valueName)) 
    {
        setTypedReceiverValue(getValueForName(valueName));
    }
}

// --------------------------------------------------------------------------------------------------------
template <class T>
string KConnectorDiscreteValueInOut<T>::getXMLValues ( int depth ) const
{     
    string valueName = getNameForValue((T)getValueAtIndex((int)value));
    return kXMLValue(getName(), KDL_XML_VALUE_STRING, &valueName, depth);
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KConnectorDiscreteValueInOut<T>::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    widgetArray->addChild(valueWidget);

    KLabel * label = new KLabel(getName());
    valueWidget->addChild(label);
        
    KButtonBox * buttonBox = new KButtonBox ();
    buttonBox->setFrameSpacing(0);
    valueWidget->addChild(buttonBox);
    
    string valueName = getNameForValue((T)getValueAtIndex(value));
    
    for (int index = 0; index < (int)names.size(); index++)
    {
        KButton * button = new KButton(names[index]);
		if (valueName == names[index]) button->activate();
        button->addReceiverCallback(((KFloatValueObject*)this),
(KSetStringPtr)(void (KFloatValueObject::*)(const string &))&KConnectorDiscreteValueInOut<T>::buttonCallback);
        buttonBox->addButton(button);
        widgetArray->getWindow()->addPickable(buttonBox);

        if (isSelected() || isPicked())
        {
            button->setBGColor(KColor(0.0, 0.0, 1.0, 0.25));
        }
    }

    if (isConnected())
    {
        ((KValueModule*)getConnectedModule())->addToWidget(valueWidget);
    }

    if (isSelected() || isPicked())
    {
        label->setFGColor(KColor(0.5, 0.5, 1.0, 1.0));
    }
}

#endif
