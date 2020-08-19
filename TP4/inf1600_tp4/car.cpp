#include "car.h"
#include <cmath>

/****************************************/
/****************************************/


/*
 * Constant used to test float equality.
 */
static const float EPSILON = 1e-4;

/*
 * Returns true if the given values are close enough.
 * Not the best possible float comparison ever, but it's
 * enough for this TP.
 */
bool Equals(float a, float b) {
   /* Take care of obvious case */
   if(a == b) return true;
   /* Take care of approximations */
   if(::fabsf(a-b) < EPSILON) return true;
   /* If we get here, the numbers are most probably not equal */
   return false;
}

/****************************************/
/****************************************/

CCar::CCar(float starting_position,float starting_speed,float starting_acceleration,float update_interval) :
   s0(starting_position),
   v0(starting_speed),
   a0(starting_acceleration),
   st_c(starting_position),
   vt_c(starting_speed),
   at_c(starting_acceleration),
   time_passed_c(0),
   st_asm(starting_position),
   vt_asm(starting_speed),
   at_asm(starting_acceleration),
   time_passed_asm(0),
   interv(update_interval),
   started(0){
}
/****************************************/
/****************************************/
CCar::~CCar() {
}

/****************************************/
/****************************************/
void CCar::VerifyCoherence() const{
	if (!Equals(st_c,st_asm))
      std::cerr << "ERROR: the current position does not match" << std::endl;
   else
      std::cout << "\tThe current position matches" << std::endl ;
  
 	if (!Equals(vt_c,vt_asm))
      std::cerr << "ERROR: the current speed does not match" << std::endl;
   else
      std::cout << "\tThe current speed matches" << std::endl ;
	
}

/****************************************/
/****************************************/
void CCar::PrintStatus() const{
    std::cout << "\tThe current position:     C: " << st_c << " ASM: " << st_asm << std::endl ;
    std::cout << "\tThe current speed:        C: " << vt_c << " ASM: " << vt_asm << std::endl ;
    std::cout << "\tThe current acceleration: C: " << at_c << " ASM: " << at_asm << std::endl ; 	
}


/****************************************/
/****************************************/
void CCar::UpdateStatusCpp(){
	st_c = st_c + (vt_c*interv) + (0.5f*at_c*interv*interv);
	vt_c = vt_c + at_c*interv;
	started += interv;	
}

/****************************************/
/****************************************/
float CCar::TotalDistCpp() const{
	return (st_c - s0);
}

/****************************************/
/****************************************/
float CCar::AverageSpeedCpp() const{
	if(started == 0)
		return v0;
	
	float totS = TotalDistCpp();
	return (totS/started);	
}


/****************************************/
/****************************************/
float CCar::EquivalentAccCpp() const{
	float totS = TotalDistCpp();
	return (2.0f * totS)/(started*started);
}

/****************************************/
/****************************************/
