/*
 *  KModulator.cpp
 *  kodisein
 */

#include "KModulator.h"
#include "KController.h"
#include "KPreferences.h"
#include "KModules.h"
#include "KGlobalModulator.h"
#include "KConsole.h"
#include "KSequenceGenerator.h"
#include "KConnectorValueOut.h"
#include "KConnectorModulatorIn.h"
#include "KConnectorModulatorOut.h"
#include "KKeyValueObject.h"
#include "KStringValueObject.h"
#include "KLabel.h"
#include "KKey.h"

#include <SDL.h>

#define MOUSE_BINDIG_X 1
#define MOUSE_BINDIG_Y 2

KDL_CLASS_INTROSPECTION_1 	(KModulator, KActivationValueModule)
KDS_MODULE_VALUES		(KModulator, "Modulator", 0.0, 0.0, 1.0f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModulator::KModulator ( bool fullCreation ) : KActivationValueModule ()
{
    sequence.push_back	(1000);
    
    activation_key	= "";
    playing  		= false;
    
    mouse_binding	= 0;
    
    seq_gen		= NULL;
    
    updateSequence	();
    reset		();
    last_value		= 0.0;
            
    if (fullCreation)
    {
        createConnectors ();
    }
}

// --------------------------------------------------------------------------------------------------------
KModulator::~KModulator ()
{
    deactivate ();
    disconnect ();
    if (seq_gen) delete seq_gen;
}

// --------------------------------------------------------------------------------------------------------
void KModulator::advanceTimePos ( int msecDiff )
{
    time_pos = (sequence_length + time_pos + msecDiff) % sequence_length; // current position in sequence

    int sequenceIndex;
    int sequenceSize = sequence.size();
    int nextValue = 0, prevValue; // find values before and after current position
    for (sequenceIndex = 0; sequenceIndex < sequenceSize; sequenceIndex++)
    {
        nextValue += sequence[sequenceIndex];
        if (nextValue > time_pos) break;
    }
    prevValue = nextValue - sequence[sequenceIndex];
                
    value = (float)(time_pos - prevValue) / (float)(nextValue - prevValue); // map value to [0,1] 
}

// --------------------------------------------------------------------------------------------------------
void KModulator::updateValue ()
{
    if (playing) // update value if playing
    {
        if (mouse_binding)
        {
            if (mouse_binding == MOUSE_BINDIG_X)
            {
                value = Controller.modules->global_modulator->getMouseX();
            }
            else 
            {
                value = Controller.modules->global_modulator->getMouseY();
            }
        }
        else
        {
            unsigned int now = KEventHandler::getTime();
            if (last_time == 0) 
            {
                last_time = now;
            }
            int msecDiff = now-last_time; // time in milliseconds since last frame
            
            if (factor_sgn != 0) //smooth start or stop
            {
                int duration = (int)(1000/factor_delta); // complete duration of smooth start or stop
                int restTime = (int)(duration * kAbs(factor_sgn) - msecDiff); // rest time in milliseconds
                
                if (factor_sgn > 0) 
                {
                    factor_sgn = kMax(0.0, restTime / (float)duration);
                    msecDiff = (int)(msecDiff * (1 - factor_sgn));
                }
                else
                {
                    factor_sgn = kMin(0.0, -(restTime / (float)duration));
                    if (factor_sgn == 0) 
                    {
                        stop();
                        return;
                    }
                    msecDiff = (int)(msecDiff * (-factor_sgn));
                }
            }
            
            advanceTimePos(msecDiff);
    
            last_time = now;
        }
    }
    
    if (last_value != value) // propagate if value changed
    {
        propagateValue(Controller.frame_time);
    }
    
    last_value = value;
}

// --------------------------------------------------------------------------------------------------------
void KModulator::reset ()
{ 
    last_time  		= 0;
    time_pos 		= 0;
    value		= 0.0;
    factor_delta	= 0.2f;
    factor_sgn		= 0.0;
    
    if (playing == false) 
    {
        propagateValue (Controller.frame_time);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModulator::stopPlaying ()
{ 
    playing	= false;
}

// --------------------------------------------------------------------------------------------------------
void KModulator::stop () 
{ 
    playing	= false;
    propagateValue (Controller.frame_time);
}

// --------------------------------------------------------------------------------------------------------
void KModulator::start () 
{ 
    last_time  	= 0; 
    playing	= true;
}

// --------------------------------------------------------------------------------------------------------
// changes the speed of the sequence by speedFactor
// 1.0 = no changes, < 1.0 = slower, > 1.0 = faster
void KModulator::changeSpeed ( float speedFactor )
{
    vector<int>::iterator iter = sequence.begin();
    while (iter != sequence.end())
    {
        int newValue = kMax(10, (int)((*iter) * speedFactor));
        
        if (newValue == (*iter) || newValue >= 123456789)
        {
            // we don't change any values or reached maximum length -> stop changes
            return;
        }
        (*iter) = newValue;
        iter++;
    }
    
    time_pos = (int)(time_pos * speedFactor);
    
    updateSequence();
}

// --------------------------------------------------------------------------------------------------------
void KModulator::updateSequence ()
{
    sequence_length = 0;
    vector<int>::iterator iter = sequence.begin();
    while (iter != sequence.end())
    {
        sequence_length += (*iter);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModulator::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();

    float ir = sqrt(3), h = 0.5;

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, h, ir);
    glVertex3f( 1.0, h, ir);
    glVertex3f( 2.0, h, 0.0);
    glVertex3f( 1.0, h, -ir);
    glVertex3f(-1.0, h, -ir);
    glVertex3f(-2.0, h, 0.0);
    glVertex3f(-1.0, h, ir);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-1.0, -h, ir);
    glVertex3f(-2.0, -h, 0.0);
    glVertex3f(-1.0, -h, -ir);
    glVertex3f( 1.0, -h, -ir);
    glVertex3f( 2.0, -h, 0.0);
    glVertex3f( 1.0, -h, ir);
    glVertex3f(-1.0, -h, ir);
    glEnd();
}
 
// --------------------------------------------------------------------------------------------------------
void KModulator::createConnectors ()
{
    int index;
    float ir = sqrt(3), h = 0.5;
        
    KConnector * connector;
    
    connector = new KConnectorValueOut( this, "value out 0" );
    connector->translate(0.0, h+KDS_VALUECONNECTOR_RADIUS, 0.0);
    addConnector(connector);

    for (index = 0; index < 6; index++)
    {
        connector = new KConnectorValueOut( this, kStringPrintf("value out %d", index+1) );
        connector->rotate (0.0, index * 60.0, 0.0);
        connector->translate(0.0, h+KDS_VALUECONNECTOR_RADIUS, 1.0);
        addConnector(connector);
    }
    
    connector = new KConnectorModulatorIn (this);
    connector->translate(0.0, 0.0, -ir - KDS_CONNECTOR_MIN_DISTANCE);
    connector->rotate (-90.0, 180.0, 0.0);
    addConnector(connector);

    for (index = 2; index < 7; index++)
    {
        connector = new KConnectorModulatorOut (this, kStringPrintf("modulator %d", index));
        connector->rotate (0.0, ((index % 5) + 1) * 60.0, 0.0);
        connector->translate(0.0, 0.0, -ir);
        connector->rotate (-90.0, 0.0, 0.0);
        addConnector(connector);
    }
    
    KValueObject * value;

    value = new KKeyValueObject( "activation key", 1 );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModulator::setActivationKey);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KModulator::getActivationKey);
    
    value = new KStringValueObject( "sequence" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModulator::setSequenceString);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KModulator::getSequenceString);      
}

// --------------------------------------------------------------------------------------------------------
void KModulator::setSequenceString ( const string & s )
{
    string str = s;
    unsigned int loc;
    sequence.clear();
    
    while ((loc = str.find(' ')) != string::npos)
    {	
        if (loc > 0) sequence.push_back(1000 * atof(str.substr(0, loc).c_str()));
        str.erase(0, loc+1);
    }
    if (str.size() > 0) sequence.push_back(1000 * atof(str.c_str()));
    
    updateSequence ();
}

// --------------------------------------------------------------------------------------------------------
string KModulator::getSequenceString () const
{
    string str = "";
    vector<int>::const_iterator iter = sequence.begin();
    while (iter != sequence.end())
    {
        char cstr[256];
        sprintf(cstr, "%g ", GLfloat(*iter)/1000.0);
        str += cstr;
        iter++;
    }
    str.resize(kMax(1, str.size()-1));
    return str;
}

// --------------------------------------------------------------------------------------------------------
string KModulator::getDisplayName () const
{ 
    return kStringPrintf("[%s %s]", getName().c_str(), activation_key.c_str()); 
}

// --------------------------------------------------------------------------------------------------------
void KModulator::activate ()
{
    Controller.addKeyHandler(this);
    activated = true;
}

// --------------------------------------------------------------------------------------------------------
void KModulator::deactivate ()
{
    Controller.removeKeyHandler(this);
    activated = false;    
}

// --------------------------------------------------------------------------------------------------------
bool KModulator::handleKey ( const KKey & key )
{       
    if (key.character >= '1' && key.character <= '9')	// todo: preferences
    {
        factor_delta = 1.0 / (key.character - '0');
    }
    else if (key.name == "ALT_" + activation_key || key.name == "CTRL+ALT_" + activation_key) 
    { // activate new recorded sequence
        if (seq_gen)
        {
            sequence = seq_gen->getSequence();		// activate new sequence
            updateSequence();				
            delete seq_gen;				// delete recorded sequence
            seq_gen = NULL;
        }
    
        reset();

        if (SDL_GetModState() & KMOD_CTRL)		// CTRL+ALT = smooth start
        {
            factor_sgn = 1;
        }
    }
    else if (key.name == "CTRL_" + activation_key)	// sequence recording
    {
        if (seq_gen == NULL)				// start new sequence ...
        {
            seq_gen = new KSequenceGenerator ();
        }
        else						// ... or add to current sequence
        {
            seq_gen->trigger();
        }
    }
    else if (key.name == Controller.preferences->getResetKey())
    {
        if (playing || value > 0.0) 
        {
            reset();
        }
        else
        {
            time_pos 	= 0;
            last_time  	= 0;
            factor_sgn 	= 0.0;
            value 	= 1.0;
            
            propagateValue(0);
        }
    }
    else if (key.name == Controller.preferences->getValueUpKey())
    {
        if (playing == false)
        {
            advanceTimePos(sequence_length * factor_delta * 0.1);
            last_time = KEventHandler::getTime();
            updateValue();
        }
    }
    else if (key.name == Controller.preferences->getValueDownKey())
    {
        if (playing == false)
        {
            advanceTimePos(-sequence_length * factor_delta * 0.1);
            last_time = KEventHandler::getTime();
            updateValue();
        }
    }
    else if (key.name == Controller.preferences->getSmoothStartKey())  	
    {
        if (factor_sgn >= 0) 
        {
            factor_sgn = 1; 
        }
        else 
        {
            factor_sgn = 1+factor_sgn;
        }
        if (playing == false)
        {
            start();
        }
    }
    else if (key.name == Controller.preferences->getSmoothStopKey())	
    {
        if (factor_sgn <= 0) 
        {
            factor_sgn = -1;
        }
        else 
        {
            factor_sgn = -1+factor_sgn;
        }
    }
    else if (key.name == Controller.preferences->getBindMouseXKey())
    {
        if (mouse_binding == MOUSE_BINDIG_X) mouse_binding = 0;
        else mouse_binding = MOUSE_BINDIG_X;
    }
    else if (key.name == Controller.preferences->getBindMouseYKey())
    {        
        if (mouse_binding == MOUSE_BINDIG_Y) mouse_binding = 0;
        else mouse_binding = MOUSE_BINDIG_Y;
    }
    else if (key.name == Controller.preferences->getSpeedUpKey()) 	changeSpeed(1.0-0.04*factor_delta);
    else if (key.name == Controller.preferences->getSpeedDownKey())  	changeSpeed(1.0+0.04*factor_delta);
    else if (key.name == Controller.preferences->getStartStopKey())  	playing ? stop() : start();
    else if (key.name == Controller.preferences->getSpeedMultiplyKey())	changeSpeed(factor_delta); 
    else if (key.name == Controller.preferences->getSpeedDivideKey())	changeSpeed(1.0/factor_delta);
    
    return false; // modulators never want to block other key handlers
}

// --------------------------------------------------------------------------------------------------------
void KModulator::initInspector ( KModuleInspector * inspector )
{
    KModule::initInspector(inspector); // override value modules initInspector method
}

// --------------------------------------------------------------------------------------------------------
void KModulator::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    valueWidget->addChild(new KLabel(kStringPrintf("<%s>", activation_key.c_str())));
}

