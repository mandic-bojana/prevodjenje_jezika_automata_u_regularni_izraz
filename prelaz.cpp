#include "prelaz.h"

Prelaz::Prelaz(Stanje _ulaznoStanje, Regex* _etiketa, Stanje _izlaznoStanje): ulaznoStanje(_ulaznoStanje),  etiketa(_etiketa), izlaznoStanje(_izlaznoStanje){
  }
Prelaz::Prelaz(const Prelaz &prelaz): ulaznoStanje(prelaz.UlaznoStanje()), izlaznoStanje(prelaz.IzlaznoStanje()) {
  etiketa=(prelaz.Etiketa())->kopija();
  }
Prelaz& Prelaz::operator=(const Prelaz &p){
  if(this!=&p){
    delete etiketa;
    
    etiketa=p.Etiketa()->kopija();
    ulaznoStanje=p.UlaznoStanje();
    izlaznoStanje=p.IzlaznoStanje();
  }
  return *this;
}
  Prelaz::~Prelaz(){
    delete etiketa;
	}

  Stanje Prelaz::UlaznoStanje() const{
    return ulaznoStanje;
  }

  Regex* Prelaz::Etiketa() const{
    return etiketa;
  }

  Stanje Prelaz::IzlaznoStanje() const{
    return izlaznoStanje;
  }

  bool Prelaz::isPetlja() const{
    if(ulaznoStanje==izlaznoStanje)
      return true;
    return false;
  }


  bool Prelaz::operator==(const Prelaz &prelaz) const{
    if((ulaznoStanje==prelaz.UlaznoStanje()) && (izlaznoStanje==prelaz.IzlaznoStanje()) )
      return true;
    return false;
  }


  bool Prelaz::operator!=(const Prelaz &prelaz) const{
    return !(*this==prelaz);
  }

bool Prelaz::operator<(const Prelaz &prelaz) const{
  if(ulaznoStanje<prelaz.UlaznoStanje())
    return true;
  else if(prelaz.UlaznoStanje()<ulaznoStanje)
    return false;
  else return izlaznoStanje<prelaz.IzlaznoStanje();
}
  


ostream & operator<<(ostream &o, const Prelaz &prelaz){
  o<<prelaz.ulaznoStanje<<" ---[ "<<*(prelaz.etiketa)<<" ]---> "<<prelaz.izlaznoStanje;
  return o;
}



