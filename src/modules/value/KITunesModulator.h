/*
 *  KITunesModulator.h
 *  kodisein
 */

#ifndef __KITunesModulator
#define __KITunesModulator

#include "KModulator.h"
#include "KITunesModulation.h"

class KITunesModulator : public KModulator
{
    KDS_MODULE_HEADER

    friend class 	KGlobalModulator;

    float 		iTunes_values[10];
    
    void		createConnectors	();
    void		updateValue		();
    float		valueForConnector	( KConnector * );
    
    protected:
    
    public:
    
                        KITunesModulator	();
                        
    void 		propagateValue 		( int = 0 );
    static float	getITunesValue		( int );
    float 		getValue 		() const { return iTunes_values[0]; }
    
    bool 		handleKey 		( const KKey & );
};

#endif
