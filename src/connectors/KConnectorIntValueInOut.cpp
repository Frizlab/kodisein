/*
 *  KConnectorIntValueInOut.cpp
 *  kodisein
 */

#include "KConnectorIntValueInOut.h"

#include "KValueModule.h"
#include "KModulator.h"
#include "KModules.h"
#include "KConsole.h"
#include "KButtonBox.h"
#include "KButton.h"
#include "KLabel.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KConnectorIntValueInOut, KConnectorValueInOut)

// --------------------------------------------------------------------------------------------------------
void KConnectorIntValueInOut::setValue ( float v )
{
    notifyReceivers(getValueAtIndex(v)); // notify receivers without changing internal value
}

// --------------------------------------------------------------------------------------------------------
void KConnectorIntValueInOut::providerSet ()
{
    // this message is send, if a provider was ?. get and store the value from the provider.
    int v;
    receiveValue(&v);
    value = (float)getIndexForValue(v);
}

// --------------------------------------------------------------------------------------------------------
void KConnectorIntValueInOut::setTypedReceiverValue ( int v )
{
    value = (float)getIndexForValue(v);
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
const string & KConnectorIntValueInOut::getNameForValue ( int typedValue ) const
{
    vector<int>::const_iterator result = find (values.begin(), values.end(), typedValue);
    if (result != values.end())
    {
        return names[result - values.begin()];
    }

    KConsole::printError(kStringPrintf("getNameForValue failed for module\n'%s'",
                                                                            module->getName().c_str()));
    return names[0];
}

// --------------------------------------------------------------------------------------------------------
int KConnectorIntValueInOut::getValueForName ( const string & valueName ) const
{
    vector<string>::const_iterator result = find(names.begin(), names.end(), valueName);
    if (result != names.end())
    {
        return values[(result - names.begin())];
    }

    KConsole::printError(kStringPrintf("getValueForName failed for name '%s'", valueName.c_str()));
	if (values.size() >= 1)
	{
		return values[0];
	}
	return 0;
}

// --------------------------------------------------------------------------------------------------------
int KConnectorIntValueInOut::getValueAtIndex ( int index ) const
{
    return values[index % values.size()];
}
                                                                            
// --------------------------------------------------------------------------------------------------------
int KConnectorIntValueInOut::getIndexForValue ( int v ) const
{
    vector<int>::const_iterator result = find(values.begin(), values.end(), v);
    return (result-values.begin());
}

// --------------------------------------------------------------------------------------------------------
void KConnectorIntValueInOut::buttonCallback ( const string & buttonText )
{
    setTypedReceiverValue(getValueForName(buttonText));
}

// --------------------------------------------------------------------------------------------------------
void KConnectorIntValueInOut::setXMLValues ( string & xml )
{    
    string valueName;
    if (kXMLParseValue(xml, getName(), KDL_XML_VALUE_STRING, &valueName)) 
    {
        setTypedReceiverValue(getValueForName(valueName));
    }
}

// --------------------------------------------------------------------------------------------------------
string KConnectorIntValueInOut::getXMLValues ( int depth ) const
{     
    string valueName = getNameForValue(getValueAtIndex((int)value));
    return kXMLValue(getName(), KDL_XML_VALUE_STRING, &valueName, depth);
}

// --------------------------------------------------------------------------------------------------------
void KConnectorIntValueInOut::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    widgetArray->addChild(valueWidget);

    KLabel * label = new KLabel(getName());
    valueWidget->addChild(label);
        
    KButtonBox * buttonBox = new KButtonBox ();
    buttonBox->setFrameSpacing(0);
    valueWidget->addChild(buttonBox);
    
    string valueName = getNameForValue(getValueAtIndex(value));
    
    for (int index = 0; index < (int)names.size(); index++)
    {
        KButton * button = new KButton(names[index]);
		if (valueName == names[index]) button->activate();
        button->addReceiverCallback(((KFloatValueObject*)this),
(KSetStringPtr)(void (KFloatValueObject::*)(const string &))&KConnectorIntValueInOut::buttonCallback);
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