/*

id.cpp
Jonathan Crawford
9/18/2017

Implementation for Class ID project

*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <id.h>

/////////////////////////////////////////
////  Default ID constructor
/////////////////////////////////////////
ID::ID() : name_(0), age_(0)
{
  this->SetName(DEF_NAME);
  this->SetAge(DEF_AGE);
}
/////////////////////////////////////////
////  ID destructor
/////////////////////////////////////////
ID::~ID() 
{
  delete[] name_; 
  name_ = 0; 
}
/////////////////////////////////////////
////  Value constructor
/////////////////////////////////////////
ID::ID(const char* newName,int newAge) : name_(0), age_(0)
{
  this->SetName(newName);
  this->SetAge(newAge);
}
/////////////////////////////////////////
////  Copy constructor
/////////////////////////////////////////
ID::ID(const ID& copyName) : name_(0), age_(0)
{
  this->SetName(copyName.GetName());
  this->SetAge(copyName.GetAge());
}
/////////////////////////////////////////
////  Copy assignment
/////////////////////////////////////////
const ID &ID::operator = ( const ID& copyID)
{
  if (this != &copyID)
    {
      this->SetName(copyID.GetName());
      this->SetAge(copyID.GetAge());
    }
  return *this;
}   
/////////////////////////////////////////
////  Name setter
/////////////////////////////////////////
void ID::SetName(const char* newName)
{
  if (name_ != 0)
    delete[] name_;
  name_= new char[strlen(newName)+1];
  strcpy(name_,newName);
  name_[strlen(name_)] = '\0'; 
}
/////////////////////////////////////////
////  Age setter
/////////////////////////////////////////
void ID::SetAge(int newAge)
{
  this->age_ = newAge;
}         
/////////////////////////////////////////
////  Name getter
/////////////////////////////////////////
const char* ID::GetName() const
{
  return name_;
}       
/////////////////////////////////////////
////  Age getter
/////////////////////////////////////////
int ID::GetAge() const
{
  return age_;
}
/////////////////////////////////////////
//// ostream operator
/////////////////////////////////////////
std::ostream& operator << (std::ostream& os, const ID& outID)
{ 
  std::cout << outID.GetName() << "\t" << outID.GetAge();
  return os;
}
