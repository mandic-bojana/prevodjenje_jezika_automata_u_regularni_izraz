#ifndef __REGEX_H__
#define __REGEX_H__ 1


#include "regex.h"

using namespace std;

//konstante za prioritete
#define EPSILON -1
#define KARAKTER 0
#define UNIJA 1 
#define KONKATENACIJA 2
#define ITERACIJA 3

int Iteracija::prioritet()const{
  return ITERACIJA;
}

int Konkatenacija::prioritet()const{
  return KONKATENACIJA;
}

int Unija::prioritet()const{
  return UNIJA;
}

int Karakter::prioritet()const{
  if(s=="eps")
    return EPSILON;
  return KARAKTER;
}

void Iteracija::ispis(ostream& o)const{
  if(operand->prioritet()==ITERACIJA || operand->prioritet()==EPSILON)
    operand->ispis(o);
  else if(operand->prioritet()>KARAKTER){
    o<<"(";
    operand->ispis(o);
    o<<")*";
  }
  else{
    operand->ispis(o);
    o<<"*";
  }
}

void Konkatenacija::ispis(ostream& o)const{
  if(prvi->prioritet()==EPSILON && drugi->prioritet()==EPSILON)
    prvi->ispis(o);
  else{
    if(prvi->prioritet()==EPSILON)
      ;
    else if(prvi->prioritet()==UNIJA){
      o<<"(";
      prvi->ispis(o);
      o<<")";
    }
    else
      prvi->ispis(o);

    if(drugi->prioritet()==EPSILON)
      ;  
    else if(drugi->prioritet()==UNIJA){
      o<<"(";
      drugi->ispis(o);
      o<<")";
    }
    else
      drugi->ispis(o);
  }
}

void Unija::ispis(ostream& o)const{
  prvi->ispis(o);
  o<<"|";
  drugi->ispis(o);
}

void Karakter::ispis(ostream &o)const{
  o<<s;
}

ostream& operator<<(ostream &o, const Regex& r){
  r.ispis(o);
  return o;
}


#endif
