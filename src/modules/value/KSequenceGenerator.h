/*
 *  KSequenceGenerator.h
 *  kodisein
 */

#ifndef __KSequenceGenerator
#define __KSequenceGenerator

#include <vector>

using namespace std;

class KSequenceGenerator
{
    protected:
    
    int			last_time;
    vector<int>		sequence;
    
    public:
        
                        KSequenceGenerator 	();
    virtual		~KSequenceGenerator	() {}
                        
    virtual void 	trigger			();
    vector<int>		getSequence		();
    virtual void	reset			() { sequence.clear(); }
    void		printSequence		( vector<int> * );
};

#endif