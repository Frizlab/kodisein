/*
 *  KModulator.h
 *  kodisein
 */

#ifndef __KModulator
#define __KModulator

#include "KActivationValueModule.h"
#include "KKeyHandler.h"

#define DEBUG_MODULATORS true

class KModuleInspector;
class KSequenceGenerator;

class KModulator : public KActivationValueModule, public KKeyHandler
{
    KDS_MODULE_HEADER
    
    friend class KGlobalModulator;
    
    protected:
    
    float			value;
    float			last_value;
    
    int				mouse_binding;
    
    bool			playing;
    
    unsigned int		last_time;
    int				time_pos;				
    int				sequence_length;
    
    void			updateSequence		();
    void			createConnectors	();
    
    vector<int>			sequence;
    float			factor_sgn;
    float			factor_delta;
    
    KSequenceGenerator * 	seq_gen;
    
    public:
                                KModulator		( bool = true );
    virtual                    ~KModulator		();
                                
    void			changeSpeed		( float );
    void			reset			();
    void			start			();
    void			stop			();
    void			stopPlaying		();
    bool			shouldPropagate		( int = 0 ) { return true; }

    
    string			getSequenceString	() const;
    void			setSequenceString	( const string & );
    virtual string		getDisplayName		() const;
    
    virtual void		activate		();
    virtual void		deactivate		();

    virtual void		displayConnectors	( int mode );
    virtual float 		getValue 		() const { return value; }
    virtual void		updateValue		();
    virtual void		advanceTimePos		( int msecDiff );
    
    virtual bool 		handleKey 		( const KKey & );
    
    virtual void		initInspector 		( KModuleInspector * );
    void 			addToWidget		( KWidgetArray *, int = 0 );
};

#endif
