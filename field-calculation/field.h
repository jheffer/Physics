#ifndef field_h 
#define field_h

class field
{
private:
  vect pos, vec; // B field at position

public:
  field(){}
  field(vect X, vect V)
  {
    pos = X;
    vec = V;
  }
  field(vect X)
  {
    pos = X;
    vect B0(0.0, 0.0, 0.0); // initial magnetic field (zero)  
    vec = B0;
  }
  ~field(){};

  // Calculate magnetic field component created by a current element
  void AddCurrent(const current& A, const int& steps)
  {
    vect direction = A.vect_AB();
    vect centre_pos, centre_vec;
    for (int i=0; i < steps; i++)
    {
      centre_pos = A.getStart() + A.vect_AB()*double(i)/steps; // find centre of current element
      centre_vec = (pos-centre_pos); // find line from centre to pos
      //A.getStart().operator<<(cout);
      vec = vec + A.vect_AB().cross(centre_vec)* 1e-7 * A.getSize() / (steps*pow(centre_vec.magnitude(),3));
      // u0 / pi = 1e-7
    }
  }

  vect getPos() const {return pos;}
  vect getVec() const {return vec;}
};

#endif
