#ifndef SAMPLE_H
#define SAMPLE_H 

// declaration of sample class
class Sample {
 
 public:

  // constructors
  Sample();
  Sample(char* filename);
  Sample(double* sample, int size);

  // copy constructor
  Sample(const Sample&);
  
  // destructor
  ~Sample();

  // overloaded operators
  Sample operator+ (const Sample& rhs);
  Sample& operator= (const Sample& rhs);

  // accessor functions
  int getSize() const {return the_size;}
  double* getSample() const {return the_sample;}
  void showSample() const;
  
  // class methods
  double mean() const;
  double stdev() const;
  double* order(int rank = 1) const;
  void selfOrder(int rank = 1);
  double correlation(const Sample& b) const;
  double covar(const Sample& b) const;

private:

  // private member data
  int the_size;
  double* the_sample;

  // private member functions
  int setSize();
  double* setSample(int size);
};
#endif