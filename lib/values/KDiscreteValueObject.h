/*
 *  KDiscreteValueObject.h
 *  kodisein
 */

#ifndef __KDiscreteValueObject
#define __KDiscreteValueObject

#include "KValueObject.h"
#include "KConsole.h"
#include "KButtonBox.h"
#include "KButton.h"
#include "KLabel.h"

#include <algorithm>

template <class T>
class KDiscreteValueObject : public KValueObject
{
    INTROSPECTION
    
    protected:
    
    vector<T>			values;
    vector<string>		names;
    
    public:
                                KDiscreteValueObject ( const vector<string> & nv, const vector<T> & vv,
                                                       const string & n = "discrete value") 
                                                       : KValueObject (n) { names = nv; values = vv;}
                        
    void			setValue		( T v );
    T	 			getValue		() const;
    const T &			getValueAtIndex		( int ) const;
    const T &			getValueForName		( const string & ) const;
    const string &		getNameForValue		( const T & ) const;
    void			buttonCallback		( const string & );
    
    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int = 0 ) const;
    virtual void		addToWidget		( KWidgetArray * );
};

// --------------------------------------------------------------------------------------------------------

TEMPLATE_INTROSPECTION1(T, KDiscreteValueObject, KValueObject)

// --------------------------------------------------------------------------------------------------------
template <class T>
void KDiscreteValueObject<T>::setValue ( T v )
{
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
template <class T>
T KDiscreteValueObject<T>::getValue () const
{
    T v;
    receiveValue(&v);
    return v;
}

// --------------------------------------------------------------------------------------------------------
template <class T>
const string & KDiscreteValueObject<T>::getNameForValue ( const T & typedValue ) const
{
    vector<T>::const_iterator result = find (values.begin(), values.end(), typedValue);
    if (result != values.end())
    {
        return names[result-values.begin()];
    }

    KConsole::printError("KDiscreteValueObject::getNameForValue failed");
    return names[0];
}

// --------------------------------------------------------------------------------------------------------
template <class T>
const T & KDiscreteValueObject<T>::getValueForName ( const string & valueName ) const
{
    vector<string>::const_iterator result = find (names.begin(), names.end(), valueName);
    if (result != names.end())
    {
        return (values[(result - names.begin())]);
    }

    KConsole::printError(kStringPrintf("getValueForName failed for name '%s'", valueName.c_str()));
    return (values[0]);
}

// --------------------------------------------------------------------------------------------------------
template <class T>
const T & KDiscreteValueObject<T>::getValueAtIndex ( int index ) const
{
    return values[index % values.size()];
}
                                                                            
// --------------------------------------------------------------------------------------------------------
template <class T>
void KDiscreteValueObject<T>::buttonCallback ( const string & buttonText )
{
    setValue(getValueForName(buttonText));
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KDiscreteValueObject<T>::setXMLValues ( string & xml )
{    
    string valueName;
    if (kXMLParseValue(xml, value_name, KDL_XML_VALUE_STRING, &valueName))
    {
        setValue(getValueForName(valueName));
    }
}

// --------------------------------------------------------------------------------------------------------
template <class T>
string KDiscreteValueObject<T>::getXMLValues ( int depth ) const
{     
    T typedValue = getValue();
    string valueName = getNameForValue(typedValue);
    return kXMLValue(value_name, KDL_XML_VALUE_STRING, &valueName, depth);
}

// --------------------------------------------------------------------------------------------------------
template <class T>
void KDiscreteValueObject<T>::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    KLabel * label = new KLabel(value_name);
    valueWidget->addChild(label);
        
    KButtonBox * buttonBox = new KButtonBox ();
    buttonBox->setFrameSpacing(0);
    valueWidget->addChild(buttonBox);
    
    string valueName = getNameForValue(getValue());
    
    for (int index = 0; index < (int)names.size(); index++)
    {
        KButton * button = new KButton(names[index]);
        button->addReceiverCallback(this, (KSetStringPtr)&KDiscreteValueObject<T>::buttonCallback);
        buttonBox->addButton(button);
        widgetArray->getWindow()->addPickable(buttonBox);
        if (valueName == names[index]) button->activate();
    }

    widgetArray->addChild(valueWidget);
}

#endif
