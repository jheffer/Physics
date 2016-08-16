#include <iostream>
#include "Particle.h"
#include "Electron.h"

using namespace std;

/* Electron */

Electron::Electron(double px, double py, double pz): Particle::Particle(px, py, pz) {
  m_mass = 0.510998918;
  m_charge = -1;
  m_id = 11;
//  cout << "Electron created." << endl;
}

Electron::~Electron() {
//  cout << "Electron destroyed." << endl;
}

string Electron::getType() const {
  return "Electron";
}

/* Muon */

Muon::Muon(double px, double py, double pz): Particle::Particle(px, py, pz) {
  m_mass = 105.658369;
  m_charge = -1;
  m_id = 13;
// cout << "Muon created." << endl;
}

Muon::~Muon() {
 // cout << "Muon destroyed." << endl;
}

string Muon::getType() const {
  return "Muon";
}

// Compare energy of two Muons
/*bool Muon::operator() (const Muon &mu) {
  if ( getEnergy() > mu.getEnergy() ) { return true; }
  return false;
}*/

/* Photon */

Photon::Photon(double px, double py, double pz): Particle::Particle(px, py, pz) {
  m_mass = 0.0;
  m_charge = 0.0;
  m_id = 22;
//  cout << "Photon created." << endl;
}

Photon::~Photon() {
//  cout << "Photon destroyed." << endl;
}

string Photon::getType() const {
  return "Photon";
}
