#include "MyFloat.h"

MyFloat::MyFloat(){
  sign = 0;
  exponent = 0;
  mantissa = 0;
}

MyFloat::MyFloat(float f){
  unpackFloat(f);
}

MyFloat::MyFloat(const MyFloat & rhs){
	sign = rhs.sign;
	exponent = rhs.exponent;
	mantissa = rhs.mantissa;
}

ostream& operator<<(std::ostream &strm, const MyFloat &f){
	strm << f.packFloat();
	return strm;

}




MyFloat MyFloat::operator+(const MyFloat& rhs) const{
	
	return *this;
}

MyFloat MyFloat::operator-(const MyFloat& rhs) const{

	return *this;
}

void MyFloat::unpackFloat(float f) {
	unpacksign(f);
	unpackexponent(f);
	unpackmantissa(f);

}//unpackFloat
void MyFloat::unpacksign(float f)
{
	unsigned int fot = *((unsigned int*)&f);
	__asm__(
	"cld;"
	"shrl $31,%[fot]" :
	[fot] "+r" (fot) :
	:
	"cc"
	);
	sign = fot;

}
void MyFloat::unpackexponent(float f)
{
	unsigned int fot = *((unsigned int*)&f);
	unsigned int mask = 0x7f800000; //lower 23 bits 0. next 8 1's
	__asm__(
	"cld;"
	"xorl %[mask],%[fot];"
	"shrl $23,%[fot]" :
	[fot] "+r" (fot) :
	[mask] "r" (mask) :
	"cc"
	);
	exponent = fot;
}
void MyFloat::unpackmantissa(float f)
{
	unsigned int fot = *((unsigned int*)&f);
	unsigned int mask = 0x7fffff; //lower 23 bits all 1's
	__asm__(
	"cld;"
	"xorl %[mask],%[fot]" :
	[fot] "+r" (fot) :
	[mask] "r"(mask):
	"cc"
	);
	mantissa = fot;
}

float MyFloat::packFloat() const{
  //returns the floating point number represented by this
  float f = 0;
  
  return f;
}//packFloat
//

bool MyFloat::carryWouldHappen(unsigned int a, unsigned int b){
  bool carry = false;
 
  return carry;
}//carryWouldHappen


