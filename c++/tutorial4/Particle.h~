// Prevents the particle header file bwing included more than once
#ifndef PARTICLE_h
#define PARTICLE_h

#include <string>
using std::string;

class Particle {

public:

  // Constructors and destructors
  Particle();
  Particle(double px, double py, double pz);
  virtual ~Particle();
  
  // Setters
  void setPx(double px); 
  void setPy(double py); 
  void setPz(double pz); 

  // Getters
  // Momentum in the x,y and z directions
  double getPx()     const; 
  double getPy()     const; 
  double getPz()     const; 
  // Angle to the z axis in degrees (0 to 180)
  double getTheta()  const; 
  // Angle to the x axis in degrees (-180 to 180)
  double getPhi()    const; 
  double getEnergy() const;
  double getMass()   const;
  int    getCharge() const;
  int    getId()     const;
  // The name of the particle as a string
  virtual string getType() const = 0;

protected:

  double m_mass;
  int    m_charge;
  int    m_id;

private:

  double m_px;
  double m_py;
  double m_pz;

};

#endif
