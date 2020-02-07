/*                                                                                                                                          
  tracker.cpp
                                                                                                                                            
  10/24/2017
                                                                                                                                            
  Jon Crawford
                                                                                                                                            
  file with tracking Main implementation for the FastLane project                                                   
                                                                                                                                   
*/

#include <iostream>
#include <vehicles.h>
#include <cstring>
#include <iomanip>

const unsigned int 
  C1 = 6, 
  C2 = 10, 
  C3 = 10, 
  c4 = 2, 
  c5 = 2, 
  c6 = 2, 
  maxShiftSize = 100, 
  maxStringSize = 50; 

const char* const badRegMsg = "BadRegistration";
const char* const badIDMsg  = "BadOperatorID";
const char* const badCDLMsg = "BadOperatorCDL";

int main()
{
  unsigned int 
    shiftSize,
    C4, C5, C6;
  VehicleType vehicleType;
  size_t shiftCount = 0;  
  std::cout <<"\nFastLane Tracker started...\n" << std::endl;
                  
  do {
    
    std::cin >> shiftSize;
    if (shiftSize == 0)
      break;
    if (shiftSize > maxShiftSize)
    {
      std::cout << "** Tracker error: max shift size exceeded" << std::endl;
      break;
    }
    if (!std::cin)
    {
      std::cout << "** Tracker error: unable to read shift size" << std::endl;
      break;
    }
    
    CommercialVehicle* shift[maxShiftSize];
    C4 = 12,    // variable C4 = max Operator ID length + c4
    C5 = 11,    // variable C5 = max Operator CDL length + c5
    C6 = 12;    // variable C6 = max Vehicle Registration Number length + c6 */ 
    //in values
    char reg[maxStringSize];
    char id[maxStringSize];
    char cdl[maxStringSize];
    unsigned int pc;
    float length, width, height, radius;
    
    //rundown values
    size_t 
      carriages = 0,
      buses = 0,
      limos = 0,
      trucks = 0,
      vans = 0,
      tankers = 0,
      flatbeds = 0,
      unknowns = 0,
      badRegs = 0,
      passengerCaps = 0;
    float loadCaps = 0; 
        
    for (size_t i = 0; i < shiftSize; ++i)
    {
      std::cin >> reg;
      vehicleType = CommercialVehicle::RegDecode(reg);
      
      switch (vehicleType)
      {
        case vehicle:
          std::cin >> id >> cdl;
          shift[i] = new CommercialVehicle (reg, id, cdl, 0);
          unknowns++;
          break;
        case carriage:
          std::cin >> id >> cdl >> pc;
          shift[i] = new Carriage (reg, id, cdl, pc);
          carriages++;
          break;
        case bus:
          std::cin >> id >> cdl >> pc;
          shift[i] = new Bus (reg, id, cdl, pc);
          buses++;
          break;
        case limo:
          std::cin >> id >> cdl >> pc;
          shift[i] = new Limo (reg, id, cdl, pc);
          limos++;
          break;
        case truck:
          std::cin >> id >> cdl;
          shift[i] = new Truck (reg, id, cdl);
          trucks++;
          break;
        case van:
          std::cin >> id >> cdl >> length >> width >> height;
          shift[i] = new Van (reg, id, cdl, length, width, height);
          vans++;
          break;
        case tanker:
          std::cin >> id >> cdl >> radius >> length;
          shift[i] = new Tanker (reg, id, cdl, radius, length);
          tankers++;
          break;
        case flatbed:
          std::cin >> id >> cdl >> length >> width;
          shift[i] = new Flatbed (reg, id, cdl, length, width);
          flatbeds++;
          break;
        case badReg:
          shift[i] = new CommercialVehicle (badRegMsg, badIDMsg, badCDLMsg,0);
          badRegs++;
          break;
        default:
          std::cin.ignore('\n');
          break;
      } // end switch
      
      if ( C4 < strlen(reg) ) C4 = strlen(reg);
      if ( C5 < strlen(id) ) C5 = strlen(id);
      if ( C6 < strlen(cdl) ) C6 = strlen(cdl);
      
      passengerCaps += shift[i]->PassengerCapacity();
      loadCaps += shift[i]->LoadCapacity();
      
    } // end for loop  
    
    shiftCount++;
    C4 += c4, C5 += c5, C6 += c6;
    
    // output shift data
    
    std::cout << " Shift " << shiftCount << " Summary\n"
              << " ===============\n";
    std::cout << '\n'
              << "  Carriages:            " << carriages << "\n" 
              << "  Buses:                " << buses << "\n"
              << "  Limos:                " << limos << "\n"
              << "  Trucks:               " << trucks << "\n"
              << "  Vans:                 " << vans << "\n"
              << "  Tankers:              " << tankers << "\n"
              << "  Flatbeds:             " << flatbeds << "\n"
              << "  Unknowns:             " << unknowns << "\n"
              << "  Badregs:              " << badRegs << "\n"
              << "  Total Passenger Cap:  " << passengerCaps << "\n";
    std::cout << std::setprecision(2) << std::fixed;         
    std::cout << "  Total Freight Cap:    " << loadCaps << "\n"
              << '\n';
    
    std::cout << " Shift " << shiftCount << " Log\n"
              << " ===============\n";
    std::cout << '\n'
              << std::setw(C1) << "Type"
              << std::setw(C2) << "Pass Cap"
              << std::setw(C3) << "Load Cap"
              << std::left << "  "
              << std::setw(C4) << "Registration"
              << std::setw(C5) << "Operator ID"
              << std::setw(C6) << "Operator CDL"
              << std::right
              << '\n';

    std::cout << std::setw(C1) << "----"
              << std::setw(C2) << "--------"
              << std::setw(C3) << "--------"
              << std::left << "  "
              << std::setw(C4) << "------------"
              << std::setw(C5) << "-----------"
              << std::setw(C6) << "------------"
              << std::right
              << '\n';
    
    for (size_t i = 0; i < shiftSize; ++i)
    {
      std::cout << std::setw(C1) << shift[i]->ShortName() 
                << std::setw(C2) << shift[i]->PassengerCapacity()
                << std::setw(C3) << shift[i]->LoadCapacity() 
                << std::left << "  "
                << std::setw(C4) << shift[i]->Registration() 
                << std::setw(C5) << shift[i]->Operator()
                << std::setw(C6) << shift[i]->CDL()
                << std::right
                << '\n';      
      
      delete shift[i];          
    }

    std::cout << '\n';    
  } // end do
  while (shiftSize < maxShiftSize && shiftSize != 0);
  
  std::cout << "\n...Thank you for using FastLane Tracker.\n" << std::endl;
  
  return 0;
}


