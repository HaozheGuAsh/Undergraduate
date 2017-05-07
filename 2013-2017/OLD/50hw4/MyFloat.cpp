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
	if (f.checked == true)
	{
		strm << "true";
		return strm;
	}
	
	
		strm << f.packFloat();
		return strm;
	
}
MyFloat MyFloat::operator== (const float& f)
{
	MyFloat tmp(f);
	if (sign == tmp.sign && exponent == tmp.exponent && mantissa == tmp.mantissa)
	{
		tmp.checked = true;
		return tmp;
	}

	return tmp;
}




MyFloat MyFloat::operator+(const MyFloat& rhs) const{
	MyFloat tmp;
	unsigned int manti1 = mantissa;
	unsigned int manti2 = rhs.mantissa;
	unsigned int expo1 = exponent;
	unsigned int expo2 = rhs.exponent;
	unsigned int sign1 = sign;
	unsigned int sign2 = rhs.sign;

//	cout << "sign1 " << sign1 << endl << "sign2 " << sign2 << endl;
//	cout << "expo1 " << expo1 << endl << "expo2 " << expo2 << endl;
//	cout << "manti1 " << manti1 << endl << "manti2 " << manti2 << endl;
	//first restore leading 1
	unsigned int mask = 0x00800000;// bit 24 == 1
	manti1 |= mask;
	manti2 |= mask;
//	cout << manti1 << endl;
	unsigned int mask2 = 0x7FFFFF80;//last 7 bit is 0
	//then make expo same(first all left shift 8 to make highest precision then right move smaller expo to be the same)
	manti1 = manti1<< 8;
	expo1 -= 8;
	manti2 = manti2<<8;
	expo2 -= 8; // shift all to left most
	if (expo1 > expo2)
	{
		int change = expo1 - expo2;
		manti2 = manti2 >> change;
		expo2 += change;
		manti2 = manti2 & mask2;

	} 
	else if (expo1 < expo2)
	{
		int change = expo2 - expo1;
		manti1 = manti1 >> change;
		expo1 += change;
		manti1 = manti1&mask2;
	}
	
	tmp.exponent = expo1;
	bool carry = false;
	//find larger one and decide sign
	if (sign1 == sign2)
	{
		tmp.sign = sign1;
		carry = carryWouldHappen(manti1, manti2);
		tmp.mantissa = manti1 + manti2;
	}
	else
	{
		if (manti1>=manti2)// ++ + -
		{
			tmp.sign = sign1;
			
			tmp.mantissa = manti1 - manti2;
		}
		else                // + + --
		{
			tmp.sign = sign2;
			
			tmp.mantissa = manti2 - manti1;
		}
	}
	//get rid of leading one
	//normalize
	
	if (carry == false)
	{
		if ((tmp.mantissa >> 31) != 1)
		{
			tmp.mantissa = tmp.mantissa << 1;
			tmp.exponent--;
		}
		tmp.mantissa = tmp.mantissa << 1;
		tmp.mantissa = tmp.mantissa >> 9;
		tmp.exponent += 8;
	}
	else
	{
		tmp.mantissa = tmp.mantissa >> 1;
		tmp.exponent++;
		tmp.mantissa = tmp.mantissa<< 1;
		tmp.mantissa = tmp.mantissa>> 9;
		tmp.exponent += 8;

	}
	if (tmp.mantissa == 0 && (sign1 != sign2) && (exponent==rhs.exponent))
	{
		tmp.exponent = 0;
	}
	return tmp;
}

MyFloat MyFloat::operator-(const MyFloat& rhs) const{
		MyFloat newrhs;
		newrhs = rhs;
		if (rhs.sign == 0)
		{
			newrhs.sign = 1;
		}
		else
		{
			newrhs.sign = 0;
		}
		return operator+(newrhs); //  change - sign to +
	
	MyFloat tmp;
	return tmp;
}

void MyFloat::unpackFloat(float f) {

	unpacksign(f);
	unpackexponent(f);
	unpackmantissa(f);

}//unpackFloat
void MyFloat::unpacksign(float f)
{
	unsigned int fot = *((unsigned int*)&f);
	//cout << "float is : " << fot << endl;
	__asm__(
	"cld;"
	"shrl $31,%[fot]" :
	[fot] "+r" (fot) :
	:
	"cc"
	);
	sign = fot;
	//cout << "sign:" << sign << endl;
}
void MyFloat::unpackexponent(float f)
{
	unsigned int fot = *((unsigned int*)&f);
	unsigned int mask = 0x7f800000; //lower 23 bits 0. next 8 1's
	__asm__(
	"cld;"
	"andl %[mask],%[fot];"
	"shrl $23,%[fot]" :
	[fot] "+r" (fot) :
	[mask] "r" (mask) :
	"cc"
	);
	exponent = fot;
	//cout << "exponent:" << exponent << endl;
}
void MyFloat::unpackmantissa(float f)
{
	unsigned int fot = *((unsigned int*)&f);
	unsigned int mask = 0x7fffff; //lower 23 bits all 1's
	__asm__(
	"cld;"
	"andl %[mask],%[fot]" :
	[fot] "+r" (fot) :
	[mask] "r"(mask):
	"cc"
	);
	mantissa = fot;
	//cout << "mantissa:" << mantissa << endl;
}

float MyFloat::packFloat() const{
  //returns the floating point number represented by this
  float f = 0;
  f = packsign(f);
  f = packexponent(f);
  f = packmantissa(f);
  return f;
}//packFloat
//
float MyFloat::packsign(float f) const
{
	__asm__(
		"cld;"
		"shll $31,%[sign];" 
		"orl %[sign],%[f] ":
		[f] "+r" (f) :
		[sign] "r" (sign):
		"cc"
		);
	return f;
}
float MyFloat::packexponent(float f) const
{
	__asm__(
		"cld;"
		"shll $23,%[expo];"
		"orl %[expo],%[f] ":
		[f] "+r" (f) :
		[expo] "r" (exponent) :
		"cc"
		);
	return f;
}
float MyFloat::packmantissa(float f) const
{
	__asm__(
		"cld;"
		"orl %[manti],%[f] ":
		[f] "+r" (f) :
		[manti] "r" (mantissa) :
		"cc"
		);
	return f;
}
bool MyFloat::carryWouldHappen(unsigned int a, unsigned int b){
  bool carry = false;
  int car = 0;
  //cout << a << endl<< b << endl;
  __asm__(
	  "cld;"
	  "addl %[a],%[b];"
	  "jc have_carry;"
	  "jmp no_carry;"
	  "have_carry:;"
	  "incl %[car];"
	  "no_carry:":
	  [car]"+r"(car), [b]"+r"(b) :
	  [a]"r"(a):
	  "cc"
	  );
 
  if (car == 1){ carry = true; }
  return carry;
}//carryWouldHappen

