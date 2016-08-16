#ifndef ELECTRON_h
#define ELECTRON_h

#include "Particle.h"

class Electron: public Particle {

public:

  Electron(double px, double py, double pz);
  ~Electron();
  string getType() const;

};

class Muon: public Particle {

public:

  Muon(double px, double py, double pz);
  ~Muon();
  string getType() const;
//  bool operator() (const Muon &mu);
};

class Photon: public Particle {

public:

  Photon(double px, double py, double pz);
  ~Photon();
  string getType() const;

};

#endif