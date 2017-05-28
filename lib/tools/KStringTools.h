/*
 *  KStringTools.h
 *  kodisein
 */

#ifndef __KStringTools
#define __KStringTools

#pragma warning(disable:4786)

#include <string>
#include <vector>
#include <stdarg.h>

using namespace std;

#ifdef WIN32
#include <stdio.h>
#endif

// --------------------------------------------------------------------------------------------------------
void		kStringInsertStringBehindTags	( string & str, const string & insertString, const string & tag);
void		kStringMerge			( string & str, const string & str2, const string & divider );
vector<string>	kStringGetComponents		( const string & str, const string & divider );
void 		kStringReplace			( string &, const string & , const string & );
void		kStringReplaceTabs		( string &, unsigned int = 4 );
string		kStringGetSharedPrefix		( const vector<string> & );
void 		kStringCropCols 		( string & , string::size_type );
void 		kStringCropRows			( string & , string::size_type );
string::size_type	kStringNthCharPos		( const string & , string::size_type, char );
string::size_type	kStringRows 			( const string & );
string::size_type	kStringCols 			( const string & );
unsigned int	kStringWidth 			( const string & , bool = true);
unsigned int	kStringHeight 			( const string & , bool = true);
unsigned int 	kStringCountChars 		( const string &, char );
string 		kStringPrintf			( const char * ... );
string		kStringPrintFormArgs	( const string &, va_list * );
bool		kStringHasSuffix		( const string &, const string & );

#endif
