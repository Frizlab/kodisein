/*
 *  KModuleObjectText.cpp
 *  kodisein
 */

#include "KModuleObjectText.h"
#include "KText.h"
#include "KStringValueObject.h"
#include "KConnectorDiscreteValueInOut.h"
#include "KXMLTools.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectText, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectText, "Text", 1.0, 1.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleObjectText::KModuleObjectText () : KObjectModule ()
{
    matrix_object = new KText (this);

    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectText::createConnectors ()
{
    KValueObject * value;

    value = new KStringValueObject("text");
    values.push_back(value);
    values.back()->addReceiverCallback(matrix_object, (KSetStringPtr)&KText::setText);
    values.back()->setProviderCallback(matrix_object, (KGetStringPtr)&KText::getText);    

    vector<string> names;
    names.push_back("roman");
    names.push_back("mono roman");
    names.push_back("8x13");
    names.push_back("9x15");
    names.push_back("times 10");
    names.push_back("times 24");
    names.push_back("helvetica 10");
    names.push_back("helvetica 12");
    names.push_back("helvetica 18");
    vector<void*> fonts;
    fonts.push_back(GLUT_STROKE_ROMAN);
    fonts.push_back(GLUT_STROKE_MONO_ROMAN);
    fonts.push_back(GLUT_BITMAP_8_BY_13);
    fonts.push_back(GLUT_BITMAP_9_BY_15);
    fonts.push_back(GLUT_BITMAP_TIMES_ROMAN_10);
    fonts.push_back(GLUT_BITMAP_TIMES_ROMAN_24);
    fonts.push_back(GLUT_BITMAP_HELVETICA_10);
    fonts.push_back(GLUT_BITMAP_HELVETICA_12);
    fonts.push_back(GLUT_BITMAP_HELVETICA_18);
    
    KConnectorValueInOut * ioConnector;
    
    ioConnector = new KConnectorDiscreteValueInOut<void*>( this, names, fonts, "font" );
    ioConnector->translate (-(1.0 + KDS_VALUECONNECTOR_RADIUS), 0.0, 0.0);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetDataPtr)&KText::setFont);
    values.back()->setProviderCallback(matrix_object, (KGetDataPtr)&KText::getFont);  
}

