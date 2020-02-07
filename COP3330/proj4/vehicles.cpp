/*                                                                                                                                          
  vehicles.cpp                                                                                                                                                                                                                                                                         
  10/17/2017                                                                                                                                                                                                                                                                           
  Jon Crawford                                                                                                                                                                                                                                                                      
  file with vehicle definition implementation for the DOT Common Carrier Framework
  project                                                          
*/

#include <iostream>
#include <vehicles.h>
#include <cstring>


CommercialVehicle::CommercialVehicle () : passengerCapacity_(1), verbose_(0)
{ 
  vehicleRegistration_= new char[1];
  vehicleRegistration_[0] = '\0';
  
  operatorID_= new char[1];
  operatorID_[0] = '\0';

  operatorCDL_= new char[1];
  operatorCDL_[0] = '\0';
  
  if (verbose_)
    std::cout << "CommercialVehicle()" << std::endl;
}
CommercialVehicle::CommercialVehicle(const char* registration,const char* operatorID,
                                     const char* operatorCDL,unsigned short passengerCapacity,bool verbose)
  : passengerCapacity_(passengerCapacity),verbose_(verbose)
{
  vehicleRegistration_= new char[strlen(registration)+1];
  strcpy(vehicleRegistration_,registration);
  vehicleRegistration_[strlen(vehicleRegistration_)] = '\0';
  
  operatorID_= new char[strlen(operatorID)+1];
  strcpy(operatorID_,operatorID);
  operatorID_[strlen(operatorID_)] = '\0';
  
  operatorCDL_= new char[strlen(operatorCDL)+1];
  strcpy(operatorCDL_,operatorCDL);
  operatorCDL_[strlen(operatorCDL_)] = '\0';

  if (verbose_)
    std::cout << "CommercialVehicle(" << vehicleRegistration_ << "," << operatorID_ << ","
              << operatorCDL_ << "," << passengerCapacity_ << "," << verbose_ << ")" << std::endl;
}
CommercialVehicle::~CommercialVehicle()
{
  delete[] vehicleRegistration_;
  delete[] operatorID_;
  delete[] operatorCDL_;
  if (verbose_)
    std::cout << "~CommercialVehicle()" << std::endl;
}
const char* CommercialVehicle::Registration () const
{
  return vehicleRegistration_;
}
const char* CommercialVehicle::Operator () const
{
  return operatorID_;
}
const char* CommercialVehicle::CDL () const
{
  return operatorCDL_;
}
unsigned int CommercialVehicle::PassengerCapacity () const
{
  return passengerCapacity_;
}
float CommercialVehicle::LoadCapacity () const
{
  return 0.00;
}
const char* CommercialVehicle::ShortName () const
{
  return "UNK";
}
VehicleType CommercialVehicle::RegDecode (const char* sn)
{
  switch (sn[0])
  {
    case '0':
      return badReg;
      break;
    case '1':
      return vehicle;
      break;
    case '2':
      return carriage;
      break;
    case '3':
      return bus;
      break;
    case '4':
      return limo;
      break;
    case '5':
      return truck;
      break;
    case '6':
      return van;
      break;
    case '7':
      return tanker;
      break;
    case '8':
      return flatbed;
      break;
    default:
      return badReg;
      break;
  } //RegDecode
}  

Carriage::Carriage() : CommercialVehicle()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Carriage()" << std::endl;
}
Carriage::Carriage(const char* registration,const char* operatorID,const char* operatorCDL,unsigned short passengerCapacity,
                   bool verbose) 
  : CommercialVehicle(registration,operatorID,operatorCDL,passengerCapacity,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Carriage(" << Registration() << "," << Operator() << ","
              << CDL() << "," << CommercialVehicle::PassengerCapacity() << "," 
              << CommercialVehicle::verbose_ << ")" << std::endl;
}
Carriage::~Carriage()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Carriage()" << std::endl;
}
const char* Carriage::ShortName() const
{
  return "CAR";
}

Bus::Bus() : Carriage()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Bus()" << std::endl;
}
Bus::Bus(const char* registration,const char* operatorID,const char* operatorCDL,unsigned short passengerCapacity,
         bool verbose) 
  : Carriage(registration,operatorID,operatorCDL,passengerCapacity,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Bus(" << Registration() << "," << Operator() << ","
              << CDL() << "," << PassengerCapacity() << "," 
              << CommercialVehicle::verbose_ << ")" << std::endl;
}
Bus::~Bus()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Bus()" << std::endl;
}
const char* Bus::ShortName() const
{
  return "BUS";
}

Limo::Limo() : Carriage()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Limo()" << std::endl;
}
Limo::Limo(const char* registration,const char* operatorID,const char* operatorCDL,unsigned short passengerCapacity,
           bool verbose) 
  : Carriage(registration,operatorID,operatorCDL,passengerCapacity,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Limo(" << Registration() << "," << Operator() << ","
              << CDL() << "," << PassengerCapacity() << "," << CommercialVehicle::verbose_ << ")" << std::endl;
}
Limo::~Limo()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Limo()" << std::endl;
}
const char* Limo::ShortName() const
{
  return "LIM";
}

Truck::Truck() : CommercialVehicle()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Truck()" << std::endl;
}
Truck::Truck(const char* registration,const char* operatorID,const char* operatorCDL,bool verbose)
  : CommercialVehicle(registration,operatorID,operatorCDL,0,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Truck(" << Registration() << "," << Operator() << ","
              << CDL() << "," << CommercialVehicle::verbose_ << ")" << std::endl;
}
Truck::~Truck()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Truck()" << std::endl;
}
const char* Truck::ShortName() const
{
  return "TRK";
}

Van::Van () : Truck(), Box()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Van()" << std::endl;
}
Van::Van (const char* registration,const char* operatorID,const char* operatorCDL,float length,float width,
         float height,bool verbose)
  : Truck(registration,operatorID,operatorCDL,verbose), Box(length,width,height,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Van(" << Registration() << "," << Operator() << ","
              << CDL() << "," << Box::x_ << "," << Box::y_ << "," << Box::z_  
              << "," << CommercialVehicle::verbose_ << ")" << std::endl;
}
Van::~Van()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Van()" << std::endl;
}                                 
float Van::LoadCapacity() const
{
  float volume = Box::Volume();
  return volume;
}                                                                                       
const char* Van::ShortName() const
{
  return "VAN";
}

Tanker::Tanker () : Truck(), Cylinder()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Tanker()" << std::endl;
}
Tanker::Tanker (const char* registration,const char* operatorID,const char* operatorCDL,float radius,float height,
                bool verbose)
  : Truck(registration,operatorID,operatorCDL,verbose), Cylinder(radius,height,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Tanker(" << Registration() << "," << Operator() << ","
              << CDL() << "," << Cylinder::x_ << "," << Cylinder::z_ << ","
              << CommercialVehicle::verbose_ << ")" << std::endl;
}
Tanker::~Tanker()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Tanker()" << std::endl;
}
float Tanker::LoadCapacity() const
{
  float volume = Cylinder::Volume();
  return volume;
}
const char* Tanker::ShortName() const
{
  return "TNK";
}

Flatbed::Flatbed () : Truck(), Rectangle()
{
  if (CommercialVehicle::verbose_)
    std::cout << "Flatbed()" << std::endl;
}
Flatbed::Flatbed (const char* registration,const char* operatorID,const char* operatorCDL,float length,float width,
                  bool verbose)
  : Truck(registration,operatorID,operatorCDL,verbose), Rectangle(length,width,verbose)
{
  if (CommercialVehicle::verbose_)
    std::cout << "Flatbed(" << Registration() << "," << Operator() << ","
              << CDL() << "," << Rectangle::x_ << "," << Rectangle::y_ << "," 
              << CommercialVehicle::verbose_ << ")" << std::endl;
}
Flatbed::~Flatbed()
{
  if (CommercialVehicle::verbose_)
    std::cout << "~Flatbed()" << std::endl;
}
float Flatbed::LoadCapacity() const
{
  float area = Rectangle::Area();
  return area;
}
const char* Flatbed::ShortName() const
{
  return "FLT";
}
