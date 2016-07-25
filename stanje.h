#include <iostream>
#include <list>

using namespace std;

class Stanje{

  private:
  int broj;
  bool pocetno;
  bool zavrsno;
  
 public:
  Stanje();

 Stanje(int _broj);

  Stanje(const Stanje& p);

  ~Stanje();

  int Broj() const;


  bool Pocetno() const;

  bool Zavrsno() const;

  void setPocetno(bool _pocetno);

  void setZavrsno(bool _zavrsno);


  bool operator==(const Stanje &p) const;

  bool operator!=(const Stanje &p) const;

  bool operator<(const Stanje &p) const; 
  
  

};


ostream & operator<<(ostream & o,const Stanje &q);
