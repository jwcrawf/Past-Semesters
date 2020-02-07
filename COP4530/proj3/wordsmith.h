/*
  wordsmith.h

  2/15/2018

  Jon Crawford

  Header file with definitions for wordsmith proj3

*/

#include <iostream>
#include <pair.h>
#include <xstring.h>
#include <list.h>
#include <ovector.h>
#include <olist.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>

#ifndef WORDSMITH_H
#define WORDSMITH_H

class WordSmith
{

public:
  
  WordSmith();
  ~WordSmith();
  bool ReadText(const fsu::String& infile, bool showProgress = 0);
  bool WriteReport(const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
  void ShowSummary() const;
  void ClearData();

private:
  
  typedef fsu::Pair < fsu::String, unsigned long > EntryType;
  typedef fsu::LessThan < EntryType > PredicateType;
  
  // typedef fsu::UOList       < EntryType , PredicateType > SetType; const char* set_type_string = "UOList";
  // typedef fsu::MOList       < EntryType , PredicateType > SetType; const char* set_type_string = "MOList";
   typedef fsu::UOVector     < EntryType , PredicateType > SetType; const char* set_type_string = "UOVector";
  // typedef fsu::MOVector     < EntryType , PredicateType > SetType; const char* set_type_string = "MOVector";
  // typedef fsu::BST_Threaded < EntryType , PredicateType > SetType; const char* set_type_string = "BST_Threaded";
  // typedef fsu::BST_ADT      < EntryType , PredicateType > SetType; const char* set_type_string = "BST_ADT";
  
  SetType wordset_;
  fsu::List < fsu::String > infiles_;
  
  static void Cleanup(fsu::String&);
  size_t Vocab() const { return wordset_.Size(); }
  size_t WordCount() const;

}; // end WordSmith

//#include <cleanup.cpp>

#endif

 
