/*
 *  KXMLTools.h
 *  kodisein
 */

#ifndef __KXMLTools
#define __KXMLTools

#pragma warning(disable:4786)

#include "KStringTools.h"

#define KDL_XML_INDENT 2

enum {	KDL_XML_VALUE_FLOAT, KDL_XML_VALUE_INT, KDL_XML_VALUE_CHAR, KDL_XML_VALUE_BOOL, 
        KDL_XML_VALUE_STRING, KDL_XML_VALUE_VERTEX, KDL_XML_VALUE_SIZE, KDL_XML_VALUE_POSITION,
        KDL_XML_VALUE_MATRIX, KDL_XML_VALUE_SEPARATED_MATRIX };

// --------------------------------------------------------------------------------------------------------
string		kXMLReadNamedAttribute	( const string &, const string & );
bool		kXMLReadNamedOpenTag	( const string &, const string &, string * = NULL);
string		kXMLParseToTagsInVector	( string &, const vector<string> & );
string		kXMLParseNamedOpenTag	( string &, const string &, string * = NULL, bool = true );
bool		kXMLParseNamedCloseTag	( string &, const string &, bool = true );
bool		kXMLParseOpenTag	( string &, string &, string * = NULL, bool = true );
bool 		kXMLParseValue		( string &, const string &, int, void *, bool = true);

string		kXMLTag			( const string &, const string & = "", int = 0 );
string 		kXMLOpenTag 		( const string &, const string & = "", int = 0 );
string 		kXMLCloseTag 		( const string &, int = 0 );
string		kXMLPrintf		( int, const char * ...);
string 		kXMLValue		( const string &, int, const void * , int = 0 );

#endif