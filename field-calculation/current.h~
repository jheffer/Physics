#ifndef current_h 
#define current_h

class current
{
private:
  vect start, end; // the current path goes from start to end
  double I; // current magnitude/A

public:
  current(){I=0;}
  current(const vect& A, const vect& B, const double& current){
    I = current;
    start = A;
    end = B;
  }
  ~current(){};
  vect vect_AB() const  {
    vect a(end.getX()-start.getX(),end.getY()-start.getY(),end.getZ()-start.getZ());
    return a;
  }
  //getters
  vect getStart() const  {return start;}
  vect getEnd() const   {return end;}
  double getSize() const  {return I;}

};

#endif
