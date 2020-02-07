/*

  shapes.cpp

  10/13/17

  Jon Crawford


  Implementation file for DOT Common Carrier project

*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <shapes.h>


Shape::Shape () : x_(1), y_(1), z_(1), verbose_(0)
{
  if (verbose_)
    std::cout << "Shape()" << std::endl;
}

Shape::Shape (float x, float y, float z, bool verbose) : x_(x), y_(y), z_(z), verbose_(verbose)
{
  if (verbose_)
    std::cout << "Shape(" << x_ << "," << y_
              << "," << z_ << "," << verbose_
              << ")" << std::endl;
}

Shape::~Shape()
{
  if (verbose_)
    std::cout << "~Shape()" << std::endl;
}

const char* Shape::Name () const
{
  return "generic";
}

float Shape::Volume () const
{
  return 0.00;
}

float Shape::Area () const
{ 
  return 0.00;
}

Box::Box () : Shape()
{
  if (Shape::verbose_)
    std::cout << "Box()" << std::endl;
}

Box::Box (float length, float width, float height, bool verbose) : Shape(length,width,height,verbose)

{
  if (Shape::verbose_)
    std::cout << "Box(" << x_ << "," << y_  
              << "," << z_ << "," << verbose_ 
              << ")" << std::endl;
}

Box::~Box() 
{
  if (Shape::verbose_)
    std::cout << "~Box()" << std::endl;
}

const char* Box::Name () const
{
  return "box";
}
                      
float Box::Volume () const
{
  float volume = (x_*y_*z_);
  return volume;
}
       
float Box::Area () const
{    //A=2(lw+lh+hw)
  float area = 2*((x_*y_) + (x_*z_) + (y_ *z_));
  return area;
}

// Class Cylinder
Cylinder::Cylinder () : Shape()           
{
  if (Shape::verbose_)
    std::cout << "Cylinder()" << std::endl;
}

Cylinder::Cylinder (float radius, float height, bool verbose) : Shape (radius,0,height,verbose)
{
  if (Shape::verbose_)
    std::cout << "Cylinder(" << x_ << "," << z_
              << "," << verbose_
              << ")" << std::endl;
}

Cylinder::~Cylinder()
{
  if (Shape::verbose_)
    std::cout << "~Cylinder()" << std::endl;
}

const char* Cylinder::Name () const
{
  return "cylinder";
}

float Cylinder::Volume () const
{
  float volume = (M_PI*z_*(pow(x_,2)));
  return volume;
}

float Cylinder::Area () const
{    //A=2πrh+2πr^2                                                                                                                       
  float area = (2*M_PI*z_*x_) + (2*M_PI*(pow(x_,2)));
  return area;
}

// class Rectangle
Rectangle::Rectangle () : Shape()
{
  if (Shape::verbose_)
    std::cout << "Rectangle()" << std::endl;
}

Rectangle::Rectangle (float length, float width, bool verbose) : Shape(length,width,0,verbose)

{
  if (Shape::verbose_)
    std::cout << "Rectangle(" << x_ << "," << y_
              << "," << verbose_
              << ")" << std::endl;
}

Rectangle::~Rectangle()
{
  if (Shape::verbose_)
    std::cout << "~Rectangle()" << std::endl;
}

const char* Rectangle::Name () const
{
  return "rectangle";
}

float Rectangle::Area () const
{
  float area = x_ * y_;
  return area;
}
