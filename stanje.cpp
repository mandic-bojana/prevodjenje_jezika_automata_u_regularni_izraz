#ifndef __STANJE_H__
#define __STANJE_H__ 1


#include "stanje.h"
 
Stanje::Stanje(){}

Stanje::Stanje(int _broj): broj(_broj){
	pocetno=false;
	zavrsno=false;
  }

  Stanje::Stanje(const Stanje& p) {
     broj=p.Broj();
	pocetno=p.Pocetno();
	zavrsno=p.Zavrsno();
  }


  int Stanje::Broj() const{
    return broj;
  }


  bool Stanje::Pocetno() const{
    return pocetno;
  }

  bool Stanje::Zavrsno() const{
    return zavrsno;
  }

  void Stanje::setPocetno(bool _pocetno){
    pocetno=_pocetno;
  }

  void Stanje::setZavrsno(bool _zavrsno){
    zavrsno=_zavrsno;
  }


  bool Stanje::operator==(const Stanje &p) const{
    return broj==p.Broj();
  }

  bool Stanje::operator!=(const Stanje &p) const{
    return !((*this)==p);
  }

bool Stanje::operator<(const Stanje &p) const {
  return broj<p.Broj();
}


ostream & operator<<(ostream & o, const Stanje &q){
  o<<"q"<<q.Broj();
  return o;
}



#endif
