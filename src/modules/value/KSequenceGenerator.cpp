/*
 *  KSequenceGenerator.cpp
 *  kodisein
 */

#include "KSequenceGenerator.h"
#include "KConsole.h"

#include <SDL.h>

// -------------------------------------------------------------------------------------------------------- 
KSequenceGenerator::KSequenceGenerator ()
{
    last_time = SDL_GetTicks();
}

// -------------------------------------------------------------------------------------------------------- 
void KSequenceGenerator::trigger ()
{
    unsigned int now = SDL_GetTicks();
    
    sequence.push_back(now - last_time);
        
    last_time = now;
}

// -------------------------------------------------------------------------------------------------------- 
void KSequenceGenerator::printSequence ( vector<int> * seq )
{
    if (seq == NULL) seq = &sequence;
    string seqString;
    vector<int>::iterator iter = seq->begin();
    while (iter != seq->end())
    {
        seqString += kStringPrintf("%d ", (*iter));
        iter++;
    }
    KConsole::print(seqString);
}

// -------------------------------------------------------------------------------------------------------- 
vector<int> KSequenceGenerator::getSequence () 
{ 
    int maxLength	= (sequence.size()+1)/2;
    int bestLength	= 0;
    int bestLengthDiff	= INT_MAX;
    int length, index, seqIndex;
    
    printSequence(&sequence);
    
    // ................................ calculate difference sums for each length
    for (length = 1; length <= maxLength; length++) 
    {
        int diffSum = 0;
        
        for (index = 0; index < length; index++)
        {
            int indexDiffSum = 0;
            
            sequence.push_back(sequence[length-1]); // insert missing last gap
            
            for (seqIndex = 1; seqIndex < (int)sequence.size() / length; seqIndex++)
            {
                indexDiffSum += abs(sequence[seqIndex*length+index] - sequence[(seqIndex-1)*length+index]);
            }
            
            sequence.pop_back();
            
            diffSum += indexDiffSum;
        }
        
        if (length > 1) // weight differences
        {
            diffSum *= (int)(1.0+1.0/float(length-1));
        }
        
        if (diffSum < bestLengthDiff) 
        {
            bestLengthDiff 	= diffSum;
            bestLength 		= length;
        }
    }
    
    // ................................ average differences for best length
    vector<int> bestSequence; 
    
    for (index = 0; index < bestLength; index++)
    {
        int indexSum = 0;
        
        for (seqIndex = 0; seqIndex < (int)sequence.size() / bestLength; seqIndex++)
        {
            indexSum += sequence[seqIndex*bestLength+index];
        }
        
        bestSequence.push_back(indexSum / (sequence.size() / bestLength));
    }

    printSequence(&bestSequence);
    
    return bestSequence;
}