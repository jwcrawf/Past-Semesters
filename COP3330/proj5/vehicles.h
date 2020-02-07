/*
  vehicles.h

  10/17/2017

  Jon Crawford

  header file with vehicle definitions for the DOT Common Carrier Framework project
*/

#ifndef _VEHICLES_H
#define _VEHICLES_H

#include <shapes.h>
#include <iostream>

enum VehicleType {badReg = 0,vehicle = 1,carriage = 2,bus = 3,limo = 4,truck = 5,van = 6,tanker = 7,flatbed = 8};

class CommercialVehicle
{
public:
  CommercialVehicle ();
  CommercialVehicle(const char* registration,const char* operatorID,const char* operatorCDL,
                    unsigned short passengerCapacity,bool verbose = 0);
  virtual ~CommercialVehicle();
  const char* Registration () const; // returns vehicle reg
  const char* Operator () const; // returns operator ID   
  const char* CDL () const; // returns operator CDL  
  unsigned int PassengerCapacity () const; // returns passenger
  virtual float LoadCapacity () const; // returns volume or area
  virtual const char* ShortName () const; // returns "UNK"
  static VehicleType RegDecode (const char* sn);

private:
  CommercialVehicle (const CommercialVehicle&);
  CommercialVehicle& operator = (const CommercialVehicle&);
  char* vehicleRegistration_;
  char* operatorID_;
  char* operatorCDL_;
  unsigned short passengerCapacity_;

protected:
  bool verbose_;
};

class Carriage: public CommercialVehicle
{
public:
  Carriage ();
  Carriage (const char* registration,const char* operatorID,const char* operatorCDL,
            unsigned short passengerCapacity,bool verbose = 0);
  virtual ~Carriage();
  const char* ShortName() const; // returns "CAR"

private:
  Carriage (const Carriage&);
  Carriage& operator = (const Carriage&); 
};

class Bus: public Carriage
{
public:
  Bus ();
  Bus (const char* registration,const char* operatorID,const char* operatorCDL,
       unsigned short passengerCapacity,bool verbose = 0);
  virtual ~Bus();
  const char* ShortName() const; // returns "BUS"                                                                   

private:
  Bus (const Bus&);
  Bus& operator = (const Bus&);
};

class Limo: public Carriage
{
public:
  Limo ();
  Limo (const char* registration,const char* operatorID,const char* operatorCDL,
        unsigned short passengerCapacity,bool verbose = 0);
  virtual ~Limo();
  const char* ShortName() const; // returns "LIM"                                                                   

private:
  Limo (const Limo&);
  Limo& operator = (const Limo&);
};

class Truck: public CommercialVehicle
{
public:
  Truck ();
  explicit Truck (const char* registration,const char* operatorID,const char* operatorCDL,
                  bool verbose = 0);
  virtual ~Truck();
  const char* ShortName() const; // returns "TRK"                                                                   

private:
  Truck (const Truck&);
  Truck& operator = (const Truck&);
};

class Van : public Truck, public Box
{
public:
  Van ();
  Van (const char* registration,const char* operatorID,const char* operatorCDL,float length,float width,
       float height , bool verbose = 0);
  virtual ~Van();
  float LoadCapacity() const; // returns volume of box  
  const char* ShortName() const; // returns "VAN"

private:
  Van (const Van&);
  Van& operator = (const Van&);
};

class Tanker : public Truck, public Cylinder
{
public:
  Tanker ();
  Tanker (const char* registration,const char* operatorID,const char* operatorCDL,float radius,float length,
          bool verbose = 0);
  virtual ~Tanker();
  float LoadCapacity() const; // returns volume of cylinder                                                              
  const char* ShortName() const; // returns "TNK"                                                                   

private:
  Tanker (const Tanker&);
  Tanker& operator = (const Tanker&);
};

class Flatbed : public Truck, public Rectangle
{
public:
  Flatbed ();
  Flatbed (const char* registration,const char* operatorID,const char* operatorCDL,float length,float width,
           bool verbose = 0);
  virtual ~Flatbed();
  float LoadCapacity() const; // returns area of rectangle                                                              
  const char* ShortName() const; // returns "FLT"                                                                   

private:
  Flatbed (const Flatbed&);
  Flatbed& operator = (const Flatbed&);
};
 
#endif
