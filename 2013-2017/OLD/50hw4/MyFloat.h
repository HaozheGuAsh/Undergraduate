#ifndef MY_FLOAT_H
  #define MY_FLOAT_H
  
  #include <iostream> 
  using namespace std;
  
  class MyFloat{
    public:
    	//constructors
      MyFloat();
	  MyFloat(float f);
	  MyFloat(const MyFloat & rhs);
      virtual ~MyFloat() {};
      
      //output
      friend ostream& operator<<(std::ostream& strm, const MyFloat& f);
	 
      
	  MyFloat operator== (const float& f);
      //addition
      MyFloat operator+(const MyFloat& rhs) const; 
      
      //subtraction
      MyFloat operator-(const MyFloat& rhs) const; 


    
    private:
		  unsigned int sign;
		  unsigned int exponent;
		  unsigned int mantissa;
		  bool checked = false;
		  
		  
		  void unpackFloat(float f);
		  void unpacksign(float f);
		  void unpackexponent(float f);
		  void unpackmantissa(float f);

		  float packFloat() const;
		  float packsign(float f)const;
		  float packexponent(float f)const;
		  float packmantissa(float f)const;
		  static bool carryWouldHappen(unsigned int a, unsigned int b);
  
  };
  
  
#endif
