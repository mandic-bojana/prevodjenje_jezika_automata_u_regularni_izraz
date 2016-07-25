#ifndef __PRELAZ_H__
#define __PRELAZ_H__ 1

#include <iostream>
#include "stanje.h"
#include "regex.h"

using namespace std;

class Prelaz{

 private:
  Stanje ulaznoStanje;
  Regex* etiketa;
  Stanje izlaznoStanje;

 public:
  Prelaz(){}
  Prelaz(Stanje _ulaznoStanje, Regex* _etiketa, Stanje _izlaznoStanje);

  Prelaz(const Prelaz &prelaz);
  ~Prelaz();

  Prelaz& operator=(const Prelaz &prelaz);

  Stanje UlaznoStanje() const;

  Regex* Etiketa() const;

  Stanje IzlaznoStanje() const;

  bool isPetlja() const;

  bool operator==(const Prelaz &prelaz) const;

  bool operator!=(const Prelaz &prelaz) const;
  
  bool operator<(const Prelaz &prelaz) const;

  friend ostream & operator<<(ostream &o,const Prelaz &prelaz);


	
};





#endif
