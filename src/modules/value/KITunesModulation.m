/*
 *  KITunesModulation.m
 *  kodisein
 */

#include "KITunesModulation.h"

#import <Foundation/Foundation.h>

// --------------------------------------------------------------------------------------------------------
void kGetITunesData ( float * dataBuffer )
{
    NSDistantObject * distantObject;
    
    distantObject = [NSConnection rootProxyForConnectionWithRegisteredName:@"KODISEIN_ITUNES_PLUGIN_CONNECTION" host:nil];

    if (distantObject)
    {
        [distantObject setProtocolForProxy:@protocol(ITunesHandlerProtocol)];
        [[((id <ITunesHandlerProtocol>)distantObject) getData] getBytes:dataBuffer];
    }
}
