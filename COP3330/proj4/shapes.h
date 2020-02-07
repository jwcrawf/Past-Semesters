/*                                                                       
  shapes.h                                                               
  10/11/17                                                                
  Jon Crawford                                                           
                                                                         
  Header file with shape definitions for DOT Common Carrier project                         
*/

#ifndef _SHAPES_H
#define _SHAPES_H

#include <cstdlib>


class Shape
{
public:
  Shape();
  Shape (float x, float y, float z, bool verbose = 0);
  virtual ~Shape();
  virtual const char* Name () const;  // returns "generic"
  virtual float Volume () const;  // returns volume of object  
  virtual float Area () const;  // returns area of object

private:
  Shape (const Shape&);
  Shape& operator = (const Shape&);
protected:
  float x_, y_, z_; // dimensions of shape
  bool verbose_;   // default value 0 given in constructor prototype
};

class Box : public Shape
{
public:
  Box ();
  Box (float length, float width, float height, bool verbose = 0);
  virtual ~Box();
  const char* Name () const;  // returns "box"
  float Volume () const;  // returns volume of box object  
  float Area () const;  // returns surface area of box object

private:
  Box (const Box&);
  Box& operator = (const Box&);
};

class Cylinder : public Shape
{
public:
  Cylinder ();
  Cylinder (float radius, float height, bool verbose = 0);
  virtual ~Cylinder();
  const char* Name () const;  // returns "cylinder"
  float Volume () const;  // returns volume of cylinder object  
  float Area () const;  // returns surface area of cylinder object

private:
  Cylinder (const Cylinder&);
  Cylinder& operator = (const Cylinder&);
};

class Rectangle : public Shape
{
public:  
  Rectangle ();
  Rectangle (float length, float width, bool verbose = 0);
  virtual ~Rectangle();
  const char* Name () const;  // returns "rectangle"
  float Area () const;  // returns area of rectangle object
   
private:
  Rectangle (const Rectangle&);
  Rectangle& operator = (const Rectangle&);
};

#endif
