#include <iostream>
#include <set>
#include <deque> 
#include "prelaz.h"
#include <cstdio>

using namespace std;

class Automat{

 private:
  set<char> azbuka;
  deque<Stanje> stanja;
  set<Prelaz> prelazi;
  
 public:
  Automat();
  Automat(set<char> _azbuka, deque<Stanje> _stanja, set<Prelaz> _prelazi);
  

  set<Prelaz> vratiSvePrelazeIzZadatogStanja(Stanje &Q);
  set<Prelaz> vratiSvePrelazeUZadatoStanje(Stanje &Q);	 
  Regex* vratiJezikPrelazaIzmedjuDvaZadataStanja(Stanje &P, Stanje &Q);
  
  friend Regex* eliminacijaStanja(const Automat &A);
  
  void ispisPrelaza();

  void ucitajAutomat(); 
  void dodajPrelaz(Prelaz &prelaz);
    
  friend ostream & operator<<(ostream &o, const Automat &A);  
  

};

