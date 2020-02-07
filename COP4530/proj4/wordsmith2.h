/*  
  wordsmith2.h
	
  Jon Crawford
	
  2/28/2018
	
  Refactored header file with definitions for wordsmith 2
*/

#ifndef WORDSMITH_H
#define WORDSMITH_H

#include <xstring.h>
#include <list.h>
#include <oaa_bst.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

class WordSmith
{
public:
  WordSmith();
  virtual ~WordSmith();
  bool ReadText(const fsu::String& infile, bool showProgress = 0);
  bool WriteReport(const fsu::String& outfile,
                   unsigned short kw = 15,   // key col width 
                   unsigned short dw = 15,   // data col width
                   std::ios_base::fmtflags kf = std::ios_base::left, // key justify 
                   std::ios_base::fmtflags df = std::ios_base::right // data justify
                  ) const;
  void ShowSummary() const;
  void ClearData();

private:
  typedef fsu::String KeyType;
  typedef size_t DataType;

  fsu::OAA < KeyType , DataType > frequency_;
  fsu::List < fsu::String > infiles_;
  size_t globalCount_;
  static void Cleanup  (fsu::String& s);
	
  
} ;

#endif
