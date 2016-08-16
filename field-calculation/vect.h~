#ifndef vect_h 
#define vect_h

class vect
{
private:
  double x,y,z;

public:
  vect(){x=0;y=0;z=0;}
  vect(const  double& A,const   double& B, const  double& C){x=A;y=B;z=C;}
  ~vect(){}

  //required functions for vectors
  double dot( const  vect& a)  { return x*a.x + y*a.y + z*a.z;}
  vect cross( const  vect& a){
    double X(0),Y(0),Z(0);
    X = y*a.z - z*a.y;
    Y = z*a.x - x*a.z;
    Z = x*a.y - y*a.x;
    return vect(X,Y,Z);
  }
  double magnitude(){return pow(x*x+y*y+z*z,.5);}

  //overload mathematical operators
  vect operator+(const vect& A){ return vect(x+A.x,y+A.y,z+A.z); }
  vect operator-(const vect& A){ return vect(x-A.x,y-A.y,z-A.z); }
  vect operator*(const double& A){ return vect(x*A,y*A,z*A); }
  vect operator/(const double& A){ return vect(x/A,y/A,z/A); }
  
  //overload << to output vector info with ease.
  void operator<<(ostream& os) { os << "x " << x << "\t" << "y " << y << "\t" << "z " << z; }

  //getters
  double getX() const  {return x;}
  double getY() const  {return y;}
  double getZ() const  {return z;}
  
  void setVect(const double& A,const double& B, const double& C){x=A;y=B;z=C;}
};

#endif
