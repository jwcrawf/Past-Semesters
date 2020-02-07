/*

id.h
Jonathan Crawford
9/17/2017

Header file for Class ID project

*/

#ifndef _ID_H
#define _ID_H

#include<iostream>
#include<string>

const char* const DEF_NAME = "#";
const int DEF_AGE = -1;

class ID
{
public:
  ID();                                // no argument constructor
  ~ID();                               // destructor
  ID(const char*, int);                // 2 argument constructor (name,age)
  ID(const ID&);                       // copy constructor
  const ID &operator = ( const ID& );  // copy assignment
  void        SetName (const char*);   // sets the name field
  void        SetAge  (int);           // sets the age field
  const char* GetName () const;        // returns a const pointer to the name
  int         GetAge  () const;        // returns the age field by value
 
private:
  char * name_; // the name field
  int age_;     // the age field
};

std::ostream& operator << (std::ostream& os, const ID&);

#endif
