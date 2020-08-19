#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "car.h"

/****************************************/
/****************************************/

float StringToFloat(const char* str) {
   float f;
   std::istringstream iss(str);
   iss >> f;
   return f;
}


/****************************************/
/****************************************/

void TestCar(float starting_position,float starting_speed,float starting_acceleration,float update_interval) {
   CCar c(starting_position,starting_speed,starting_acceleration,update_interval);
   /* Print starting values of our car */
   c.PrintStatus();
   /* Verify initial coeherence */
   c.VerifyCoherence();
   
   float averageSpeedCpp = c.AverageSpeedCpp();
   float averageSpeedAsm = c.AverageSpeedAsm();
   
   std::cout << "\tThe average speed: C: " << averageSpeedCpp << " ASM: " << averageSpeedAsm << std::endl;
   if(!Equals(averageSpeedCpp, averageSpeedAsm))
      std::cerr << "ERROR: the average speed do not match" << std::endl;
   else
      std::cout << "\tThe average speed matches" << std::endl;
   
   c.UpdateStatusCpp();
   c.UpdateStatusAsm();
   c.VerifyCoherence();
   c.PrintStatus();
   c.UpdateStatusCpp();
   c.UpdateStatusAsm();
   c.VerifyCoherence();
   c.PrintStatus();
   c.UpdateStatusCpp();
   c.UpdateStatusAsm();
   c.VerifyCoherence();
   c.PrintStatus();
   averageSpeedCpp = c.AverageSpeedCpp();
   averageSpeedAsm = c.AverageSpeedAsm();
   std::cout << "\tThe average speed: C: " << averageSpeedCpp << " ASM: " << averageSpeedAsm << std::endl;
   if(!Equals(averageSpeedCpp, averageSpeedAsm))
      std::cerr << "ERROR: the average speed does not match" << std::endl;
   else
      std::cout << "\tThe average speed matches" << std::endl;
   
   
   float totalDistCpp = c.TotalDistCpp();
   float totalDistAsm = c.TotalDistAsm();
   std::cout << "\tThe total distance: C: " << totalDistCpp << " ASM: " << totalDistAsm << std::endl;
   if(!Equals(totalDistCpp, totalDistAsm))
      std::cerr << "ERROR: the total distance does not match" << std::endl;
   else
      std::cout << "\tThe total distance matches" << std::endl;


   float equivAccCpp = c.EquivalentAccCpp();
   float equivAccAsm = c.EquivalentAccAsm();
   std::cout << "\tThe equivalent acceleration: C: " << equivAccCpp << " ASM: " << equivAccAsm << std::endl;
   if(!Equals(equivAccCpp, equivAccAsm))
      std::cerr << "ERROR: the equivalent acceleration does not match" << std::endl;
   else
      std::cout << "\tThe equivalent acceleration matches" << std::endl;
}
/****************************************/
/****************************************/

int main(int argc, char** argv) {
   /*
    * Command line argument parsing
    */
   /* Check that the right number of args was passed */
   if(argc != 5) {
      std::cerr << "Usage:" << std::endl;
      std::cerr << "\ttp4 <starting_position> <starting_speed> <starting_acceleration> <update_interval>" << std::endl;
      return 1;
   }
   /* Parse values */
   
   float starting_position = StringToFloat(argv[1]);
   float starting_speed = StringToFloat(argv[2]);
   float starting_acceleration = StringToFloat(argv[3]);
   float update_interval = StringToFloat(argv[4]);
   
   /* Check that the the update interval is greater than 1 */
   if(update_interval < 1)  {
      std::cerr << "ERROR: the update interval must be larger than 1" << std::endl;
      return 1;
   }
   
   if(starting_acceleration < 1)  {
      std::cerr << "ERROR: the starting acceleration must be larger than 1" << std::endl;
      return 1;
   }
   /* Perform tests */
   TestCar(starting_position,starting_speed,starting_acceleration,update_interval);
   return 0;
}

