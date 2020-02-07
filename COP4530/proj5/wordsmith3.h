/*  
  wordsmith3.h
	
  Jon Crawford
	
  3/5/2018
	
  Refactored header file with definitions for wordsmith 3
*/

#ifndef WORDSMITH_H
#define WORDSMITH_H

#include <xstring.h>
#include <list.h>
#include <map_bst_threaded.h>
#include <mapiter_threaded.h>
#include <fstream>
#include <iostream>
#include <pair.h>

class WordSmith
{
public:
  WordSmith           ();
  virtual ~WordSmith  ();
  bool   ReadText     (const fsu::String& infile, bool showProgress = 0);
  bool   WriteReport  (const fsu::String& outfile,
                       unsigned short kw = 15, unsigned short dw = 15)  const;
  void   ShowSummary  () const;
  void   ClearData    ();
  void   ShowAnalysis () const;
private:
  typedef fsu::String                     KeyType;
  typedef size_t                          DataType;
  typedef fsu::Map_BST <KeyType,DataType> MapType;
  fsu::Map_BST < KeyType, DataType >      frequency_;
  fsu::List < fsu::String >               infiles_;
  size_t                                  globalCount_;

  static void Cleanup  (fsu::String& s);
	
} ;

#endif
